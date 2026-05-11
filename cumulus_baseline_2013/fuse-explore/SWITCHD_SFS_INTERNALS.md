# switchd FUSE / SFS Internals

Cumulus calls its FUSE filesystem **SFS — "Switch File System"**. The source
file is `lib/sfs/sfs.c` in the Cumulus 2.5 build tree (the build-server path
`/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c`
is hardcoded into the binary as `__FILE__` strings in `assert()` callsites).

This document reverse-engineers the full mechanism: what the on-disk-looking
tree at `/cumulus/switchd/` actually is, how reads/writes get dispatched, what
the registered handlers look like, and how triggers like `ctrl/hal/resync`
turn into BCM SDK calls.

---

## 1. The big picture

`switchd` is statically linked against **libfuse 2.x** (uses the
lower-level `fuse_new` + `fuse_mount` pair, not the convenience `fuse_main`).
At startup it:

1. Builds an in-memory tree of **`sfs_entry`** structs, one per path. The tree
   is rooted at the global `sfs_root` pointer (`DAT_11e45f94`).
2. Calls `sfs_register(path, entry_template, custom_getter, custom_setter, ctx)`
   for every config knob, telemetry counter, and trigger — 76 static call
   sites in the binary, plus per-port loops that register `52 × 4 = 208`
   per-interface entries.
3. Calls `fuse_new()` with a populated `fuse_operations` struct, then
   `fuse_mount("/cumulus/switchd", ...)`.
4. Enters the FUSE loop. Every VFS operation routed through `/cumulus/switchd/`
   lands in one of the registered callbacks below.

Mount point: **`/cumulus/switchd`** (literal string at `0x113189e0`,
referenced from `main()` at `FUN_10007af8`).

---

## 2. The `fuse_operations` table

Struct at **`0x11819868`** in switchd's data section, passed as the 2nd arg
to `fuse_new()` at `0x1004b7d0`. 19 of the 30 standard libfuse-2 callbacks
are populated:

| Off | Field | Handler | Size | Role |
|---|---|---|---|---|
| 0x00 | `getattr` | `FUN_100496e4` | 376 | stat(): returns mode + size from sfs_entry |
| 0x0c | `mknod` | `FUN_1004996c` | 52 | stub |
| 0x10 | `mkdir` | `FUN_100499a0` | 44 | stub |
| 0x14 | `unlink` | `FUN_100499cc` | 40 | stub |
| 0x18 | `rmdir` | `FUN_100499f4` | 40 | stub |
| 0x1c | `symlink` | `FUN_10049a1c` | 44 | stub |
| 0x20 | `rename` | `FUN_10049a48` | 44 | stub |
| 0x24 | `link` | `FUN_10049a74` | 44 | stub |
| 0x28 | `chmod` | `FUN_10049aa0` | 44 | stub |
| 0x2c | `chown` | `FUN_10049acc` | 48 | stub |
| 0x30 | `truncate` | `FUN_1004acec` | 48 | stub (returns ok) |
| 0x34 | `utime` | `FUN_10049afc` | 44 | stub |
| **0x38** | **`open`** | **`FUN_10049b88`** | **332** | **allocates per-fh backing buffer** |
| **0x3c** | **`read`** | **`FUN_1004a264`** | **452** | **find backing → refresh → memcpy** |
| **0x40** | **`write`** | **`FUN_1004abb4`** | **124** | **trampoline → `FUN_1004aaf0`** |
| 0x48 | `flush` | `FUN_1004ac30` | 188 | flush backing |
| 0x4c | `release` | `FUN_10049cd4` | 196 | free backing buffer |
| 0x50 | `fsync` | `FUN_10049b28` | 48 | |
| 0x68 | `readdir` | `FUN_1004985c` | 272 | walks entry->children |
| 0x80 | `create` | `FUN_10049b58` | 48 | stub |
| 0x90 | `utimens` | `FUN_1004ad1c` | 264 | |

The 11 NULLs are the mutating-path callbacks (mkdir/unlink/rmdir/etc.) that
Cumulus does not allow — the user-facing tree is fixed at startup. The
modifying paths that ARE allowed are `truncate`, `write`, `utime`/`utimens`
because `cl-acltool` writes config files atomically (open → truncate → write
→ release).

