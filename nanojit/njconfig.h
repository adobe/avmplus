/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __njconfig_h__
#define __njconfig_h__

#include "avmplus.h"

// Do not include nanojit.h here; this file should be usable without it.

#ifdef FEATURE_NANOJIT

namespace nanojit
{
    /**
     * A struct used to configure the assumptions that Assembler can make when
     * generating code. The ctor will fill in all fields with the most reasonable
     * values it can derive from compiler flags and/or runtime detection, but
     * the embedder is free to override any or all of them as it sees fit.
     * Using the ctor-provided default setup is guaranteed to provide a safe
     * runtime environment (though perhaps suboptimal in some cases), so an embedder
     * should replace these values with great care.
     *
     * Note that although many fields are used on only specific architecture(s),
     * this struct is deliberately declared without ifdef's for them, so (say) ARM-specific
     * fields are declared everywhere. This reduces build dependencies (so that this
     * files does not require nanojit.h to be included beforehand) and also reduces
     * clutter in this file; the extra storage space required is trivial since most
     * fields are single bits.
     */
    struct Config
    {
    public:
        // fills in reasonable default values for all fields.
        Config();

        // ARM architecture to assume when generate instructions for (currently, 4 <= arm_arch <= 7)
        uint8_t arm_arch;

        // If true, use CSE.
        uint32_t cseopt:1;

        // If true, use full-range addressing for branches even when a short branch will suffice (x86-64 only)
        uint32_t force_long_branch:1;

        // Can we use SSE2 instructions? (x86-only)
        uint32_t i386_sse2:1;

        // Can we use SSE3 instructions? (x86-only)
        uint32_t i386_sse3:1;

        // Can we use SSE4.1 instructions? (x86 only)
        uint32_t i386_sse41:1;

        // Can we use cmov instructions? (x86-only)
        uint32_t i386_use_cmov:1;

        // Should we use a virtual stack pointer? (x86-only)
        uint32_t i386_fixed_esp:1;

        // Whether or not to generate VFP instructions. (ARM only)
        uint32_t arm_vfp:1;

        // @todo, document me
        uint32_t arm_show_stats:1;

        // If true, use softfloat for all floating point operations,
        // whether or not an FPU is present. (ARM only for now, but might also includes MIPS in the future)
        uint32_t soft_float:1;

        // If true, compiler will insert a random amount of space in between functions (x86-32 only)
        uint32_t harden_function_alignment:1;

        // If true, compiler will insert randomly choosen no-op instructions at random locations within a compiled method (x86-32 only)
        uint32_t harden_nop_insertion:1;

        // If true, compiler will attempt to minimize the ability of an attacker to control literal constants appearing in the code
        uint32_t harden_blind_constants:1;

		// Check protection flags when allocating memory for compiled code.
        uint32_t check_page_flags:1;

        inline bool
        use_cmov()
        {
#ifdef AVMPLUS_IA32
            return i386_use_cmov;
#else
            return true;
#endif
        }
    };


    /**
     * Abstract class for source of random numbers for JIT hardening.
     */

    // Moved here from Assembler.h so it can be used without including nanojit.h.
    // The header files are a mess and could stand some rationalization.

    class Noise
    {
        public:
            virtual ~Noise() {}
            // Produce a random signed integer in the range 0..maxValue, where maxValue > 0.
            virtual int32_t getValue(int32_t maxValue) = 0;
            // Produce a random 32-bit unsigned integer.
            virtual uint32_t getValue32() = 0;
    };

}

#endif // FEATURE_NANOJIT
#endif // __njconfig_h__
