/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef __GCDebug__
#define __GCDebug__

#include "GCTypes.h"

namespace MMgc
{
    void GCDebugIndent(size_t count);

#if defined(GCDEBUG) && !defined(DEBUG) && !defined(_DEBUG)

    // If debug checks are enabled only in MMgc via GCDEBUG,
    // we need our own reporting infrastructure.  Otherwise,
    // we define macros that redirect to AvmAssert functionality.

    void GCDebugMsg(const char* msg, bool debugBreak);
    void GCDebugMsg(bool debugBreak, const char* format, ...);

    #define GCAssertMsg(condition, message)         \
        do {                                        \
            if (!(condition))                       \
                MMgc::GCDebugMsg((message), true);  \
        } while (0)

    #define GCAssert(condition) \
        _GCAssert((condition), __LINE__,__FILE__)

    #define _GCAssert(condition, line_, file_) \
        __GCAssert((condition), line_, file_)

    #define __GCAssert(condition, line_, file_) \
        do { GCAssertMsg((condition), \
                          "Assertion failed: \"" #condition "\" (" #file_ ":" #line_ ")\n"); \
        } while (0)

#else

    #define GCAssert         AvmAssert
    #define GCAssertMsg      AvmAssertMsg
    #define GCDebugMsg       avmplus::AvmDebugMsg

#endif

}

#endif /* __GCDebug__ */
