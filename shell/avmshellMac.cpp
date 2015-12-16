/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//mac

#include "avmshell.h"
#include "PosixPartialPlatform.h"

#include <sys/signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <string>

namespace avmshell
{
    class MacPlatform : public PosixPartialPlatform
    {
    public:
        MacPlatform(void* stackbase) : stackbase(stackbase) {}
        virtual ~MacPlatform() {}

        virtual void setTimer(int seconds, AvmTimerCallback callback, void* callbackData);
        virtual uintptr_t getMainThreadStackLimit();

    private:
        void* stackbase;
    };

    uintptr_t MacPlatform::getMainThreadStackLimit()
    {
        struct rlimit r;
        size_t stackheight = avmshell::kStackSizeFallbackValue;
        // https://bugzilla.mozilla.org/show_bug.cgi?id=504976: setting the height to kStackSizeFallbackValue
        // is not ideal if the stack is meant to be unlimited but is an OK workaround for the time being.
        if (getrlimit(RLIMIT_STACK, &r) == 0 && r.rlim_cur != RLIM_INFINITY)
            stackheight = size_t(r.rlim_cur);
        return uintptr_t(stackbase) - stackheight + avmshell::kStackMargin;
    }

    AvmTimerCallback pCallbackFunc = 0;
    void* pCallbackData = 0;

    void MacPlatform::setTimer(int seconds, AvmTimerCallback callback, void* callbackData)
    {
        extern void alarmProc(int);

        pCallbackFunc = callback;
        pCallbackData = callbackData;

        signal(SIGALRM, alarmProc);
        alarm(seconds);

    }

    void alarmProc(int /*signum*/)
    {
        pCallbackFunc(pCallbackData);
    }
}

avmshell::MacPlatform* gPlatformHandle = NULL;

avmshell::Platform* avmshell::Platform::GetInstance()
{
    AvmAssert(gPlatformHandle != NULL);
    return gPlatformHandle;
}

//Add Stack trace dump for shell tests
#ifdef VMCFG_HALFMOON_AOT_RUNTIME

typedef void (*sighandler_t)(int);
static sighandler_t sOrigHandler_ABRT = SIG_DFL;
static sighandler_t sOrigHandler_ILL = SIG_DFL;
static sighandler_t sOrigHandler_SEGV = SIG_DFL;
static sighandler_t sOrigHandler_FPE = SIG_DFL;
static sighandler_t sOrigHandler_BUS = SIG_DFL;
static sighandler_t sOrigHandler_PIPE = SIG_DFL;

static void SignalHandler(int type)
{
    (void)type;
    
    //Reset signal handlers
    signal(SIGABRT, sOrigHandler_ABRT);
    signal(SIGILL, sOrigHandler_ILL);
    signal(SIGSEGV, sOrigHandler_SEGV);
    signal(SIGFPE, sOrigHandler_FPE);
    signal(SIGBUS, sOrigHandler_BUS);
    signal(SIGPIPE, sOrigHandler_PIPE);

    
    // Print StackTrace
    void ** buffer = new void*[16];
    int numEntries = backtrace(buffer, 16 );
    char** symbolLines = backtrace_symbols(buffer, numEntries);
    fprintf(stderr,"\n********** Call Stack **********\n");
    for(int i=2; i< numEntries; i++)
    {
        int status;
        std::string stackLine(symbolLines[i]);
        std::size_t sym_end = stackLine.rfind('+') -1;
        std::size_t sym_start = stackLine.rfind(' ', sym_end -1) +1 ;
        std::string symbol = stackLine.substr(sym_start, sym_end - sym_start);
        char *realname = abi::__cxa_demangle(symbol.c_str(), 0, 0, &status);
        fprintf(stderr, "%s%s%s\n",stackLine.substr(0,sym_start).c_str(),
                                (status == 0 )? realname : symbol.c_str(),
                                stackLine.substr(sym_end).c_str());
        free(realname);
    }
    free(symbolLines);
    delete[] buffer;

}

static void InstallUncaughtExceptionHandler()
{
    sOrigHandler_ABRT = signal(SIGABRT, SignalHandler);
    sOrigHandler_ILL  = signal(SIGILL, SignalHandler);
    sOrigHandler_SEGV = signal(SIGSEGV, SignalHandler);
    sOrigHandler_FPE  = signal(SIGFPE, SignalHandler);
    sOrigHandler_BUS  = signal(SIGBUS, SignalHandler);
    sOrigHandler_PIPE = signal(SIGPIPE, SignalHandler);
}
#endif // VMCFG_HALFMOON_AOT_RUNTIME


int main(int argc, char *argv[])
{
#ifdef VMCFG_HALFMOON_AOT_RUNTIME
    //For halfmoon, install signal handlers to get stacktrace
    InstallUncaughtExceptionHandler();
#endif
    
#ifdef VMCFG_MACH_EXCEPTIONS
    avmplus::GenericGuard::staticInit();
#endif

    char* dummy;
    avmshell::MacPlatform platformInstance(&dummy);
    gPlatformHandle = &platformInstance;

    int code = avmshell::Shell::run(argc, argv);
    if (code == avmshell::OUT_OF_MEMORY)
        write(1, "OUT OF MEMORY\n", 14);

#ifdef VMCFG_MACH_EXCEPTIONS
    avmplus::GenericGuard::staticDestroy();
#endif

    return code;
}
