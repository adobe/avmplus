/*
 * Copyright (C) 2007, 2008, 2010, 2012 Apple Inc. All rights reserved.
 * Copyright (C) 2007 Justin Haygood (jhaygood@reaktix.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef Atomics_h
#define Atomics_h

#include "CPU.h"

#if defined(_MSC_VER) && (_MSC_VER < 1600)
	#ifndef _STDINT
	#define _STDINT
	#ifndef RC_INVOKED
	#include <yvals.h>

	/* NB: assumes
		byte has 8 bits
		long is 32 bits
		pointer can convert to and from long long
		long long is longest type
	 */

	_C_STD_BEGIN
			/* TYPE DEFINITIONS */
	typedef short int16_t;
	typedef int int32_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;

	typedef signed char int_least8_t;
	typedef short int_least16_t;
	typedef int int_least32_t;

	typedef unsigned char uint_least8_t;
	typedef unsigned short uint_least16_t;
	typedef unsigned int uint_least32_t;

	typedef char int_fast8_t;
	typedef int int_fast16_t;
	typedef int int_fast32_t;

	typedef unsigned char uint_fast8_t;
	typedef unsigned int uint_fast16_t;
	typedef unsigned int uint_fast32_t;

	#ifndef _INTPTR_T_DEFINED
	 #define _INTPTR_T_DEFINED
	 #ifdef _WIN64
	typedef __int64 intptr_t;
	 #else /* _WIN64 */
	typedef _W64 int intptr_t;
	 #endif /* _WIN64 */
	#endif /* _INTPTR_T_DEFINED */

	#ifndef _UINTPTR_T_DEFINED
	 #define _UINTPTR_T_DEFINED
	 #ifdef _WIN64
	typedef unsigned __int64 uintptr_t;
	 #else /* _WIN64 */
	typedef _W64 unsigned int uintptr_t;
	 #endif /* _WIN64 */
	#endif /* _UINTPTR_T_DEFINED */

	typedef _Longlong int64_t;
	typedef _ULonglong uint64_t;

	typedef _Longlong int_least64_t;
	typedef _ULonglong uint_least64_t;

	typedef _Longlong int_fast64_t;
	typedef _ULonglong uint_fast64_t;

	typedef _Longlong intmax_t;
	typedef _ULonglong uintmax_t;

			/* LIMIT MACROS */
	#define INT8_MIN	(-0x7f - _C2)
	#define INT16_MIN	(-0x7fff - _C2)
	#define INT32_MIN	(-0x7fffffff - _C2)

	#define INT8_MAX	0x7f
	#define INT16_MAX	0x7fff
	#define INT32_MAX	0x7fffffff
	#define UINT8_MAX	0xff
	#define UINT16_MAX	0xffff
	#define UINT32_MAX	0xffffffff

	#define INT_LEAST8_MIN		(-0x7f - _C2)
	#define INT_LEAST16_MIN		(-0x7fff - _C2)
	#define INT_LEAST32_MIN		(-0x7fffffff - _C2)

	#define INT_LEAST8_MAX		0x7f
	#define INT_LEAST16_MAX		0x7fff
	#define INT_LEAST32_MAX		0x7fffffff
	#define UINT_LEAST8_MAX		0xff
	#define UINT_LEAST16_MAX	0xffff
	#define UINT_LEAST32_MAX	0xffffffff

	#define INT_FAST8_MIN		(-0x7f - _C2)
	#define INT_FAST16_MIN		(-0x7fff - _C2)
	#define INT_FAST32_MIN		(-0x7fffffff - _C2)

	#define INT_FAST8_MAX		0x7f
	#define INT_FAST16_MAX		0x7fff
	#define INT_FAST32_MAX		0x7fffffff
	#define UINT_FAST8_MAX		0xff
	#define UINT_FAST16_MAX		0xffff
	#define UINT_FAST32_MAX		0xffffffff

	 #if _INTPTR == 0 || _INTPTR == 1
	#define INTPTR_MAX			0x7fffffff
	#define INTPTR_MIN			(-INTPTR_MAX - _C2)
	#define UINTPTR_MAX			0xffffffff

	 #else /* _INTPTR == 2 */
	#define INTPTR_MIN			(-_LLONG_MAX - _C2)
	#define INTPTR_MAX			_LLONG_MAX
	#define UINTPTR_MAX			_ULLONG_MAX
	#endif /* _INTPTR */

	#define INT8_C(x)	(x)
	#define INT16_C(x)	(x)
	#define INT32_C(x)	((x) + (INT32_MAX - INT32_MAX))

	#define UINT8_C(x)	(x)
	#define UINT16_C(x)	(x)
	#define UINT32_C(x)	((x) + (UINT32_MAX - UINT32_MAX))

	#ifdef _WIN64
	 #define PTRDIFF_MIN		INT64_MIN
	 #define PTRDIFF_MAX		INT64_MAX
	#else /* _WIN64 */
	 #define PTRDIFF_MIN		INT32_MIN
	 #define PTRDIFF_MAX		INT32_MAX
	#endif /* _WIN64 */

	#define SIG_ATOMIC_MIN	INT32_MIN
	#define SIG_ATOMIC_MAX	INT32_MAX

	#ifndef SIZE_MAX
	 #ifdef _WIN64
	  #define SIZE_MAX		UINT64_MAX
	 #else /* _WIN64 */
	  #define SIZE_MAX		UINT32_MAX
	 #endif /* _WIN64 */
	#endif /* SIZE_MAX */

	#define WCHAR_MIN	0x0000
	#define WCHAR_MAX	0xffff

	#define WINT_MIN	0x0000
	#define WINT_MAX	0xffff

	 #define INT64_MIN	(-0x7fffffffffffffff - _C2)
	 #define INT64_MAX	0x7fffffffffffffff
	 #define UINT64_MAX	0xffffffffffffffffU

	 #define INT_LEAST64_MIN	(-0x7fffffffffffffff - _C2)
	 #define INT_LEAST64_MAX	0x7fffffffffffffff
	 #define UINT_LEAST64_MAX	0xffffffffffffffffU

	 #define INT_FAST64_MIN		(-0x7fffffffffffffff - _C2)
	 #define INT_FAST64_MAX		0x7fffffffffffffff
	 #define UINT_FAST64_MAX	0xffffffffffffffffU

	 #define INTMAX_MIN		(-0x7fffffffffffffff - _C2)
	 #define INTMAX_MAX		0x7fffffffffffffff
	 #define UINTMAX_MAX	0xffffffffffffffffU

	#define INT64_C(x)		((x) + (INT64_MAX - INT64_MAX))
	#define UINT64_C(x)		((x) + (UINT64_MAX - UINT64_MAX))
	#define INTMAX_C(x)		INT64_C(x)
	#define UINTMAX_C(x)	UINT64_C(x)
	_C_STD_END
	#endif /* RC_INVOKED */
	#endif /* _STDINT */

	 #if defined(_STD_USING)
	using _CSTD int8_t; using _CSTD int16_t;
	using _CSTD int32_t; using _CSTD int64_t;

	using _CSTD uint8_t; using _CSTD uint16_t;
	using _CSTD uint32_t; using _CSTD uint64_t;

	using _CSTD int_least8_t; using _CSTD int_least16_t;
	using _CSTD int_least32_t;  using _CSTD int_least64_t;
	using _CSTD uint_least8_t; using _CSTD uint_least16_t;
	using _CSTD uint_least32_t; using _CSTD uint_least64_t;

	using _CSTD intmax_t; using _CSTD uintmax_t;

	using _CSTD uintptr_t;
	using _CSTD intptr_t;

	using _CSTD int_fast8_t; using _CSTD int_fast16_t;
	using _CSTD int_fast32_t; using _CSTD int_fast64_t;
	using _CSTD uint_fast8_t; using _CSTD uint_fast16_t;
	using _CSTD uint_fast32_t; using _CSTD uint_fast64_t;
	 #endif /* defined(_STD_USING) */
