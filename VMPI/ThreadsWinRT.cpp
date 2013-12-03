/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "VMPI.h"
#include "VMAssert.h"

// std
#include <thread>
#include <map>
#include <mutex>

// We make an assumption that using fiber local storage is equivalent of using thread local storage.
#ifndef FLS_OUT_OF_INDEXES
    #define FLS_OUT_OF_INDEXES (DWORD)0xFFFFFFFF
#endif

bool VMPI_tlsCreate(uintptr_t* tlsId)
{
    DWORD id = FlsAlloc(NULL);
    *tlsId = (uintptr_t)id;
    return (id != FLS_OUT_OF_INDEXES);
}

void VMPI_tlsDestroy(uintptr_t tlsId)
{
    FlsFree((DWORD)tlsId);
}

/*
The std::thread API does not use thread ids in the API unlike when using pthreads or win32 threads for example.
Std::threads are objects. It is not possible to get std::thread object for "current thread" for example.
Once we create a new std::thread, we get its id (which is an object as well) and then use a special
hash map (which is defined by std API) to get an unique identifier for the thread, type if size_t.
This is used as the thread type in the vmpi API. A look up is done whenever we need to access a thread that
the vm has created earlier.

It is not possible to call join, detach for threads that the vm did not create (for example the main thread)
- we don't know their ids. Luckily by reading the code, the vm does not try to do such a thing.

To return something from VMPI_currentThread we return hash of std::this_thread::get_id().
To return something from VMPI_nullThread we return hash of an uninitialized std::thread::id object. Returning 0 might work too.

TODO: test a bit so that the Ids we get are unique.
*/
std::map<size_t, std::thread*> g_vmpiThreadMap;
std::mutex g_vmpiThreadMapMutex;
#define THREAD_PAIR size_t, std::thread*

std::thread* getThread(vmpi_thread_t thread)
{
	// NOTE: g_vmpiThreadMapMutex has to be locked at this point!
	std::map<THREAD_PAIR>::iterator it;

	it = g_vmpiThreadMap.find(thread);
	if(it == g_vmpiThreadMap.end())
	{
		// This should never happen
		assert(false); 
		return NULL;
	}

	std::thread* th = it->second;
	return th;
}

size_t getThreadId(std::thread* thread)
{
	std::hash<std::thread::id> hash;
	return hash( thread->get_id() );
}

bool VMPI_threadCreate(vmpi_thread_t* thread, vmpi_thread_attr_t* attr, vmpi_thread_start_t start_fn, vmpi_thread_arg_t arg)
{
	// To do: support attributes such as priority if possible

	std::lock_guard<std::mutex> lock(g_vmpiThreadMapMutex);

	std::thread* newThread = new std::thread(start_fn, arg);
	size_t threadId = getThreadId(newThread);

	std::pair<std::map<THREAD_PAIR>::iterator, bool> ret;
	ret = g_vmpiThreadMap.insert( std::pair<THREAD_PAIR>(threadId, newThread) );

	// For some reason we could not insert. Maybe the id existed already?
	if(ret.second == false)
	{
		// This should never happen.
		assert(false);
		return false;
	}

	*thread = threadId;
	return true;
}

// Used by vmbase::VMThread::startInternal - in other words by threads created with VMPI_createThread.
bool VMPI_threadDetach(vmpi_thread_t thread)
{
	// Note! For some reason they have not implemented detach on win32. However it is implemented in ThreadsPosix.cpp.

	std::lock_guard<std::mutex> lock(g_vmpiThreadMapMutex);

	std::thread* th = getThread(thread);
	if(th)
	{
		g_vmpiThreadMap.erase(thread);
		th->detach();
		delete th;
		return true;
	} else
	{
		return false;
	}
}

// Used by avmplus::MostlyonBlockingChannel in Channels.cpp.
void VMPI_threadSleep(int32_t timeout_millis)
{
	std::this_thread::sleep_for( std::chrono::milliseconds(timeout_millis) );
}

// Actually VMPI_threadJoin is not called by the vm at the moment, so comment out:
/*
void VMPI_threadJoin(vmpi_thread_t thread)
{
	std::lock_guard<std::mutex> lock(g_vmpiThreadMapMutex);

	std::thread* th = getThread(thread);
	if(th)
	{
		th->join();
	}
}
*/

// VMPI_condVarInit happens to be in win32-platform.h.

void VMPI_condVarWait(vmpi_condvar_t* condvar, vmpi_mutex_t* mutex)
{
	SleepConditionVariableCS(condvar, mutex, INFINITE);
}

bool VMPI_condVarTimedWait(vmpi_condvar_t* condvar, vmpi_mutex_t* mutex, int32_t timeout_millis)
{
	return SleepConditionVariableCS(condvar, mutex, timeout_millis) == 0;
}

void VMPI_condVarBroadcast(vmpi_condvar_t* condvar)
{
	WakeAllConditionVariable(condvar);
}

void VMPI_condVarSignal(vmpi_condvar_t* condvar)
{
	WakeConditionVariable(condvar);
}

bool VMPI_threadAttrInit(vmpi_thread_attr_t* attr)
{
    attr->stackSize = VMPI_threadAttrDefaultStackSize();
    attr->guardSize = VMPI_threadAttrDefaultGuardSize();
    attr->priority = THREAD_PRIORITY_NORMAL;
    return true;
}

bool VMPI_threadAttrDestroy(vmpi_thread_attr_t* attr)
{
    (void)attr;
    return true;
}

bool VMPI_threadAttrSetGuardSize(vmpi_thread_attr_t* attr, size_t size)
{
    attr->guardSize = size;
    return true;
}

bool VMPI_threadAttrSetStackSize(vmpi_thread_attr_t* attr, size_t size)
{
    attr->stackSize = size;
    return true;
}

void VMPI_threadAttrSetPriorityLow(vmpi_thread_attr_t* attr)
{
    attr->priority = THREAD_PRIORITY_BELOW_NORMAL;
}

void VMPI_threadAttrSetPriorityNormal(vmpi_thread_attr_t* attr)
{
    attr->priority = THREAD_PRIORITY_NORMAL;
}

void VMPI_threadAttrSetPriorityHigh(vmpi_thread_attr_t* attr)
{
    attr->priority = THREAD_PRIORITY_ABOVE_NORMAL;
}

size_t VMPI_threadAttrDefaultGuardSize()
{
    // It will be a single page.
    // The SetThreadStackGuarantee API isn't available so we can't change it
    // from the default.
    // http://msdn.microsoft.com/en-us/library/8cxs58a6%28vs.71%29.aspx
    return VMPI_getVMPageSize();
}

size_t VMPI_threadAttrDefaultStackSize()
{
    // FIXME: bug 609822 Is it possible to implement VMPI_threadAttrDefaultStackSize on win32?
    //
    // Stack size is set in the linker. The default is 1MB:
    // http://msdn.microsoft.com/en-us/library/8cxs58a6%28vs.71%29.aspx
    // But can we find this out programmatically? There doesn't appear to be an API:
    // http://msdn.microsoft.com/en-us/library/ms686774%28v=VS.85%29.aspx
    return 1024 * 1024;
}