The stubs (44-52 byte funcs) return `-EROFS` or simply success without doing
anything.

---

## 3. The `sfs_entry` struct (reverse-engineered)

Based on field offsets used in the read/write/getattr handlers:

```c
struct sfs_entry {
    /*0x00*/ int       type;          // 0=dir,1=string,2=bool,3=u16,4=u32,5=int,6=trigger,7=enum
    /*0x04*/ char     *description;   // human-readable, shown to .meta consumers
    /*0x08*/ int       size_hint;     // 0 for dirs, file size for files
    /*0x0c*/ time_t    mtime;         // updated on every read() — set via time()
    /*0x10*/ uint32_t  size;          // current size of stringified value
    /*0x14*/ // (padding / fh-counter?)
    /*0x18*/ void     *value_ptr;     // pointer to the typed value (or string)
    /*0x1c*/ uint32_t  default_value; // for triggers + numeric defaults
    /*0x1e*/ uint16_t  min_u16;       // for type 3 — clamp lower
    /*0x20*/ union {
                uint16_t max_u16;     // for type 3 — clamp upper
                struct enum_pair *mapping; // for type 7 — enum {key,name} pairs
            };
    /*0x24*/ // ...
    /*0x38*/ struct sfs_backing *backings_list; // per-open backing buffers
    /*0x3c*/ int     (*getter)(path, entry, ctx); // custom refresh hook
    /*0x40*/ int     (*setter)(path, entry, ctx); // custom write-through hook
    /*0x44*/ void     *ctx;           // opaque user data passed to hooks
    // ...
};
```

The `sfs_entry` tree is keyed by path string. Lookup is via
`FUN_10048bd0(path, &out)` which hashes the path against the global root
table at `DAT_11e45f94`.

### Per-open `sfs_backing` (cache)

Each `open()` call allocates a backing buffer attached to the entry. When
`read()` runs, `FUN_1004965c(entry+0x18)` walks the backings list and finds
the one whose `fh` matches the current `fuse_context->fh`. This is the
cache: the value is computed at open time (or on a stale read), held in the
backing, and served from there on subsequent reads.

```c
struct sfs_backing {
    /*0x00*/ uint32_t fh;              // libfuse-assigned file handle
    /*0x04*/ uint32_t fh_id;
    /*0x08*/ void    *value_bytes;     // stringified value buffer
    /*0x0c*/ ...
    /*0x10*/ uint32_t size;            // length of value_bytes
    /*0x18*/ int      refcount;        // incremented on open
    /*0x1c*/ struct sfs_backing *next; // singly-linked list under entry
};
```

---

## 4. The 8 SFS types

Set in `entry->type` (offset 0x08). The same 8 are the only types that
appear in the `.meta` schema file:

| Type | `.meta` name | Read format | Write parser |
|---|---|---|---|
| 0 | dir | (lists children) | — |
| 1 | `char *` | raw bytes + "\n" | strncpy with size bound |
| 2 | `bool` | "TRUE"/"FALSE" + "\n" | accepts TRUE/FALSE/true/false ±"\n" |
| 3 | `uint16_t` | snprintf("%d", *u16) | atoi → clamp to entry->min/max |
| 4 | `uint32_t` | snprintf("%d", *u32) | atoi truncated to u32 |
| 5 | `int` | snprintf("%u", *int) | atoi |
| 6 | `trigger` | "write '%d' to trigger\n" OR custom help text | parse, then run setter |
| 7 | `enum` | walks mapping table, writes value name | (parses string back via mapping) |

The read-side formatter is **`FUN_10049d98`** (1228 bytes — a giant
type-switch), and the write-side parser is **`FUN_1004a428`** (1736 bytes —
the mirror image).

---

## 5. The `sfs_register` API

Wrapper at `FUN_1004bf0c` (120B), real implementation at `FUN_100493c0`.
Signature:

```c
bool sfs_register(
    const char       *path,      // FUSE path, e.g. "/config/route/max_routes"
    sfs_entry_t      *template,  // stack-allocated template, copied into tree
    custom_getter_t   getter,    // NULL for read-from-value_ptr default
    custom_setter_t   setter,    // NULL for write-to-value_ptr default
    void             *ctx        // passed to getter/setter
);
```

