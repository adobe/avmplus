/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __ThreadPool__
#define __ThreadPool__

#include "vmbase.h"

//
// Simple thread-pool.
//

//Need to have __stdcall in WIN to avoid __cdecl, and match the signature
#ifdef _WIN32
#define MY_STD_CALL __stdcall
#else
#define MY_STD_CALL
#endif

class ThreadPool
{
public:
    //
    // Describes a "Job" that can be queued to the ThreadPool
    //
    class Job {
    public:
        virtual ~Job() {}
        
    private:
        friend class ThreadPool;
        
        virtual void handler() = 0;
        virtual void destroy() { delete this; }
        Job* next_;
    };
    
    ThreadPool()
    : jobQueueBack_(0)
    , maxQueue_(0)
    , queueLength_(0)
    , stop_(false)
    , nRunning_(0)
    {}
    
    //
    // Starts the ThreadPool with the given number of threads and a maximum queue size.
    // Zero is a good length for the queue because you don't usually want to get out
    // ahead of the thread pool processing.
    //
    void start(unsigned nthreads, unsigned maxQueue = 0) {
        maxQueue_ = maxQueue;
        for (unsigned i = 0; i < nthreads; ++i) {
            vmpi_thread_t thread;
            VMPI_threadCreate(&thread, 0, threadBodyEnter, (vmpi_thread_arg_t)this);
        }
    }
    
    //
    // Signal the ThreadPool to shut down when processing is complete and wait for completion.
    //
    void stopAndWait() {
        SCOPE_LOCK_NAMED(locker, monitor_) {
            stop_ = true;
            locker.notifyAll();
            while (jobQueueBack_ || nRunning_ > 0)
                locker.wait();
        }
    }
    
    //
    // Enqueues a job. Job must be allocated with "new"
    //
    void enqueueJob(Job* job) {
        SCOPE_LOCK_NAMED(locker, monitor_) {
            while (queueLength_ > maxQueue_)
                locker.wait();
            queueLength_ += 1;
            if (jobQueueBack_) {
                job->next_ = jobQueueBack_->next_;
                jobQueueBack_->next_ = job;
            }
            else {
                job->next_ = job;
            }
            jobQueueBack_ = job;
            locker.notifyAll();
        }
    }
    
private:
    static vmpi_thread_rtn_t MY_STD_CALL threadBodyEnter(vmpi_thread_arg_t arg) {
        ThreadPool* threadPool = (ThreadPool*)arg;
        return threadPool->threadBody();
    }
    
    vmpi_thread_rtn_t threadBody() {
        SCOPE_LOCK(monitor_) {
            nRunning_ += 1;
        }
        for (;;) {
            Job* job = 0;
            SCOPE_LOCK_NAMED(locker, monitor_) {
                // wait for something to happen
                while (!jobQueueBack_ && !stop_)
                    locker.wait();
                
                if (jobQueueBack_) {
                    job = jobQueueBack_->next_;
                    if (job == jobQueueBack_)
                        jobQueueBack_ = 0;
                    else
                        jobQueueBack_->next_ = job->next_;
                    queueLength_ -= 1;
                    locker.notifyAll();  // in case someone is waiting to enqueue
                }
                else if (stop_) {
                    nRunning_ -= 1;
                    if (nRunning_ == 0)
                        locker.notifyAll();
                    break;
                }
            }
            
            // Run job outside of monitor
            if (job) {
                job->handler();
                job->destroy();
            }
            
            // Wake up anyone waiting on job to finish (for instance enqueueJob())
            SCOPE_LOCK_NAMED(locker2, monitor_) {
                locker2.notifyAll();
            }
        }
        return 0;
    }
    
    Job* jobQueueBack_;  // Circular list starting from the back
    unsigned maxQueue_;
    unsigned queueLength_;
    bool stop_;
    unsigned nRunning_;
    vmbase::WaitNotifyMonitor monitor_;
};

#endif
