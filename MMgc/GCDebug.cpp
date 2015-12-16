/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "MMgc.h"

namespace MMgc
{
    void GCDebugIndent(size_t count)
    {
	#ifdef GCDEBUG
        while (count > 10) {
            VMPI_debugLog("          ");
            count -= 10;
        }
        while (count > 0) {
            VMPI_debugLog(" ");
            count--;
        }
	#else
        (void)count;
	#endif
    }

#if defined(GCDEBUG) && !defined(DEBUG) && !defined(_DEBUG)

    // If debug checks are enabled only in MMgc via GCDEBUG,
    // we need our own reporting infrastructure.  Otherwise,
    // we define macros that redirect to AvmAssert functionality.

    void GCDebugMsg(bool debugBreak, const char* format, ...)
    {
        char buf[1024];
        va_list args;
        va_start(args, format);

        VMPI_vsnprintf(buf, sizeof(buf), format, args);
        // Belt and suspenders, remove when we're sure VMPI_vsnprintf is completely reliable
        buf[sizeof(buf)-2] = '\n';
        buf[sizeof(buf)-1] = '\0';
        va_end(args);
        GCDebugMsg(buf, debugBreak);
    }

    void GCDebugMsg(const char* p, bool debugBreak)
    {
        VMPI_debugLog(p);
        if(debugBreak)
            VMPI_debugBreak();
    }

#endif

}