The template's `type`/`description`/`value_ptr`/etc. fields are copied. For
triggers, `value_ptr` is typically NULL and `default_value` holds the magic
number (usually `1`) you have to write to fire the trigger.

### 76 static call sites

The binary contains exactly 76 calls to `sfs_register`. They are concentrated
in eight grouping functions:

| Caller | # calls | Purpose |
|---|---|---|
| `FUN_10005eac` | 28 | Most `/config/*` knobs (route, stats, traffic, etc.) |
| `FUN_10005960`/`FUN_100059dc` | 5 | `/run/route_info/*` route counters |
| `FUN_1000de1c` | 8 | `/run/route_info/{ecmp_nh,host,mac}/*` |
| `FUN_10009a50` | 5 | `/run/acl_info/*` ACL counters |
| `FUN_10009b6c` | 3 | `/config/netlink/*` + `/ctrl/netlink/*` |
| `FUN_1000fa58`/`FUN_1000fb10`/`FUN_1000fc54` | 3 | Other `/run/route_info` |
| `FUN_10021884` | 1 | `/ctrl/hal/resync` |
| `FUN_10007af8` (main) | 4 | `/ctrl/logger`, `/ctrl/debug`, etc. |
| `FUN_10042508`/`FUN_10042610`/`FUN_10042730`/`FUN_100427d4` | 7 | `/run/stats/*` and `/clear/stats/*` |
| `FUN_1000e958` | 1 | `/config/interface/%s/interface_mode` (called 52× in a loop) |
| `FUN_1000ead4` | 3 | `/config/interface/%s/storm_control/{broadcast,multicast,unknown_unicast}` (×52) |
| others | ~7 | misc |

The per-port handlers (`FUN_1000e958`, `FUN_1000ead4`) format the path
dynamically with the port name and register one entry per port. That's
where the `52 × 4 = 208` per-interface entries come from — they appear in
`.meta` but only as one entry each in the binary's `sfs_register` table.

`52 × 4 (interface) + 28 + 5 + 8 + 5 + 3 + 3 + 1 + 4 + 7 + 7 + ... ≈ 295`
which matches `.meta`'s 295 schema lines exactly.

---

## 6. Read path: `cat /cumulus/switchd/config/route/max_routes`

```
syscall: open("/cumulus/switchd/config/route/max_routes", O_RDONLY)
      → fuse_operations.open  = FUN_10049b88
        ↳ FUN_10048bd0(path, &entry)   // hash-lookup in sfs_root
        ↳ allocate backing buffer
        ↳ link it into entry->backings (offset 0x38)
        ↳ store backing addr in fuse_file_info.fh

syscall: read(fd, buf, count)
      → fuse_operations.read  = FUN_1004a264
        ↳ entry = *(fi+0x14)
        ↳ backing = FUN_1004965c(entry+0x18)  // find backing by fh
        ↳ if entry->value_bytes is empty OR cache stale:
              FUN_10049d98(path, entry)        // refresh + format
                ↳ if entry->getter != NULL:
                      ret = entry->getter(path, entry, entry->ctx)
                      if ret != 0: skip default formatter
                ↳ switch (entry->type):
                      case 4: snprintf("%d", *(uint32_t *)entry->value_ptr)
                ↳ FUN_1004bcec(entry, formatted, len)  // copies into backing
        ↳ memcpy(buf, backing->value_bytes + offset, len)
        ↳ time(&entry->mtime)

syscall: close(fd)
      → fuse_operations.release = FUN_10049cd4
        ↳ refcount-- on backing
        ↳ if zero, unlink from entry->backings list and free
```

The **cache layer is per-fh**: each open allocates its own buffer. The
custom getter (`entry->getter` at offset 0x3c) is the hook for refreshing
the cached value from elsewhere — e.g. a BCM SDK call, a kernel netlink
query, a CPLD register read. If the getter is NULL, the default-formatter
simply reads `*entry->value_ptr` and stringifies it.

---

## 7. Write path: `echo 32768 > /cumulus/switchd/config/route/max_routes`

