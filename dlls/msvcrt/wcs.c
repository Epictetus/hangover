/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu_wcscat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t count;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

INT CDECL MSVCRT_wcscat_s(WCHAR *dst, size_t count, const WCHAR *src)
{
    struct qemu_wcscat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCAT_S);
    call.dst = (uint64_t)dst;
    call.count = count;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscat_s(struct qemu_syscall *call)
{
    struct qemu_wcscat_s *c = (struct qemu_wcscat_s *)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcscat_s(QEMU_G2H(c->dst), c->count, QEMU_G2H(c->src));
}

#endif

struct qemu_wcscpy
{
    struct qemu_syscall super;
    uint64_t dst, src;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT_wcscpy(WCHAR *dst, const WCHAR *src)
{
    struct qemu_wcscpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCPY);
    call.dst = (uint64_t)dst;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_wcscpy(struct qemu_syscall *call)
{
    struct qemu_wcscpy *c = (struct qemu_wcscpy *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcscpy(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

struct qemu_wcscpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_wcscpy_s(WCHAR *dst, size_t size, const WCHAR *src)
{
    struct qemu_wcscpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCPY_S);
    call.dst = (uint64_t)dst;
    call.size = size;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscpy_s(struct qemu_syscall *call)
{
    struct qemu_wcscpy_s *c = (struct qemu_wcscpy_s *)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcscpy_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src));
}

#endif

struct qemu_wcsncmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_wcsncmp(const wchar_t *str1, const wchar_t *str2, size_t count)
{
    struct qemu_wcsncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCMP);
    call.str1 = (uint64_t)str1;
    call.str2 = (uint64_t)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsncmp(struct qemu_syscall *call)
{
    struct qemu_wcsncmp *c = (struct qemu_wcsncmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcsncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu_wcsstr
{
    struct qemu_syscall super;
    uint64_t str, sub;
};

#ifdef QEMU_DLL_GUEST

const WCHAR * __cdecl MSVCRT_wcsstr(const WCHAR *str, const WCHAR *sub)
{
    struct qemu_wcsstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSSTR);
    call.str = (uint64_t)str;
    call.sub = (uint64_t)sub;

    qemu_syscall(&call.super);

    return (const wchar_t *)call.super.iret;
}

#else

void qemu_wcsstr(struct qemu_syscall *call)
{
    struct qemu_wcsstr *c = (struct qemu_wcsstr *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcsstr(QEMU_G2H(c->str), QEMU_G2H(c->sub)));
}

#endif

struct qemu_wcstod
{
    struct qemu_syscall super;
    uint64_t str, end;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_wcstod(const WCHAR *str, WCHAR **end)
{
    struct qemu_wcstod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOD);
    call.str = (uint64_t)str;
    call.end = (uint64_t)end;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_wcstod(struct qemu_syscall *call)
{
    struct qemu_wcstod *c = (struct qemu_wcstod *)call;
    WCHAR *end;
    WINE_TRACE("\n");

    c->super.dret = p_wcstod(QEMU_G2H(c->str), c->end ? &end : NULL);

    if (c->end)
        *(uint64_t *)QEMU_G2H(c->end) = QEMU_H2G(end);
}

#endif
struct qemu__snwprintf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__snwprintf(WCHAR *str, unsigned int len, const WCHAR *format, ...)
{
    struct qemu_wcscpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SNWPRINTF);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__snwprintf(struct qemu_syscall *call)
{
    struct qemu__snwprintf *c = (struct qemu__snwprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif
