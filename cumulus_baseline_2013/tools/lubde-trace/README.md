# LUBDE LD_PRELOAD trace shim (PARTIAL — does not work for daemonized switchd)

Intercepts ioctl() and logs the LUBDE opcode + buffer contents for every
LUBDE_* call switchd issues. Built for PowerPC32 BE.

## Build
```
docker run --rm --entrypoint bash -v $(pwd):/work edgenos-builder:latest \
  -c 'powerpc-linux-gnu-gcc -shared -fPIC -O2 -U_FORTIFY_SOURCE \
       -fno-stack-protector -static-libgcc \
       -o /work/lubde_trace.so /work/lubde_trace.c'
```

## Deploy
```
scp lubde_trace.so root@chassis:/usr/local/lib/   # MUST be root-owned for sudo'd procs
```

## Use
```
LD_PRELOAD=/usr/local/lib/lubde_trace.so \
LUBDE_TRACE_LOG=/var/log/lubde.log \
  /usr/sbin/switchd -d -lic /etc/cumulus/.license.txt
```

## Known issues (as of 2026-05-11)

The shim works for simple programs (`ls`, `cat`, `switchd -V`) but does
NOT successfully intercept ioctls in fully-daemonized `switchd -d`. The
shim's constructor doesn't fire in the daemonized child for unknown
reasons. Investigated:
- ✗ glibc version mismatch (fixed: use `syscall()` instead of `dlsym`)
- ✗ Wrong opcode mask (fixed: `>= 0x20004c00 && <= 0x20004c1f`)
- ✗ fd closed during daemonization (fixed: lazy reopen)
- ✗ LD_PRELOAD ignored for non-root-owned libs under sudo
  (fixed: chown root:root + place in /usr/local/lib)
- ✗ Still no markers in daemonized switchd → switchd's daemonization
  appears to scrub LD_PRELOAD from env, OR re-execs without it,
  OR something else is going on.

Possible next steps not yet tried:
1. Use `/etc/ld.so.preload` (system-wide, can't be stripped by env scrubbing)
2. Add tracing inside the BDE kernel module via `printk` patch + recompile
3. Use gdb hardware breakpoint on `ioctl@plt` in switchd (risky per
   feedback_gdb_switchd memory)
4. Try ltrace if installable
5. Patch a verbose strace for ioctl-buffer-dumping