```
syscall: open(path, O_WRONLY|O_TRUNC)
      → fuse_operations.open      // same as read
      → fuse_operations.truncate  // FUN_1004acec — clears backing
syscall: write(fd, "32768\n", 6)
      → fuse_operations.write = FUN_1004abb4
        ↳ trampoline to FUN_1004aaf0(path, buf, len, off, fi, entry)
        ↳ if offset == 0:
              FUN_1004a428(path, entry)   // <<< TYPE-DISPATCHED PARSER
                ↳ raw = FUN_1004bec0(...)  // pull the new bytes from the buffer
                ↳ switch (entry->type):
                      case 4 (uint32):
                          new = atoi(raw)
                          // optionally clamp to entry->min/max — only for u16
                          *(uint32_t *)entry->value_ptr = new
                          if entry->setter != NULL:
                              entry->setter(path, entry, entry->ctx)
syscall: close(fd)
      → fuse_operations.release
```

The custom **setter** (`entry->setter` at offset 0x40) is where the change
actually propagates to hardware. For `/config/route/max_routes` it'll
trigger a route-table resize; for `/config/interface/swp1/interface_mode`
it calls the HAL interface-mode setter which programs the BCM PHY.

The **bool parser** is permissive: accepts `TRUE`/`true`/`FALSE`/`false`
with optional trailing newline (8 variants checked via successive
`strcmp`s).

The **u16 parser** is the only one that clamps to the schema's min/max —
the u32 and int parsers trust the caller.

---

## 8. Trigger path: `echo 1 > /cumulus/switchd/ctrl/hal/resync`

Registered at `FUN_10021884:0x10021d64` with:
```c
sfs_register("/ctrl/hal/resync", template_at_0x118190f8,
             NULL,                  // no getter (just returns help string)
             FUN_1002348c,          // setter = the resync handler
             NULL);                 // no ctx
```

The setter `FUN_1002348c` (228B):

```c
int hal_resync_trigger(entry) {
    LOG_DEBUG("/ctrl/hal/resync triggered");      // sfs.c line 0x24f

    hal = FUN_10022b38();                          // get the HAL singleton

    /* Phase 1: walk every HAL route — clear "in_hw" bit. */
    work_queue(DAT_11e456b8, /* hal_routes */
               FUN_10023444,                       // clear in_hw flag (mask 0x7fffffff)
               NULL);

    /* Phase 2: walk every HW route — sync into HAL cache. */
    work_queue(hal, FUN_100231e0, NULL);
       // ↳ for each HW route:
       //     hal_route = hash_lookup(hal_routes, hw_route_key);
       //     if (hal_route exists):
       //         if (different) update + log "HW route doesn't match HAL — Updating"
       //     else:
       //         alloc new hal_route + log "Route in HW but not in HAL — Adding"
       //     mark hal_route->flags |= 0x80000000 (in_hw)

    /* Phase 3: sweep — delete HAL routes that didn't get marked. */
    work_queue(DAT_11e456b8, FUN_10023570, NULL);
       // ↳ if (!(hal_route->flags & 0x80000000)):
       //       hash_delete(hal_neighbors, hal_route)
       //       log "Route in HAL cache but not in HW — Deleting"

    barrier(hal, NULL);
    return 0;
}
```

This is a classic **mark-and-sweep delta resync**: walk HW once
authoritatively, mark each HAL entry that matches, then sweep unmarked
HAL entries. Same algorithm cl-acltool uses to push iptables → FP TCAM.

The actual log messages, captured verbatim from the binary:
- `"HW route doesn't match HAL route. Updating."`  (sfs.c-related src line 0x21a)
- `"Route in HW, but not in HAL cache. Adding."`   (line 0x209)
- `"Route in HAL cache, but not in HW. Deleting."` (line 0x23d)

These will show up in `/var/log/switchd.log` whenever someone (or
cl-acltool) writes `1` to `/ctrl/hal/resync`.

---

## 9. Worked example: `/config/interface/swp1/interface_mode`

### Registration (per-port, in `FUN_1000e958`)

