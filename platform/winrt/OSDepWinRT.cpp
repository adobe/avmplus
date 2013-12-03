/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "avmplus.h"

using namespace Windows::System::Threading;
using namespace Windows::Foundation;

namespace avmplus
{
	struct IntWriterData
	{
		ThreadPoolTimer^ timer;
	};
	
	uintptr_t OSDep::startIntWriteTimer(uint32_t millis, volatile int *addr)
    {
		IntWriterData *data = (IntWriterData *) VMPI_alloc(sizeof(IntWriterData));
		data->timer = nullptr;
		
		TimeSpan timeSpan;
		timeSpan.Duration = millis;

		data->timer = ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler([&] (ThreadPoolTimer^ timer) {
			*addr = 1;
		}
		), timeSpan);
		return (uintptr_t)data;
    }

    void OSDep::stopTimer(uintptr_t handle)
    {
		IntWriterData *data = (IntWriterData *) handle;
		data->timer->Cancel();
		data->timer = nullptr;
		VMPI_free(data);
    }
}
