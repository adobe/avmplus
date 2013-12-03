/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "MMgc.h"

#ifdef MMGC_MEMORY_PROFILER
/*
It may not be possible to implement this feature in Windows Store apps, at least by using the same APIs as before.

You can see win32 implementation in SpyUtilsWin.cpp.
*/

void AVMPI_spyCallback()
{
}

bool AVMPI_spySetup()
{
    return false;
}

void AVMPI_spyTeardown()
{
}

bool AVMPI_hasSymbols()
{
    return false;
}

#endif //MMGC_MEMORY_PROFILER