```c
void register_interface_mode(int port) {
    int per_port_state = DAT_11e4564c + port * 0x200;

    sfs_entry_t tmpl = {
        .type        = 7,                       // enum
        .description = "Port Interface Mode",
        .default_val = 0x1a4,
        .value_ptr   = per_port_state + 0x1cc,  // cached enum value (uint32_t)
        .mapping     = &DAT_11819028,           // 15-entry enum table
    };

    char *path = asprintf("/config/interface/%s/interface_mode",
                          per_port_state + 4);  // port name "swp1" etc.
    sfs_register(path, &tmpl,
                 FUN_1000e890,                  // getter
                 FUN_1000e8f4,                  // setter
                 per_port_state);               // ctx
    free(path);
}
```

The enum mapping at `0x11819028`:

| Key | Name |
|---|---|
| 0 | `Invalid` |
| 1 | `None` |
| 2 | `XGMII` |
| 3 | `XLAUI` |
| 4 | `SFI` |
| 5 | `XFI` |
| 6 | `KR` |
| 7 | `KR4` |
| 8 | `CR` |
| 9 | `CR4` |
| 10 | `SR` |
| 11 | `SR4` |
| 12 | `LR` |
| 13 | `LR4` |
| 14 | `ZR` |
| -1 | (terminator) |

### Reading `swp1/interface_mode`

```c
int getter(path, entry, ctx) {
    // ctx = per_port_state — points at struct port_info
    hal_get_intfmode(ctx->hal_handle /* *(ctx+0x18) */,
                     &ctx->cached_mode /* ctx+0x1cc */);
    return 0;
}
```

`FUN_10022284` (HAL hop) eventually calls `bcm_port_interface_get()`.

The default formatter for type-7 then walks the enum mapping, finds the
key matching `*entry->value_ptr`, writes the name string + `"\n"`.

### Writing `XFI` to `swp1/interface_mode`

```c
// Generic type-7 parser (FUN_1004a428 case 7):
//   raw = "XFI\n"
//   walk mapping until name == "XFI" → key 5
//   *entry->value_ptr = 5

int setter(path, entry, ctx) {
    hal_set_intfmode(ctx->hal_handle, ctx->cached_mode);
    return 0;
}
```

`FUN_10022308` (HAL hop) eventually calls `bcm_port_interface_set()` and a
chain of PHY reprogramming logic.

---

## 10. The `.meta` file

The 29 KB file at the root of the mount is **auto-generated from the
registered entry templates**. Each entry's `description`, `type`,
`default`, and (for u16) `min`/`max` are dumped tab-separated on init.

Format (1 line per registered path):

```
<path>\t<description>\t<type>\t<default>\t<min>\t<max>[\t<enum_values>]
```

The 295 lines = roughly:

- 75 static config knobs (the non-interface `/config/*`)
- 52 × 4 = 208 per-interface entries (`interface_mode` + 3 storm_control)
- 36 `/run/*` telemetry counters
- 6 `/ctrl/*` triggers + loggers
- 2 `/clear/*` action triggers

Where does it live? It's served by the FUSE filesystem itself — a special
implicit entry at `/.meta`. The first `readdir()` of the root populates it.

---

## 11. What's exposed but NOT in `.meta`

Searching the binary for path strings revealed two paths that exist as
sfs entries but don't appear in `.meta`:

- **`/ctrl/debug`** (`0x11318870`, referenced from `main()`) — toggles
  verbose debug mode. Not user-facing.
- **`/ctrl/sample/ulog_channel`** — sample-rate kernel ULOG channel
  selector. Visible in `find` but no `.meta` documentation.

Files that switchd uses but writes to the **real** filesystem (not FUSE):
- `/var/run/switchd.pid`  — pid file
- `/var/run/switchd.ready` — readiness flag (touched after init complete)
- `/var/run/switchd.restart` — restart-request flag
- `/etc/cumulus/switchd.conf` — startup config file (parsed by
  `FUN_10005eac`, which then populates the FUSE tree via sfs_register)

The relationship between the conf file and FUSE: **the conf file is the
initial-state loader**. Every `key=value` line in `/etc/cumulus/switchd.conf`
maps directly to a FUSE path; writing to the FUSE path overrides the
conf file at runtime, but won't survive restart.

---

## 12. Build-server breadcrumbs

