/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "VMPI.h"

#include <mach/mach.h>
#include <mach/mach_time.h>

// Call VMPI_getPerformanceFrequency() once to initialize its cache; avoids thread safety issues.
static uint64_t unused_value = VMPI_getPerformanceFrequency();

uint64_t VMPI_getPerformanceFrequency()
{
    // *** NOTE ABOUT THREAD SAFETY ***
    //
    // These statics ought to be safe because they are initialized by a call at startup
    // (see lines above this function), before any AvmCores are created.
    
    static mach_timebase_info_data_t info;
    static uint64_t frequency = 0;
    if ( frequency == 0 ) {
        (void) mach_timebase_info(&info);
        frequency = (uint64_t) ( 1e9 / ((double) info.numer / (double) info.denom) );
    }
    return frequency;
}

uint64_t VMPI_getPerformanceCounter()
{
    return mach_absolute_time();
}

static size_t computePagesize()
{
    /*  Bug 3944609, We are calculating the number of private pages and then multiplying them with pageSize. Now for 64 bit the page size returned is 16K which is wrong, where as in AVMPI_getPrivateResidentPageCount() we are calculating the page numbers of size 4K.
        one of the way to find the page size by looking into size of a vm
     
        size vm_size_t 2326528
        info vm_region_top_info_data_t
        obj_id unsigned int 1920607759
        ref_count unsigned int 12
        private_pages_resident unsigned int 0
        shared_pages_resident unsigned int 568
        share_mode unsigned char '' '’
     
        We can see the size of this VM section is 2326528 which is equal to (private_pages_resident + shared_pages_resident)* 4*1024.  Here we are calculating the page number of size 4K by divinding the vm size to total number of private pages and shared pasges. However this approach is not working in case of HMAOT, hence hardcoding the page size to 4K for iOS 64 bit as currently I don't find any suitable way for the same. 
     
      In case of HMAOT :
        (private_pages_resident + shared_pages_resident)* 4*1024 > vm_size
     
     */
    
long pagesize = -1;
#if defined(VMCFG_64BIT) && defined(VMCFG_ARM) && defined(FR_SDK_COCOA_TOUCH)
    pagesize = 4096;
#else
    pagesize = sysconf(_SC_PAGESIZE);
#endif
    
    // MacOS X 10.1 needs the extra check
    if (pagesize == -1)
        pagesize = 4096;
    return size_t(pagesize);

}

// Private to VMPI_getVMPageSize; DO NOT REFERENCE THIS VARIABLE ELSEWHERE.
// Always call VMPI_getVMPageSize, even inside this file.

static size_t pagesize = computePagesize();

size_t VMPI_getVMPageSize()
{
    return pagesize;
}
