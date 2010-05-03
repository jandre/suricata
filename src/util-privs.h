/* Copyright (c) 2010 Open Infomation Security Foundation */

/**
 * \author  Gurvinder Singh <gurvindersinghdahiya@gmail.com>
 *
 */

#ifndef _UTIL_PRIVS_H
#define	_UTIL_PRIVS_H

#define SC_CAP_NONE             0x01
#define SC_CAP_SYS_ADMIN        0x02
#define SC_CAP_SYS_RAW_IO       0x04
#define SC_CAP_IPC_LOCK         0x08
#define SC_CAP_NET_ADMIN        0x10
#define SC_CAP_NET_RAW          0x20
#define SC_CAP_NET_BIND_SERVICE 0x40
#define SC_CAP_NET_BROADCAST    0x80

#ifndef HAVE_LIBCAP_NG
#define SCDropCaps(...)
#define SCDropMainThreadCaps(...)
#else
#include "threadvars.h"
#include "util-debug.h"
#include <cap-ng.h>

/**Drop the previliges of the given thread tv, based on the thread cap_flags
 * which implies the capability requirement of the given thread. Initially all
 * caps are dropped and later, the required caps are set for the given thread
 */
void SCDropCaps(ThreadVars *tv);
/*
#define SCDropCaps(tv) ({ \
    capng_clear(CAPNG_SELECT_BOTH); \
    capng_apply(CAPNG_SELECT_BOTH); \
    if (tv->cap_flags & SC_CAP_IPC_LOCK) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_IPC_LOCK); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_IPC_LOCK has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_NET_ADMIN) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_NET_ADMIN); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_NET_ADMIN has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_NET_BIND_SERVICE) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_NET_BIND_SERVICE); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_NET_BIND_SERVICE has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_NET_BROADCAST) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_NET_BROADCAST); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_NET_BROADCAST has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_NET_RAW) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_NET_RAW); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_NET_RAW has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_SYS_ADMIN) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_SYS_ADMIN); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_SYS_ADMIN has been set", tv->name); \
    } \
    if (tv->cap_flags & SC_CAP_SYS_RAW_IO) { \
        capng_update(CAPNG_ADD, (capng_type_t) (CAPNG_EFFECTIVE | CAPNG_PERMITTED), CAP_SYS_RAWIO); \
        capng_apply(CAPNG_SELECT_CAPS); \
        SCLogDebug("For thread \"%s\" CAP_SYS_RAWIO has been set", tv->name); \
    } \
})
*/
void SCDropMainThreadCaps(uint32_t , uint32_t );

#endif /* HAVE_LIBCAP_NG */

int SCGetUserID(char *, char *, uint32_t *, uint32_t *);
int SCGetGroupID(char *, uint32_t *);

#endif	/* _UTIL_PRIVS_H */