#else
	#include <stdint.h>
#endif

#if COMPILER(MSVC)
#include <windows.h>
#endif

#if defined(THREAD_SANITIZER)
#include <sanitizer/tsan_interface_atomic.h>
#endif

#if defined(ADDRESS_SANITIZER)
#include <sanitizer/asan_interface.h>
#endif

namespace WTF {

#if COMPILER(MSVC)

ALWAYS_INLINE int atomicTestAndSetToOne(int volatile* ptr)
{
    int ret = InterlockedExchange(reinterpret_cast<long volatile*>(ptr), 1);
    //ASSERT(!ret || ret == 1);
    return ret;
}

ALWAYS_INLINE void atomicSetOneToZero(int volatile* ptr)
{
    //ASSERT(*ptr == 1);
    InterlockedExchange(reinterpret_cast<long volatile*>(ptr), 0);
}

#else

ALWAYS_INLINE int atomicTestAndSetToOne(int volatile* ptr)
{
    int ret = __sync_lock_test_and_set(ptr, 1);
    //ASSERT(!ret || ret == 1);
    return ret;
}

ALWAYS_INLINE void atomicSetOneToZero(int volatile* ptr)
{
    //ASSERT(*ptr == 1);
    __sync_lock_release(ptr);
}
#endif

} // namespace WTF

#endif // Atomics_h
