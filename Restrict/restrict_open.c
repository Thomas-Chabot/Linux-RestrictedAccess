/* Using the LD_PRELOAD mechanism, overwrites various controls to open a file
     to check first that the file can be opened. */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "can_access.h"

int open(const char *pathname, int flags, ...)
{
    static int (*_open)(const char *, int, mode_t) = NULL;
    mode_t mode;
    va_list vl;
    va_start(vl, flags);
    mode = va_arg(vl, mode_t);
    va_end(vl);

    if (!_open) {
        _open = dlsym(RTLD_NEXT, "open");
    }
    if (can_open(pathname)) {
        return _open(pathname, flags, mode);
    } else {
        return -1;
    }
}

int open64(const char *pathname, int flags, ...)
{
    static int (*_open64)(const char *, int, mode_t) = NULL;
    mode_t mode;
    va_list vl;
    va_start(vl, flags);
    mode = va_arg(vl, mode_t);
    va_end(vl);

    if (!_open64) {
        _open64 = dlsym(RTLD_NEXT, "open64");
    }
    if (can_open(pathname)) {
        return _open64(pathname, flags, mode);
    } else {
        return -1;
    }
}

FILE *fopen(const char *pathname, const char *mode)
{
    static FILE *(*_fopen)(const char *, const char *) = NULL;

    if (!_fopen) {
        _fopen = dlsym(RTLD_NEXT, "fopen");
    }
    if (can_open(pathname)) {
        return _fopen(pathname, mode);
    } else {
        return NULL;
    }
}

int execve(const char *filename, char *const argv[], char *const envp[])
{
    static int (*_execve)(const char *, char *const argv[], char *const envp[]);

    if (!_execve) {
        _execve = dlsym(RTLD_NEXT, "execve");
    }
    if (can_open(filename)) {
        return _execve(filename, argv, envp);
    } else {
        return -1;
    }
}

int execvp(const char *filename, char *const argv[])
{
    static int (*_execvp)(const char *, char *const argv[]);

    if (!_execvp) {
        _execvp = dlsym(RTLD_NEXT, "execvp");
    }
    if (can_open(filename)) {
        return _execvp(filename, argv);
    } else {
        return -1;
    }
}

int execv(const char *filename, char *const argv[])
{
    static int (*_execv)(const char *, char *const argv[]);

    if (!_execv) {
        _execv = dlsym(RTLD_NEXT, "execv");
    }
    if (can_open(filename)) {
        return _execv(filename, argv);
    } else {
        return -1;
    }
}

// These are stat() and stat64() functions, that internally in GNU libc() are
// implemented as __xstat and __xstat64. See:
// http://stackoverflow.com/questions/5478780/c-and-ld-preload-open-and-open64-calls-intercepted-but-not-stat64

int __xstat(int x, const char *filename, struct stat *st)
{
    static int (*__xstat2)(int x, const char *, struct stat *);

    if (!__xstat2) {
        __xstat2 = dlsym(RTLD_NEXT, "__xstat");
    }
    if (can_open(filename)) {
        return __xstat2(x, filename, st);
    } else {
        return -1;
    }
}

int __xstat64(int x, const char *filename, struct stat64 *st)
{
    static int (*__xstat642)(int x, const char *, struct stat64 *);

    if (!__xstat642) {
        __xstat642 = dlsym(RTLD_NEXT, "__xstat64");
    }

    if (can_open(filename)) {
        return __xstat642(x, filename, st);
    } else {
        return -1;
    }
}
/*
int access(const char *pathname, int mode)
{
    static int (*_access)(const char *pathname, int mode);

    if (!_access) {
        _access = dlsym(RTLD_NEXT, "access");
    }

    if (can_open(pathname)) {
        return _access(pathname, mode);
    } else {
        return -1;
    }
}
*/
