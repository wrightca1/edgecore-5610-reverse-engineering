/*
 * LD_PRELOAD shim — log every LUBDE ioctl with its argument buffer
 *
 * Robust against daemonization: opens log lazily on first/failing write.
 *
 * Build: powerpc-linux-gnu-gcc -shared -fPIC -O2 \
 *          -U_FORTIFY_SOURCE -fno-stack-protector -static-libgcc \
 *          -o lubde_trace.so lubde_trace.c
 * Use:   LD_PRELOAD=./lubde_trace.so LUBDE_TRACE_LOG=/var/log/lubde.log switchd ...
 */
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/time.h>

/* Captured log path so we survive switchd unsetting env */
static char log_path[256] = "/var/log/lubde-trace.log";
static int log_fd = -1;

__attribute__((constructor))
static void init(void) {
    const char *path = getenv("LUBDE_TRACE_LOG");
    if (path) {
        strncpy(log_path, path, sizeof(log_path) - 1);
        log_path[sizeof(log_path) - 1] = '\0';
    }
    /* Drop a marker file so we can see WHICH processes loaded the shim. */
    char marker[64];
    snprintf(marker, sizeof(marker), "/tmp/shim_pid_%d", (int) getpid());
    int mfd = open(marker, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (mfd >= 0) {
        const char *m = "shim loaded\n";
        ssize_t w = write(mfd, m, 12); (void) w;
        close(mfd);
    }
}

/* Robust log writer: opens fd lazily, reopens after EBADF (post-daemonize). */
static void log_write(const char *buf, int n) {
    for (int attempt = 0; attempt < 2; attempt++) {
        if (log_fd < 0) {
            log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (log_fd < 0) return;
        }
        ssize_t w = write(log_fd, buf, n);
        if (w >= 0) return;
        /* write failed — fd probably got closed; reset and retry once */
        log_fd = -1;
    }
}

static const char *opname(unsigned long cmd) {
    switch (cmd) {
    case 0x20004c00: return "VERSION";
    case 0x20004c01: return "GET_NUM_DEV";
    case 0x20004c02: return "GET_DEVICE";
    case 0x20004c03: return "PCI_CFG_PUT";
    case 0x20004c04: return "PCI_CFG_GET";
    case 0x20004c05: return "GET_DMA_INFO";
    case 0x20004c06: return "ENABLE_IRQ";
    case 0x20004c07: return "DISABLE_IRQ";
    case 0x20004c08: return "USLEEP";
    case 0x20004c09: return "WAIT_IRQ";
    case 0x20004c0a: return "PHYS_RD32";
    case 0x20004c0b: return "PHYS_WR32";
    case 0x20004c0c: return "GET_DEV_TYPE";
    case 0x20004c0d: return "SPI_READ";
    case 0x20004c0e: return "SPI_WRITE";
    case 0x20004c13: return "READ_REG";
    case 0x20004c14: return "WRITE_REG";
    case 0x20004c15: return "GET_PCI_BUS";
    case 0x20004c16: return "IRQ_MASK_SET";
    case 0x20004c1a: return "GET_DEV_RES";
    default: return "OTHER";
    }
}

int ioctl(int fd, unsigned long request, ...) {
    va_list ap;
    va_start(ap, request);
    void *arg = va_arg(ap, void *);
    va_end(ap);

    int is_lubde = (request >= 0x20004c00 && request <= 0x20004c1f);

    uint32_t pre[6] = {0};
    if (is_lubde && arg) memcpy(pre, arg, 24);

    int ret = (int) syscall(__NR_ioctl, fd, request, arg);

    if (is_lubde) {
        uint32_t post[6] = {0};
        if (arg) memcpy(post, arg, 24);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        char buf[512];
        int n = snprintf(buf, sizeof(buf),
            "%ld.%06ld fd=%d %-12s arg=%p pre=%08x,%08x,%08x,%08x,%08x,%08x post=%08x,%08x,%08x,%08x,%08x,%08x ret=%d\n",
            (long)tv.tv_sec, (long)tv.tv_usec, fd, opname(request), arg,
            pre[0], pre[1], pre[2], pre[3], pre[4], pre[5],
            post[0], post[1], post[2], post[3], post[4], post[5],
            ret);
        if (n > 0 && n < (int)sizeof(buf)) log_write(buf, n);
    }

    return ret;
}
