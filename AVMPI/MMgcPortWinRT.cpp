/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <windows.h>

#include "MMgc.h"

bool AVMPI_canMergeContiguousRegions()
{
    return false;
}

bool AVMPI_canCommitAlreadyCommittedMemory()
{
    return false;
}

bool AVMPI_useVirtualMemory()
{
    return false;
}

bool AVMPI_areNewPagesDirty()
{
    return false;
}

void* AVMPI_reserveMemoryRegion(void* /*address*/, size_t /*size*/)
{
	return NULL;
}

bool AVMPI_releaseMemoryRegion(void* /*address*/, size_t /*size*/)
{
    return false;
}

bool AVMPI_commitMemory(void* /*address*/, size_t /*size*/)
{
	return false;
}

bool AVMPI_decommitMemory(char* /*address*/, size_t /*size*/)
{
	return false;
}

void* AVMPI_allocateAlignedMemory(size_t size)
{
	void* mem = _aligned_malloc(size, VMPI_getVMPageSize());
	memset(mem, 0, size);
	return mem;
}

void AVMPI_releaseAlignedMemory(void* address)
{
	_aligned_free(address);
}

size_t AVMPI_getPrivateResidentPageCount()
{
    void* addr = 0;
    size_t bytes = 0;
    MEMORY_BASIC_INFORMATION info;
    while(true)
    {
        size_t ret = VirtualQuery(addr, &info, sizeof(MEMORY_BASIC_INFORMATION));
        if(ret == 0)
            break;

        if((info.State & MEM_COMMIT) && (info.Type & MEM_PRIVATE))
            bytes += info.RegionSize;

            addr = (void*) ((intptr_t)info.BaseAddress + info.RegionSize);
    }

    return bytes / VMPI_getVMPageSize();
}

void AVMPI_cleanStack(size_t amt)
{
    void *space = alloca(amt);
    if(space)
    {
        VMPI_memset(space, 0, amt);
    }
}

uintptr_t AVMPI_getThreadStackBase()
{
    MEMORY_BASIC_INFORMATION info;
    VirtualQuery(&info, &info, sizeof(MEMORY_BASIC_INFORMATION));
    return (uintptr_t)info.BaseAddress + info.RegionSize;
}

void *AVMPI_allocateCodeMemory(size_t /*nbytes*/)
{
	return NULL;
}

void AVMPI_freeCodeMemory(void* /*address*/, size_t /*nbytes*/)
{
}

void AVMPI_makeCodeMemoryExecutable(void* /*address*/, size_t /*nbytes*/, bool /*makeItSo*/)
{
}

#ifdef MMGC_MEMORY_PROFILER
/*
It may not be possible to implement this feature in Windows Store apps, at least by using the same APIs as before.

You can see win32 implementation in MMgcPortWin.cpp.
*/

bool AVMPI_captureStackTrace(uintptr_t* /*buffer*/, size_t /*bufferSize*/, uint32_t /*framesToSkip*/)
{
	return false;
}

bool AVMPI_getFileAndLineInfoFromPC(uintptr_t /*pc*/, char* /*filenameBuffer*/, size_t /*bufferSize*/, uint32_t* /*lineNumber*/)
{
	return false;
}

bool AVMPI_getFunctionNameFromPC(uintptr_t /*pc*/, char* /*buffer*/, size_t /*bufferSize*/)
{
	return false;
}

void AVMPI_setupPCResolution()
{
}

void AVMPI_desetupPCResolution()
{
}

bool AVMPI_isMemoryProfilingEnabled()
{
	return false;
}

#endif // MMGC_MEMORY_PROFILER