The binary contains five embedded source-file paths that reveal the
Cumulus 2.5 build tree:

- `/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/lib/sfs/sfs.c`
- `/work/monster-07/.../switchd/switchd.c`
- `/work/monster-07/.../lib/utils/log.c`
- `/work/monster-07/.../lib/utils/hash.c`
- `/work/monster-07/.../switchd/route.c`

So the lib tree is:

```
CumulusLinux-2.5_br_BUILD_powerpc/
    lib/
        sfs/     <- the FUSE filesystem (this doc)
        utils/   <- log.c, hash.c — base helpers
    switchd/
        switchd.c  <- main()
        route.c    <- where the resync workers come from
```

---

## 13. Implications for EdgeNOS

To preserve Cumulus tool compatibility (`cl-acltool`, `clagd`, datapath
scripts, monitoring utilities), the EdgeNOS switchd-equivalent should:

1. **Mount its FUSE filesystem at `/cumulus/switchd/`** (literal path).
2. **Mirror the 295-entry `.meta` schema**. The schema format above is
   what every tool parses.
3. **Implement the same 19 fuse_operations callbacks** with the same
   semantics: `open` allocates a backing, `read` refreshes via the
   getter and serves from backing, `write` trampolines through a
   type-dispatched parser then calls a setter.
4. **Match the type ID numbering** (0=dir, 1=string, ..., 7=enum).
5. **Implement the `/ctrl/hal/resync` mark-and-sweep contract**: when
   you write `1`, all HAL state must be reconciled against HW (kernel
   route table) and any drift logged + corrected.
6. **Support `/ctrl/netlink/resync` and `/ctrl/resync`** the same way.
7. **Generate `.meta` automatically** from the registered entries —
   don't hand-maintain it.

The captured schema in `full-snapshot/switchd_snapshot/.meta` is the
authoritative blueprint.

---

## 14. Key symbol cross-reference

| Symbol | Address | Role |
|---|---|---|
| `fuse_operations` struct | `0x11819868` | 19 callbacks populated |
| `sfs_root` (root entry ptr) | `DAT_11e45f94` | global tree root |
| `sfs_register` wrapper | `FUN_1004bf0c` | public API (120B) |
| `sfs_register` impl | `FUN_100493c0` | hash-insert |
| `sfs_lookup` | `FUN_10048bd0` | path → entry |
| `sfs_find_backing` | `FUN_1004965c` | fh → backing |
| `sfs_format_value` | `FUN_10049d98` | type-keyed reader (1228B) |
| `sfs_parse_value` | `FUN_1004a428` | type-keyed writer (1736B) |
| `sfs_setup` (fuse_new caller) | `FUN_1004b638` | mount entry |
| `sfs_teardown` (fuse_unmount) | `FUN_1004b924` | unmount |
| getattr | `FUN_100496e4` | (376B) |
| read | `FUN_1004a264` | (452B) |
| write (trampoline) | `FUN_1004abb4` | (124B) |
| write (real) | `FUN_1004aaf0` | (196B) |
| readdir | `FUN_1004985c` | (272B) |
| open | `FUN_10049b88` | (332B) |
| release | `FUN_10049cd4` | (196B) |
| `/ctrl/hal/resync` setter | `FUN_1002348c` | (228B) |
| resync worker A (clear) | `FUN_10023444` | (72B) |
| resync worker B (sync) | `FUN_100231e0` | (612B) |
| resync worker C (sweep) | `FUN_10023570` | (304B) |
| `interface_mode` register fn | `FUN_1000e958` | (224B, per-port) |
| `interface_mode` getter | `FUN_1000e890` | (100B) — calls HAL |
| `interface_mode` setter | `FUN_1000e8f4` | (100B) — calls HAL |
| storm_control register fn | `FUN_1000ead4` | (per-port, 3× sfs_register) |
| `interface_mode` enum table | `0x11819028` | 15 entries |
| conf-file → SFS bridge | `FUN_10005eac` | parses switchd.conf |

---

*Reverse-engineered from Cumulus Linux 2.5.0 switchd binary (PowerPC,
big-endian, stripped). Verified against live `.meta` schema captured
from chassis 10.1.1.212 on 2013-06-01.*
