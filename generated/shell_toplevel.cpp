/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* machine generated file -- do not edit */

namespace avmplus { namespace NativeID {

const uint32_t shell_toplevel_abc_class_count = 54;
const uint32_t shell_toplevel_abc_script_count = 7;
const uint32_t shell_toplevel_abc_method_count = 281;
const uint32_t shell_toplevel_abc_length = 18376;

/* thunks (78 total) */
avmplus::Atom avmplus_Domain_currentDomain_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::DomainClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainClass*, argv[argoff0]);
    avmplus::DomainObject* const ret = obj->get_currentDomain();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_Domain_currentDomain_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_currentDomain_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_MIN_DOMAIN_MEMORY_LENGTH_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::DomainClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainClass*, argv[argoff0]);
    uint32_t const ret = obj->get_MIN_DOMAIN_MEMORY_LENGTH();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_Domain_MIN_DOMAIN_MEMORY_LENGTH_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_MIN_DOMAIN_MEMORY_LENGTH_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_private_init_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::DomainObject* arg1 = (avmplus::DomainObject*)AvmThunkUnbox_OBJECT(avmplus::DomainObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::DomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainObject*, argv[argoff0]);
    obj->init(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_Domain_private_init_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_private_init_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_loadBytes_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_OBJECT
    };
    avmplus::ByteArrayObject* arg1 = (avmplus::ByteArrayObject*)AvmThunkUnbox_OBJECT(avmplus::ByteArrayObject*, argv[argoff1]);
    uint32_t arg2 = (argc < 2 ? AvmThunkCoerce_INT_UINT(0) : AvmThunkUnbox_UINT(uint32_t, argv[argoff2]));
    (void)env;
    avmplus::DomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainObject*, argv[argoff0]);
    avmplus::Atom const ret = obj->loadBytes(
        arg1
        , arg2
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_Domain_loadBytes_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_loadBytes_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_getClass_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::DomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainObject*, argv[argoff0]);
    avmplus::ClassClosure* const ret = obj->getClass(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_Domain_getClass_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_getClass_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_domainMemory_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::DomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainObject*, argv[argoff0]);
    avmplus::ByteArrayObject* const ret = obj->get_domainMemory();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_Domain_domainMemory_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_domainMemory_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_Domain_domainMemory_set_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::ByteArrayObject* arg1 = (avmplus::ByteArrayObject*)AvmThunkUnbox_OBJECT(avmplus::ByteArrayObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::DomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::DomainObject*, argv[argoff0]);
    obj->set_domainMemory(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_Domain_domainMemory_set_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_Domain_domainMemory_set_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_sampler_NewObjectSample_object_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::NewObjectSampleObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::NewObjectSampleObject*, argv[argoff0]);
    avmplus::Atom const ret = obj->get_object();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_sampler_NewObjectSample_object_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_sampler_NewObjectSample_object_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double flash_sampler_NewObjectSample_size_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::NewObjectSampleObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::NewObjectSampleObject*, argv[argoff0]);
    double const ret = obj->get_size();
    return double(ret);
}
double flash_sampler_NewObjectSample_size_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = flash_sampler_NewObjectSample_size_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_clearSamples_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::clearSamples(obj);
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler_clearSamples_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_clearSamples_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_startSampling_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::startSampling(obj);
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler_startSampling_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_startSampling_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_stopSampling_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::stopSampling(obj);
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler_stopSampling_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_stopSampling_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_pauseSampling_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::pauseSampling(obj);
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler_pauseSampling_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_pauseSampling_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_sampleInternalAllocs_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::bool32 arg1 = AvmThunkUnbox_BOOLEAN(avmplus::bool32, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::sampleInternalAllocs(obj
        , arg1
    );
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler_sampleInternalAllocs_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_sampleInternalAllocs_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler__setSamplerCallback_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::FunctionObject* arg1 = (avmplus::FunctionObject*)AvmThunkUnbox_OBJECT(avmplus::FunctionObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    SamplerScript::_setSamplerCallback(obj
        , arg1
    );
    return undefinedAtom;
}
avmplus::Atom native_script_function_flash_sampler__setSamplerCallback_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler__setSamplerCallback_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double native_script_function_flash_sampler_getSize_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    double const ret = SamplerScript::getSize(obj
        , arg1
    );
    return double(ret);
}
double native_script_function_flash_sampler_getSize_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = native_script_function_flash_sampler_getSize_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_getMemberNames_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_ATOM
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    avmplus::bool32 arg2 = (argc < 2 ? false : AvmThunkUnbox_BOOLEAN(avmplus::bool32, argv[argoff2]));
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    avmplus::Atom const ret = SamplerScript::getMemberNames(obj
        , arg1
        , arg2
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler_getMemberNames_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_getMemberNames_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler__getSamples_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::ClassClosure* arg1 = (avmplus::ClassClosure*)AvmThunkUnbox_OBJECT(avmplus::ClassClosure*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    avmplus::Atom const ret = SamplerScript::_getSamples(obj
        , arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler__getSamples_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler__getSamples_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double native_script_function_flash_sampler_getSampleCount_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    double const ret = SamplerScript::getSampleCount(obj);
    return double(ret);
}
double native_script_function_flash_sampler_getSampleCount_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = native_script_function_flash_sampler_getSampleCount_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double native_script_function_flash_sampler__getInvocationCount_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_ATOM
        , argoff3 = argoff2 + AvmThunkArgSize_OBJECT
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    avmplus::QNameObject* arg2 = (avmplus::QNameObject*)AvmThunkUnbox_OBJECT(avmplus::QNameObject*, argv[argoff2]);
    uint32_t arg3 = AvmThunkUnbox_UINT(uint32_t, argv[argoff3]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    double const ret = SamplerScript::_getInvocationCount(obj
        , arg1
        , arg2
        , arg3
    );
    return double(ret);
}
double native_script_function_flash_sampler__getInvocationCount_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = native_script_function_flash_sampler__getInvocationCount_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_isGetterSetter_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_ATOM
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    avmplus::QNameObject* arg2 = (avmplus::QNameObject*)AvmThunkUnbox_OBJECT(avmplus::QNameObject*, argv[argoff2]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    bool const ret = SamplerScript::isGetterSetter(obj
        , arg1
        , arg2
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler_isGetterSetter_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_isGetterSetter_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_getLexicalScopes_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::FunctionObject* arg1 = (avmplus::FunctionObject*)AvmThunkUnbox_OBJECT(avmplus::FunctionObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    avmplus::ArrayObject* const ret = SamplerScript::getLexicalScopes(obj
        , arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler_getLexicalScopes_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_getLexicalScopes_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_getSavedThis_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::FunctionObject* arg1 = (avmplus::FunctionObject*)AvmThunkUnbox_OBJECT(avmplus::FunctionObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    avmplus::Atom const ret = SamplerScript::getSavedThis(obj
        , arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler_getSavedThis_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_getSavedThis_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom native_script_function_flash_sampler_getMasterString_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(avmplus::ScriptObject*, argv[argoff0]);
    avmplus::String* const ret = SamplerScript::getMasterString(obj
        , arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom native_script_function_flash_sampler_getMasterString_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = native_script_function_flash_sampler_getMasterString_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_trace_Trace_setLevel_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_INT
    };
    int32_t arg1 = AvmThunkUnbox_INT(int32_t, argv[argoff1]);
    int32_t arg2 = (argc < 2 ? 2 : AvmThunkUnbox_INT(int32_t, argv[argoff2]));
    (void)env;
    avmplus::TraceClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::TraceClass*, argv[argoff0]);
    avmplus::Atom const ret = obj->setLevel(
        arg1
        , arg2
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_trace_Trace_setLevel_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_trace_Trace_setLevel_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_trace_Trace_getLevel_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    int32_t arg1 = (argc < 1 ? 2 : AvmThunkUnbox_INT(int32_t, argv[argoff1]));
    (void)env;
    avmplus::TraceClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::TraceClass*, argv[argoff0]);
    int32_t const ret = obj->getLevel(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_trace_Trace_getLevel_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_trace_Trace_getLevel_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_trace_Trace_setListener_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::FunctionObject* arg1 = (avmplus::FunctionObject*)AvmThunkUnbox_OBJECT(avmplus::FunctionObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmplus::TraceClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::TraceClass*, argv[argoff0]);
    avmplus::Atom const ret = obj->setListener(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_trace_Trace_setListener_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_trace_Trace_setListener_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_trace_Trace_getListener_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmplus::TraceClass* const obj = AvmThunkUnbox_AvmReceiver(avmplus::TraceClass*, argv[argoff0]);
    avmplus::FunctionObject* const ret = obj->getListener();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_trace_Trace_getListener_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_trace_Trace_getListener_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_pr_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::ShellWorkerClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerClass*, argv[argoff0]);
    obj->pr(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom flash_system_Worker_pr_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_pr_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_private_internalGetState_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    avmplus::String* const ret = obj->internalGetState();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_Worker_private_internalGetState_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_private_internalGetState_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_start_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    obj->start();
    return undefinedAtom;
}
avmplus::Atom flash_system_Worker_start_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_start_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_isParentOf_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmshell::ShellWorkerObject* arg1 = (avmshell::ShellWorkerObject*)AvmThunkUnbox_OBJECT(avmshell::ShellWorkerObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    bool const ret = obj->isParentOf(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_Worker_isParentOf_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_isParentOf_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_isPrimordial_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    bool const ret = obj->get_isPrimordial();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_Worker_isPrimordial_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_isPrimordial_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_setSharedProperty_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_STRING
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    avmplus::Atom arg2 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    obj->setSharedProperty(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom flash_system_Worker_setSharedProperty_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_setSharedProperty_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_getSharedProperty_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    avmplus::Atom const ret = obj->getSharedProperty(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_Worker_getSharedProperty_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_getSharedProperty_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_Worker_terminate_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::ShellWorkerObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerObject*, argv[argoff0]);
    bool const ret = obj->terminate();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_Worker_terminate_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_Worker_terminate_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_WorkerDomain_private_createWorkerFromByteArrayInternal_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::ByteArrayObject* arg1 = (avmplus::ByteArrayObject*)AvmThunkUnbox_OBJECT(avmplus::ByteArrayObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::ShellWorkerDomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerDomainObject*, argv[argoff0]);
    avmshell::ShellWorkerObject* const ret = obj->createWorkerFromByteArrayInternal(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_WorkerDomain_private_createWorkerFromByteArrayInternal_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_WorkerDomain_private_createWorkerFromByteArrayInternal_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom flash_system_WorkerDomain_listWorkers_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::ShellWorkerDomainObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::ShellWorkerDomainObject*, argv[argoff0]);
    avmplus::ObjectVectorObject* const ret = obj->listWorkers();
    return avmplus::Atom(ret);
}
avmplus::Atom flash_system_WorkerDomain_listWorkers_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = flash_system_WorkerDomain_listWorkers_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double avmplus_MI_plus_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    double arg1 = AvmThunkUnbox_DOUBLE(double, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::MIObject* const obj = AvmThunkUnbox_AvmReceiver(avmshell::MIObject*, argv[argoff0]);
    double const ret = obj->::avmshell::MIObjectImpl::plus(
        arg1
    );
    return double(ret);
}
double avmplus_MI_plus_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = avmplus_MI_plus_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_exit_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    int32_t arg1 = AvmThunkUnbox_INT(int32_t, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->exit(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_exit_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_exit_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_exec_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    int32_t const ret = obj->exec(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_exec_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_exec_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_sleep_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    int32_t arg1 = AvmThunkUnbox_INT(int32_t, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->sleep(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_sleep_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_sleep_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_getAvmplusVersion_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::String* const ret = obj->getAvmplusVersion();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_getAvmplusVersion_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_getAvmplusVersion_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_getFeatures_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::String* const ret = obj->getFeatures();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_getFeatures_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_getFeatures_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_getRunmode_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::String* const ret = obj->getRunmode();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_getRunmode_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_getRunmode_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_trace_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::ArrayObject* arg1 = (avmplus::ArrayObject*)AvmThunkUnbox_OBJECT(avmplus::ArrayObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->trace(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_trace_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_trace_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_write_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->write(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_write_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_write_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_debugger_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->debugger();
    return undefinedAtom;
}
avmplus::Atom avmplus_System_debugger_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_debugger_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_isDebugger_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    bool const ret = obj->isDebugger();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_isDebugger_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_isDebugger_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double avmplus_System_getNanosecondTimer_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    double const ret = obj->getNanosecondTimer();
    return double(ret);
}
double avmplus_System_getNanosecondTimer_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = avmplus_System_getNanosecondTimer_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_getTimer_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    uint32_t const ret = obj->getTimer();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_getTimer_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_getTimer_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_private_getArgv_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::ArrayObject* const ret = obj->getArgv();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_private_getArgv_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_private_getArgv_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_readLine_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::String* const ret = obj->readLine();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_readLine_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_readLine_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double avmplus_System_totalMemory_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    double const ret = obj->get_totalMemory();
    return double(ret);
}
double avmplus_System_totalMemory_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = avmplus_System_totalMemory_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double avmplus_System_freeMemory_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    double const ret = obj->get_freeMemory();
    return double(ret);
}
double avmplus_System_freeMemory_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = avmplus_System_freeMemory_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
double avmplus_System_privateMemory_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    double const ret = obj->get_privateMemory();
    return double(ret);
}
double avmplus_System_privateMemory_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    double retVal = avmplus_System_privateMemory_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_forceFullCollection_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->forceFullCollection();
    return undefinedAtom;
}
avmplus::Atom avmplus_System_forceFullCollection_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_forceFullCollection_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_queueCollection_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->queueCollection();
    return undefinedAtom;
}
avmplus::Atom avmplus_System_queueCollection_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_queueCollection_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_ns_example_nstest_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->ns_example_nstest();
    return undefinedAtom;
}
avmplus::Atom avmplus_System_ns_example_nstest_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_ns_example_nstest_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_isGlobal_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    bool const ret = obj->isGlobal(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_isGlobal_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_isGlobal_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_swfVersion_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    int32_t const ret = obj->get_swfVersion();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_swfVersion_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_swfVersion_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_apiVersion_get_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    int32_t const ret = obj->get_apiVersion();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_apiVersion_get_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_apiVersion_get_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_disposeXML_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::XMLObject* arg1 = (avmplus::XMLObject*)AvmThunkUnbox_OBJECT(avmplus::XMLObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->disposeXML(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_disposeXML_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_disposeXML_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_deopt_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    int32_t arg1 = AvmThunkUnbox_INT(int32_t, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->deopt(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_deopt_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_deopt_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_smashObjectVectorSize_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_OBJECT
    };
    avmplus::ObjectVectorObject* arg1 = (avmplus::ObjectVectorObject*)AvmThunkUnbox_OBJECT(avmplus::ObjectVectorObject*, argv[argoff1]);
    uint32_t arg2 = AvmThunkUnbox_UINT(uint32_t, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->smashObjectVectorSize(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_smashObjectVectorSize_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_smashObjectVectorSize_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_smashIntVectorSize_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_OBJECT
    };
    avmplus::IntVectorObject* arg1 = (avmplus::IntVectorObject*)AvmThunkUnbox_OBJECT(avmplus::IntVectorObject*, argv[argoff1]);
    uint32_t arg2 = AvmThunkUnbox_UINT(uint32_t, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->smashIntVectorSize(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_smashIntVectorSize_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_smashIntVectorSize_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_smashUIntVectorSize_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_OBJECT
    };
    avmplus::UIntVectorObject* arg1 = (avmplus::UIntVectorObject*)AvmThunkUnbox_OBJECT(avmplus::UIntVectorObject*, argv[argoff1]);
    uint32_t arg2 = AvmThunkUnbox_UINT(uint32_t, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->smashUIntVectorSize(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_smashUIntVectorSize_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_smashUIntVectorSize_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_smashDoubleVectorSize_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_OBJECT
    };
    avmplus::DoubleVectorObject* arg1 = (avmplus::DoubleVectorObject*)AvmThunkUnbox_OBJECT(avmplus::DoubleVectorObject*, argv[argoff1]);
    uint32_t arg2 = AvmThunkUnbox_UINT(uint32_t, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->smashDoubleVectorSize(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_smashDoubleVectorSize_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_smashDoubleVectorSize_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_pauseForGCIfCollectionImminent_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    double arg1 = (argc < 1 ? 0.75 : AvmThunkUnbox_DOUBLE(double, argv[argoff1]));
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->pauseForGCIfCollectionImminent(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_pauseForGCIfCollectionImminent_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_pauseForGCIfCollectionImminent_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_is64bit_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    bool const ret = obj->is64bit();
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_is64bit_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_is64bit_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_isIntptr_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    bool const ret = obj->isIntptr(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_isIntptr_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_isIntptr_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_runInSafepoint_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::FunctionObject* arg1 = (avmplus::FunctionObject*)AvmThunkUnbox_OBJECT(avmplus::FunctionObject*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    obj->runInSafepoint(
        arg1
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_System_runInSafepoint_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_runInSafepoint_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_System_canonicalizeNumber_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::Atom arg1 = AvmThunkUnbox_ATOM(avmplus::Atom, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::SystemClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::SystemClass*, argv[argoff0]);
    avmplus::Atom const ret = obj->canonicalizeNumber(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_System_canonicalizeNumber_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_System_canonicalizeNumber_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_File_exists_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::FileClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::FileClass*, argv[argoff0]);
    bool const ret = obj->exists(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_File_exists_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_File_exists_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_File_read_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::FileClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::FileClass*, argv[argoff0]);
    avmplus::String* const ret = obj->read(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_File_read_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_File_read_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_File_write_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_STRING
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    avmplus::String* arg2 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::FileClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::FileClass*, argv[argoff0]);
    obj->write(
        arg1
        , arg2
    );
    return undefinedAtom;
}
avmplus::Atom avmplus_File_write_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_File_write_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_File_readByteArray_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    (void)argc;
    (void)env;
    avmshell::FileClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::FileClass*, argv[argoff0]);
    avmplus::ByteArrayObject* const ret = obj->readByteArray(
        arg1
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_File_readByteArray_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_File_readByteArray_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}
avmplus::Atom avmplus_File_writeByteArray_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_OBJECT
        , argoff2 = argoff1 + AvmThunkArgSize_STRING
    };
    avmplus::String* arg1 = AvmThunkUnbox_STRING(avmplus::String*, argv[argoff1]);
    avmplus::ByteArrayObject* arg2 = (avmplus::ByteArrayObject*)AvmThunkUnbox_OBJECT(avmplus::ByteArrayObject*, argv[argoff2]);
    (void)argc;
    (void)env;
    avmshell::FileClass* const obj = AvmThunkUnbox_AvmReceiver(avmshell::FileClass*, argv[argoff0]);
    bool const ret = obj->writeByteArray(
        arg1
        , arg2
    );
    return avmplus::Atom(ret);
}
avmplus::Atom avmplus_File_writeByteArray_sampler_thunk(MethodEnv* env, uint32_t argc, Atom* argv)
{
    Namespace* dxns = env->core()->dxns();
    MethodFrame frame;
    frame.enter(env->core(), env);
    frame.setDxns(dxns);
    avmplus::Atom retVal = avmplus_File_writeByteArray_thunk(env, argc, argv);
    frame.exit(env->core());
    return retVal;
}

class SlotOffsetsAndAsserts
{
public:
    #ifdef DEBUG
    static uint32_t getSlotOffset(Traits* t, int nameId);
    static uint32_t getMethodIndex(Traits* t, int nameId);
    static uint32_t getGetterIndex(Traits* t, int nameId);
    static uint32_t getSetterIndex(Traits* t, int nameId);
    #endif // DEBUG
    enum {
        kSlotsOffset_avmplus_CTestClass = 0,
        kSlotsOffset_avmplus_CTestObject = 0,
        kSlotsOffset_avmshell_MIClass = 0,
        kSlotsOffset_avmshell_MIObject = 0,
        kSlotsOffset_avmshell_SystemClass = offsetof(avmshell::SystemClass, m_slots_SystemClass),
        kSlotsOffset_avmplus_SystemObject = 0,
        kSlotsOffset_avmshell_FileClass = 0,
        kSlotsOffset_avmplus_FileObject = 0,
        kSlotsOffset_avmshell_AbstractBaseClass = 0,
        kSlotsOffset_avmshell_AbstractBaseObject = 0,
        kSlotsOffset_avmshell_RestrictedBaseClass = 0,
        kSlotsOffset_avmshell_RestrictedBaseObject = 0,
        kSlotsOffset_avmshell_AbstractRestrictedBaseClass = 0,
        kSlotsOffset_avmshell_AbstractRestrictedBaseObject = 0,
        kSlotsOffset_avmshell_CheckBaseClass = 0,
        kSlotsOffset_avmshell_CheckBaseObject = 0,
        kSlotsOffset_avmshell_NativeBaseClass = 0,
        kSlotsOffset_avmshell_NativeBaseObject = 0,
        kSlotsOffset_avmplus_NativeBaseAS3Class = 0,
        kSlotsOffset_avmplus_NativeBaseAS3Object = 0,
        kSlotsOffset_avmplus_ShellCoreFriend1Class = offsetof(avmplus::ShellCoreFriend1Class, m_slots_ShellCoreFriend1Class),
        kSlotsOffset_avmplus_ShellCoreFriend1Object = 0,
        kSlotsOffset_avmplus_ShellCoreFriend2Class = offsetof(avmplus::ShellCoreFriend2Class, m_slots_ShellCoreFriend2Class),
        kSlotsOffset_avmplus_ShellCoreFriend2Object = 0,
        kSlotsOffset_avmplus_CapabilitiesClass = 0,
        kSlotsOffset_avmplus_CapabilitiesObject = 0,
        kSlotsOffset_avmplus_public_classClass = 0,
        kSlotsOffset_avmplus_public_classObject = offsetof(avmplus::public_classObject, m_slots_public_classObject),
        kSlotsOffset_avmplus_public_class_AIR_1_0Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_0Object = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0Class = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0Object = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5Object = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_1Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_1Object = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0_32Class = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0_32Object = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_2Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_2Object = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_0_FP_10_0Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_0_FP_10_0Object = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class = 0,
        kSlotsOffset_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class = 0,
        kSlotsOffset_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Object = 0,
        kSlotsOffset_avmshell_NativeSubclassOfAbstractBaseClass = 0,
        kSlotsOffset_avmshell_NativeSubclassOfAbstractBaseObject = 0,
        kSlotsOffset_avmplus_SubclassOfAbstractBaseClass = 0,
        kSlotsOffset_avmplus_SubclassOfAbstractBaseObject = 0,
        kSlotsOffset_avmshell_NativeSubclassOfRestrictedBaseClass = 0,
        kSlotsOffset_avmshell_NativeSubclassOfRestrictedBaseObject = 0,
        kSlotsOffset_avmplus_SubclassOfRestrictedBaseClass = 0,
        kSlotsOffset_avmplus_SubclassOfRestrictedBaseObject = 0,
        kSlotsOffset_avmshell_NativeSubclassOfAbstractRestrictedBaseClass = 0,
        kSlotsOffset_avmshell_NativeSubclassOfAbstractRestrictedBaseObject = 0,
        kSlotsOffset_avmplus_SubclassOfAbstractRestrictedBaseClass = 0,
        kSlotsOffset_avmplus_SubclassOfAbstractRestrictedBaseObject = 0,
        kSlotsOffset_avmplus_NativeBaseExtender1Class = 0,
        kSlotsOffset_avmplus_NativeBaseExtender1Object = offsetof(avmplus::NativeBaseExtender1Object, m_slots_NativeBaseExtender1Object),
        kSlotsOffset_avmplus_NativeBaseExtender2Class = 0,
        kSlotsOffset_avmplus_NativeBaseExtender2Object = offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object),
        kSlotsOffset_avmplus_DomainClass = 0,
        kSlotsOffset_avmplus_DomainObject = 0,
        kSlotsOffset_avmplus_StackFrameClass = 0,
        kSlotsOffset_avmplus_StackFrameObject = offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject),
        kSlotsOffset_avmplus_SampleClass = 0,
        kSlotsOffset_avmplus_SampleObject = offsetof(avmplus::SampleObject, m_slots_SampleObject),
        kSlotsOffset_avmplus_ClassFactoryClass = offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass),
        kSlotsOffset_avmplus_ClassFactoryObject = 0,
        kSlotsOffset_avmplus_NewObjectSampleClass = 0,
        kSlotsOffset_avmplus_NewObjectSampleObject = offsetof(avmplus::NewObjectSampleObject, m_slots_NewObjectSampleObject),
        kSlotsOffset_avmplus_DeleteObjectSampleClass = 0,
        kSlotsOffset_avmplus_DeleteObjectSampleObject = offsetof(avmplus::DeleteObjectSampleObject, m_slots_DeleteObjectSampleObject),
        kSlotsOffset_avmplus_TraceClass = offsetof(avmplus::TraceClass, m_slots_TraceClass),
        kSlotsOffset_avmplus_TraceObject = 0,
        kSlotsOffset_avmplus_EndianClass = offsetof(avmplus::EndianClass, m_slots_EndianClass),
        kSlotsOffset_avmplus_EndianObject = 0,
        kSlotsOffset_avmplus_WorkerStateClass = offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass),
        kSlotsOffset_avmplus_WorkerStateObject = 0,
        kSlotsOffset_avmshell_ShellWorkerClass = offsetof(avmshell::ShellWorkerClass, m_slots_ShellWorkerClass),
        kSlotsOffset_avmshell_ShellWorkerObject = offsetof(avmshell::ShellWorkerObject, m_slots_ShellWorkerObject),
        kSlotsOffset_avmplus_WorkerEventClass = offsetof(avmplus::WorkerEventClass, m_slots_WorkerEventClass),
        kSlotsOffset_avmplus_WorkerEventObject = offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject),
        kSlotsOffset_avmshell_ShellWorkerDomainClass = offsetof(avmshell::ShellWorkerDomainClass, m_slots_ShellWorkerDomainClass),
        kSlotsOffset_avmshell_ShellWorkerDomainObject = 0,
        kSlotsOffset_fnord
    };
    #ifdef DEBUG
    static void check_avmplus_CTestClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_MIClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_SystemClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_FileClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_AbstractBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_RestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_AbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_CheckBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_NativeBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_NativeBaseAS3Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_ShellCoreFriend1Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_ShellCoreFriend2Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_CapabilitiesClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_classClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_0Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_FP_10_0Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_5Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_5_1Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_FP_10_0_32Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_5_2Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_0_FP_10_0Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class(Traits* ctraits, Traits* itraits);
    static void check_avmshell_NativeSubclassOfAbstractBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_SubclassOfAbstractBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_NativeSubclassOfRestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_SubclassOfRestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_NativeSubclassOfAbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_SubclassOfAbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_NativeBaseExtender1Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_NativeBaseExtender2Class(Traits* ctraits, Traits* itraits);
    static void check_avmplus_DomainClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_StackFrameClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_SampleClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_ClassFactoryClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_NewObjectSampleClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_DeleteObjectSampleClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_TraceClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_EndianClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_WorkerStateClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_ShellWorkerClass(Traits* ctraits, Traits* itraits);
    static void check_avmplus_WorkerEventClass(Traits* ctraits, Traits* itraits);
    static void check_avmshell_ShellWorkerDomainClass(Traits* ctraits, Traits* itraits);
    #endif
};
#ifdef DEBUG
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_CTestClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_MIClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_SystemClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmshell::SystemClass, m_slots_SystemClass) == kSlotsOffset_avmshell_SystemClass);
    MMGC_STATIC_ASSERT(offsetof(avmshell::SystemClass, m_slots_SystemClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmshell::SystemClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 48) == (offsetof(avmshell::SystemClass, m_slots_SystemClass) + offsetof(avmshell_SystemClassSlots, m_argv)));
    AvmAssert(getMethodIndex(ctraits, 35) == 5); // exit
    AvmAssert(getMethodIndex(ctraits, 36) == 6); // exec
    AvmAssert(getMethodIndex(ctraits, 37) == 7); // sleep
    AvmAssert(getMethodIndex(ctraits, 38) == 8); // getAvmplusVersion
    AvmAssert(getMethodIndex(ctraits, 39) == 9); // getFeatures
    AvmAssert(getMethodIndex(ctraits, 40) == 10); // getRunmode
    AvmAssert(getMethodIndex(ctraits, 41) == 11); // trace
    AvmAssert(getMethodIndex(ctraits, 42) == 12); // write
    AvmAssert(getMethodIndex(ctraits, 43) == 13); // debugger
    AvmAssert(getMethodIndex(ctraits, 44) == 14); // isDebugger
    AvmAssert(getMethodIndex(ctraits, 45) == 15); // getNanosecondTimer
    AvmAssert(getMethodIndex(ctraits, 46) == 16); // getTimer
    AvmAssert(getMethodIndex(ctraits, 47) == 17); // private::getArgv
    AvmAssert(getMethodIndex(ctraits, 49) == 18); // readLine
    AvmAssert(getGetterIndex(ctraits, 50) == 19); // totalMemory
    AvmAssert(getGetterIndex(ctraits, 51) == 21); // freeMemory
    AvmAssert(getGetterIndex(ctraits, 52) == 23); // privateMemory
    AvmAssert(getMethodIndex(ctraits, 53) == 25); // forceFullCollection
    AvmAssert(getMethodIndex(ctraits, 54) == 26); // queueCollection
    AvmAssert(getMethodIndex(ctraits, 55) == 27); // http://www.example.com::nstest
    AvmAssert(getMethodIndex(ctraits, 56) == 28); // isGlobal
    AvmAssert(getGetterIndex(ctraits, 57) == 29); // swfVersion
    AvmAssert(getGetterIndex(ctraits, 58) == 31); // apiVersion
    AvmAssert(getMethodIndex(ctraits, 59) == 33); // disposeXML
    AvmAssert(getMethodIndex(ctraits, 60) == 34); // deopt
    AvmAssert(getMethodIndex(ctraits, 61) == 35); // smashObjectVectorSize
    AvmAssert(getMethodIndex(ctraits, 62) == 36); // smashIntVectorSize
    AvmAssert(getMethodIndex(ctraits, 63) == 37); // smashUIntVectorSize
    AvmAssert(getMethodIndex(ctraits, 64) == 38); // smashDoubleVectorSize
    AvmAssert(getMethodIndex(ctraits, 65) == 39); // pauseForGCIfCollectionImminent
    AvmAssert(getMethodIndex(ctraits, 66) == 40); // is64bit
    AvmAssert(getMethodIndex(ctraits, 67) == 41); // isIntptr
    AvmAssert(getMethodIndex(ctraits, 68) == 42); // runInSafepoint
    AvmAssert(getMethodIndex(ctraits, 69) == 43); // canonicalizeNumber
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_FileClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_AbstractBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_RestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_AbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_CheckBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_NativeBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_NativeBaseAS3Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_ShellCoreFriend1Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::ShellCoreFriend1Class, m_slots_ShellCoreFriend1Class) == kSlotsOffset_avmplus_ShellCoreFriend1Class);
    MMGC_STATIC_ASSERT(offsetof(avmplus::ShellCoreFriend1Class, m_slots_ShellCoreFriend1Class) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::ShellCoreFriend1Class) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 84) == (offsetof(avmplus::ShellCoreFriend1Class, m_slots_ShellCoreFriend1Class) + offsetof(avmplus_ShellCoreFriend1ClassSlots, m_private_foo)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_ShellCoreFriend2Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::ShellCoreFriend2Class, m_slots_ShellCoreFriend2Class) == kSlotsOffset_avmplus_ShellCoreFriend2Class);
    MMGC_STATIC_ASSERT(offsetof(avmplus::ShellCoreFriend2Class, m_slots_ShellCoreFriend2Class) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::ShellCoreFriend2Class) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 87) == (offsetof(avmplus::ShellCoreFriend2Class, m_slots_ShellCoreFriend2Class) + offsetof(avmplus_ShellCoreFriend2ClassSlots, m_private_bar)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_CapabilitiesClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_classClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::public_classObject, m_slots_public_classObject) == kSlotsOffset_avmplus_public_classObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::public_classObject, m_slots_public_classObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::public_classObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 93) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var)));
    AvmAssert(getSlotOffset(itraits, 94) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_0)));
    AvmAssert(getSlotOffset(itraits, 95) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_FP_10_0)));
    AvmAssert(getSlotOffset(itraits, 96) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_5)));
    AvmAssert(getSlotOffset(itraits, 97) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_5_1)));
    AvmAssert(getSlotOffset(itraits, 98) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_FP_10_0_32)));
    AvmAssert(getSlotOffset(itraits, 99) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_5_2)));
    AvmAssert(getSlotOffset(itraits, 100) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_0_FP_10_0)));
    AvmAssert(getSlotOffset(itraits, 101) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_AIR_1_5_1_FP_10_0_AIR_1_5_2)));
    AvmAssert(getSlotOffset(itraits, 102) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_var_FP_10_0_32_AIR_1_0_FP_10_0)));
    AvmAssert(getSlotOffset(itraits, 103) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const)));
    AvmAssert(getSlotOffset(itraits, 104) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_0)));
    AvmAssert(getSlotOffset(itraits, 105) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_FP_10_0)));
    AvmAssert(getSlotOffset(itraits, 106) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_5)));
    AvmAssert(getSlotOffset(itraits, 107) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_5_1)));
    AvmAssert(getSlotOffset(itraits, 108) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_FP_10_0_32)));
    AvmAssert(getSlotOffset(itraits, 109) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_5_2)));
    AvmAssert(getSlotOffset(itraits, 110) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_0_FP_10_0)));
    AvmAssert(getSlotOffset(itraits, 111) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_AIR_1_5_1_FP_10_0_AIR_1_5_2)));
    AvmAssert(getSlotOffset(itraits, 112) == (offsetof(avmplus::public_classObject, m_slots_public_classObject) + offsetof(avmplus_public_classObjectSlots, m_public_const_FP_10_0_32_AIR_1_0_FP_10_0)));
    AvmAssert(getMethodIndex(itraits, 113) == 3); // public_function
    AvmAssert(getMethodIndex(itraits, 114) == 4); // public_function_AIR_1_0
    AvmAssert(getMethodIndex(itraits, 115) == 5); // public_function_FP_10_0
    AvmAssert(getMethodIndex(itraits, 116) == 6); // public_function_AIR_1_5
    AvmAssert(getMethodIndex(itraits, 117) == 7); // public_function_AIR_1_5_1
    AvmAssert(getMethodIndex(itraits, 118) == 8); // public_function_FP_10_0_32
    AvmAssert(getMethodIndex(itraits, 119) == 9); // public_function_AIR_1_5_2
    AvmAssert(getMethodIndex(itraits, 120) == 10); // public_function_AIR_1_0_FP_10_0
    AvmAssert(getMethodIndex(itraits, 121) == 11); // public_function_AIR_1_5_1_FP_10_0_AIR_1_5_2
    AvmAssert(getMethodIndex(itraits, 122) == 12); // public_function_FP_10_0_32_AIR_1_0_FP_10_0
    AvmAssert(getGetterIndex(itraits, 123) == 13); // public_getset
    AvmAssert(getGetterIndex(itraits, 124) == 15); // public_getset_AIR_1_0
    AvmAssert(getGetterIndex(itraits, 125) == 17); // public_getset_FP_10_0
    AvmAssert(getGetterIndex(itraits, 126) == 19); // public_getset_AIR_1_5
    AvmAssert(getGetterIndex(itraits, 127) == 21); // public_getset_AIR_1_5_1
    AvmAssert(getGetterIndex(itraits, 128) == 23); // public_getset_FP_10_0_32
    AvmAssert(getGetterIndex(itraits, 129) == 25); // public_getset_AIR_1_5_2
    AvmAssert(getGetterIndex(itraits, 130) == 27); // public_getset_AIR_1_0_FP_10_0
    AvmAssert(getGetterIndex(itraits, 131) == 29); // public_getset_AIR_1_5_1_FP_10_0_AIR_1_5_2
    AvmAssert(getGetterIndex(itraits, 132) == 31); // public_getset_FP_10_0_32_AIR_1_0_FP_10_0
    AvmAssert(getSetterIndex(itraits, 123) == 14); // public_getset
    AvmAssert(getSetterIndex(itraits, 124) == 16); // public_getset_AIR_1_0
    AvmAssert(getSetterIndex(itraits, 125) == 18); // public_getset_FP_10_0
    AvmAssert(getSetterIndex(itraits, 126) == 20); // public_getset_AIR_1_5
    AvmAssert(getSetterIndex(itraits, 127) == 22); // public_getset_AIR_1_5_1
    AvmAssert(getSetterIndex(itraits, 128) == 24); // public_getset_FP_10_0_32
    AvmAssert(getSetterIndex(itraits, 129) == 26); // public_getset_AIR_1_5_2
    AvmAssert(getSetterIndex(itraits, 130) == 28); // public_getset_AIR_1_0_FP_10_0
    AvmAssert(getSetterIndex(itraits, 131) == 30); // public_getset_AIR_1_5_1_FP_10_0_AIR_1_5_2
    AvmAssert(getSetterIndex(itraits, 132) == 32); // public_getset_FP_10_0_32_AIR_1_0_FP_10_0
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_0Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_1Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0_32Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_2Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_0_FP_10_0Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfAbstractBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_SubclassOfAbstractBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfRestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_SubclassOfRestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfAbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_SubclassOfAbstractRestrictedBaseClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_NativeBaseExtender1Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::NativeBaseExtender1Object, m_slots_NativeBaseExtender1Object) == kSlotsOffset_avmplus_NativeBaseExtender1Object);
    MMGC_STATIC_ASSERT(offsetof(avmplus::NativeBaseExtender1Object, m_slots_NativeBaseExtender1Object) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::NativeBaseExtender1Object) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 159) == (offsetof(avmplus::NativeBaseExtender1Object, m_slots_NativeBaseExtender1Object) + offsetof(avmplus_NativeBaseExtender1ObjectSlots, m_private_foo)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_NativeBaseExtender2Class(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object) == kSlotsOffset_avmplus_NativeBaseExtender2Object);
    MMGC_STATIC_ASSERT(offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::NativeBaseExtender2Object) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 161) == (offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object) + offsetof(avmplus_NativeBaseExtender2ObjectSlots, m_private_foo)));
    AvmAssert(getSlotOffset(itraits, 162) == (offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object) + offsetof(avmplus_NativeBaseExtender2ObjectSlots, m_private_foo1)));
    AvmAssert(getSlotOffset(itraits, 163) == (offsetof(avmplus::NativeBaseExtender2Object, m_slots_NativeBaseExtender2Object) + offsetof(avmplus_NativeBaseExtender2ObjectSlots, m_private_foo2)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_DomainClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_StackFrameClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) == kSlotsOffset_avmplus_StackFrameObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::StackFrameObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 382) == (offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) + offsetof(avmplus_StackFrameObjectSlots, m_name)));
    AvmAssert(getSlotOffset(itraits, 383) == (offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) + offsetof(avmplus_StackFrameObjectSlots, m_file)));
    AvmAssert(getSlotOffset(itraits, 384) == (offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) + offsetof(avmplus_StackFrameObjectSlots, m_line)));
    AvmAssert(getSlotOffset(itraits, 385) == (offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject) + offsetof(avmplus_StackFrameObjectSlots, m_scriptID)));
    AvmAssert(getMethodIndex(itraits, 386) == 3); // toString
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_SampleClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::SampleObject, m_slots_SampleObject) == kSlotsOffset_avmplus_SampleObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::SampleObject, m_slots_SampleObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::SampleObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 388) == (offsetof(avmplus::SampleObject, m_slots_SampleObject) + offsetof(avmplus_SampleObjectSlots, m_time)));
    AvmAssert(getSlotOffset(itraits, 389) == (offsetof(avmplus::SampleObject, m_slots_SampleObject) + offsetof(avmplus_SampleObjectSlots, m_stack)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_ClassFactoryClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) == kSlotsOffset_avmplus_ClassFactoryClass);
    MMGC_STATIC_ASSERT(offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::ClassFactoryClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 395) == (offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) + offsetof(avmplus_ClassFactoryClassSlots, m_StackFrameClass)));
    AvmAssert(getSlotOffset(ctraits, 396) == (offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) + offsetof(avmplus_ClassFactoryClassSlots, m_SampleClass)));
    AvmAssert(getSlotOffset(ctraits, 397) == (offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) + offsetof(avmplus_ClassFactoryClassSlots, m_DeleteObjectSampleClass)));
    AvmAssert(getSlotOffset(ctraits, 398) == (offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass) + offsetof(avmplus_ClassFactoryClassSlots, m_NewObjectSampleClass)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_NewObjectSampleClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::NewObjectSampleObject, m_slots_NewObjectSampleObject) == kSlotsOffset_avmplus_NewObjectSampleObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::NewObjectSampleObject, m_slots_NewObjectSampleObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::NewObjectSampleObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 400) == (offsetof(avmplus::NewObjectSampleObject, m_slots_NewObjectSampleObject) + offsetof(avmplus_NewObjectSampleObjectSlots, m_id)));
    AvmAssert(getSlotOffset(itraits, 401) == (offsetof(avmplus::NewObjectSampleObject, m_slots_NewObjectSampleObject) + offsetof(avmplus_NewObjectSampleObjectSlots, m_type)));
    AvmAssert(getGetterIndex(itraits, 402) == 3); // object
    AvmAssert(getGetterIndex(itraits, 403) == 5); // size
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_DeleteObjectSampleClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::DeleteObjectSampleObject, m_slots_DeleteObjectSampleObject) == kSlotsOffset_avmplus_DeleteObjectSampleObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::DeleteObjectSampleObject, m_slots_DeleteObjectSampleObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::DeleteObjectSampleObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 400) == (offsetof(avmplus::DeleteObjectSampleObject, m_slots_DeleteObjectSampleObject) + offsetof(avmplus_DeleteObjectSampleObjectSlots, m_id)));
    AvmAssert(getSlotOffset(itraits, 403) == (offsetof(avmplus::DeleteObjectSampleObject, m_slots_DeleteObjectSampleObject) + offsetof(avmplus_DeleteObjectSampleObjectSlots, m_size)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_TraceClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::TraceClass, m_slots_TraceClass) == kSlotsOffset_avmplus_TraceClass);
    MMGC_STATIC_ASSERT(offsetof(avmplus::TraceClass, m_slots_TraceClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::TraceClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 439) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_OFF)));
    AvmAssert(getSlotOffset(ctraits, 440) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_METHODS)));
    AvmAssert(getSlotOffset(ctraits, 441) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_METHODS_WITH_ARGS)));
    AvmAssert(getSlotOffset(ctraits, 442) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_METHODS_AND_LINES)));
    AvmAssert(getSlotOffset(ctraits, 443) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_METHODS_AND_LINES_WITH_ARGS)));
    AvmAssert(getSlotOffset(ctraits, 444) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_FILE)));
    AvmAssert(getSlotOffset(ctraits, 445) == (offsetof(avmplus::TraceClass, m_slots_TraceClass) + offsetof(avmplus_TraceClassSlots, m_LISTENER)));
    AvmAssert(getMethodIndex(ctraits, 446) == 5); // setLevel
    AvmAssert(getMethodIndex(ctraits, 447) == 6); // getLevel
    AvmAssert(getMethodIndex(ctraits, 448) == 7); // setListener
    AvmAssert(getMethodIndex(ctraits, 449) == 8); // getListener
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_EndianClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::EndianClass, m_slots_EndianClass) == kSlotsOffset_avmplus_EndianClass);
    MMGC_STATIC_ASSERT(offsetof(avmplus::EndianClass, m_slots_EndianClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::EndianClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 455) == (offsetof(avmplus::EndianClass, m_slots_EndianClass) + offsetof(avmplus_EndianClassSlots, m_BIG_ENDIAN)));
    AvmAssert(getSlotOffset(ctraits, 456) == (offsetof(avmplus::EndianClass, m_slots_EndianClass) + offsetof(avmplus_EndianClassSlots, m_LITTLE_ENDIAN)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_WorkerStateClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) == kSlotsOffset_avmplus_WorkerStateClass);
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::WorkerStateClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 473) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_NEW)));
    AvmAssert(getSlotOffset(ctraits, 474) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_RUNNING)));
    AvmAssert(getSlotOffset(ctraits, 475) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_TERMINATED)));
    AvmAssert(getSlotOffset(ctraits, 476) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_FAILED)));
    AvmAssert(getSlotOffset(ctraits, 477) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_ABORTED)));
    AvmAssert(getSlotOffset(ctraits, 478) == (offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass) + offsetof(avmplus_WorkerStateClassSlots, m_EXCEPTION)));
    AvmAssert(getMethodIndex(ctraits, 479) == 5); // code
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_ShellWorkerClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerClass, m_slots_ShellWorkerClass) == kSlotsOffset_avmshell_ShellWorkerClass);
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerClass, m_slots_ShellWorkerClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmshell::ShellWorkerClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 486) == (offsetof(avmshell::ShellWorkerClass, m_slots_ShellWorkerClass) + offsetof(avmshell_ShellWorkerClassSlots, m_private_m_current)));
    AvmAssert(getGetterIndex(ctraits, 484) == 5); // current
    AvmAssert(getMethodIndex(ctraits, 485) == 7); // pr
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerObject, m_slots_ShellWorkerObject) == kSlotsOffset_avmshell_ShellWorkerObject);
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerObject, m_slots_ShellWorkerObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmshell::ShellWorkerObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 495) == (offsetof(avmshell::ShellWorkerObject, m_slots_ShellWorkerObject) + offsetof(avmshell_ShellWorkerObjectSlots, m_private_m_byteCode)));
    AvmAssert(getGetterIndex(itraits, 487) == 3); // state
    AvmAssert(getMethodIndex(itraits, 488) == 5); // private::internalGetState
    AvmAssert(getMethodIndex(itraits, 489) == 6); // start
    AvmAssert(getMethodIndex(itraits, 490) == 7); // isParentOf
    AvmAssert(getGetterIndex(itraits, 491) == 8); // isPrimordial
    AvmAssert(getMethodIndex(itraits, 492) == 10); // setSharedProperty
    AvmAssert(getMethodIndex(itraits, 493) == 11); // getSharedProperty
    AvmAssert(getMethodIndex(itraits, 494) == 12); // terminate
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmplus_WorkerEventClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerEventClass, m_slots_WorkerEventClass) == kSlotsOffset_avmplus_WorkerEventClass);
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerEventClass, m_slots_WorkerEventClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::WorkerEventClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 500) == (offsetof(avmplus::WorkerEventClass, m_slots_WorkerEventClass) + offsetof(avmplus_WorkerEventClassSlots, m_WORKER_STATE)));
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject) == kSlotsOffset_avmplus_WorkerEventObject);
    MMGC_STATIC_ASSERT(offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmplus::WorkerEventObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(itraits, 504) == (offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject) + offsetof(avmplus_WorkerEventObjectSlots, m_private_m_previousState)));
    AvmAssert(getSlotOffset(itraits, 505) == (offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject) + offsetof(avmplus_WorkerEventObjectSlots, m_private_m_currentState)));
    AvmAssert(getSlotOffset(itraits, 506) == (offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject) + offsetof(avmplus_WorkerEventObjectSlots, m_flash_system_m_target)));
    AvmAssert(getGetterIndex(itraits, 501) == 3); // currentState
    AvmAssert(getGetterIndex(itraits, 502) == 5); // previousState
    AvmAssert(getGetterIndex(itraits, 503) == 7); // target
}
REALLY_INLINE void SlotOffsetsAndAsserts::check_avmshell_ShellWorkerDomainClass(Traits* ctraits, Traits* itraits)
{
    (void)ctraits; (void)itraits;
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerDomainClass, m_slots_ShellWorkerDomainClass) == kSlotsOffset_avmshell_ShellWorkerDomainClass);
    MMGC_STATIC_ASSERT(offsetof(avmshell::ShellWorkerDomainClass, m_slots_ShellWorkerDomainClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(avmshell::ShellWorkerDomainClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(ctraits, 519) == (offsetof(avmshell::ShellWorkerDomainClass, m_slots_ShellWorkerDomainClass) + offsetof(avmshell_ShellWorkerDomainClassSlots, m_private_m_current)));
    AvmAssert(getGetterIndex(ctraits, 484) == 5); // current
}
#endif // DEBUG


AVMTHUNK_BEGIN_NATIVE_TABLES(shell_toplevel)

    AVMTHUNK_BEGIN_NATIVE_METHODS(shell_toplevel)
        AVMTHUNK_NATIVE_METHOD(avmplus_MI_plus, ::avmshell::MIObjectImpl::plus)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_exit, avmshell::SystemClass::exit)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_exec, avmshell::SystemClass::exec)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_sleep, avmshell::SystemClass::sleep)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_getAvmplusVersion, avmshell::SystemClass::getAvmplusVersion)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_getFeatures, avmshell::SystemClass::getFeatures)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_getRunmode, avmshell::SystemClass::getRunmode)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_trace, avmshell::SystemClass::trace)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_write, avmshell::SystemClass::write)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_debugger, avmshell::SystemClass::debugger)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_isDebugger, avmshell::SystemClass::isDebugger)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_getNanosecondTimer, avmshell::SystemClass::getNanosecondTimer)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_getTimer, avmshell::SystemClass::getTimer)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_private_getArgv, avmshell::SystemClass::getArgv)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_readLine, avmshell::SystemClass::readLine)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_totalMemory_get, avmshell::SystemClass::get_totalMemory)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_freeMemory_get, avmshell::SystemClass::get_freeMemory)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_privateMemory_get, avmshell::SystemClass::get_privateMemory)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_forceFullCollection, avmshell::SystemClass::forceFullCollection)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_queueCollection, avmshell::SystemClass::queueCollection)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_ns_example_nstest, avmshell::SystemClass::ns_example_nstest)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_isGlobal, avmshell::SystemClass::isGlobal)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_swfVersion_get, avmshell::SystemClass::get_swfVersion)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_apiVersion_get, avmshell::SystemClass::get_apiVersion)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_disposeXML, avmshell::SystemClass::disposeXML)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_deopt, avmshell::SystemClass::deopt)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_smashObjectVectorSize, avmshell::SystemClass::smashObjectVectorSize)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_smashIntVectorSize, avmshell::SystemClass::smashIntVectorSize)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_smashUIntVectorSize, avmshell::SystemClass::smashUIntVectorSize)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_smashDoubleVectorSize, avmshell::SystemClass::smashDoubleVectorSize)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_pauseForGCIfCollectionImminent, avmshell::SystemClass::pauseForGCIfCollectionImminent)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_is64bit, avmshell::SystemClass::is64bit)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_isIntptr, avmshell::SystemClass::isIntptr)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_runInSafepoint, avmshell::SystemClass::runInSafepoint)
        AVMTHUNK_NATIVE_METHOD(avmplus_System_canonicalizeNumber, avmshell::SystemClass::canonicalizeNumber)
        AVMTHUNK_NATIVE_METHOD(avmplus_File_exists, avmshell::FileClass::exists)
        AVMTHUNK_NATIVE_METHOD(avmplus_File_read, avmshell::FileClass::read)
        AVMTHUNK_NATIVE_METHOD(avmplus_File_write, avmshell::FileClass::write)
        AVMTHUNK_NATIVE_METHOD(avmplus_File_readByteArray, avmshell::FileClass::readByteArray)
        AVMTHUNK_NATIVE_METHOD(avmplus_File_writeByteArray, avmshell::FileClass::writeByteArray)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_currentDomain_get, avmplus::DomainClass::get_currentDomain)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_MIN_DOMAIN_MEMORY_LENGTH_get, avmplus::DomainClass::get_MIN_DOMAIN_MEMORY_LENGTH)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_private_init, avmplus::DomainObject::init)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_loadBytes, avmplus::DomainObject::loadBytes)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_getClass, avmplus::DomainObject::getClass)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_domainMemory_get, avmplus::DomainObject::get_domainMemory)
        AVMTHUNK_NATIVE_METHOD(avmplus_Domain_domainMemory_set, avmplus::DomainObject::set_domainMemory)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getMasterString, SamplerScript::getMasterString)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getSavedThis, SamplerScript::getSavedThis)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getLexicalScopes, SamplerScript::getLexicalScopes)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_isGetterSetter, SamplerScript::isGetterSetter)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler__getInvocationCount, SamplerScript::_getInvocationCount)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getSampleCount, SamplerScript::getSampleCount)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler__getSamples, SamplerScript::_getSamples)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getMemberNames, SamplerScript::getMemberNames)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_getSize, SamplerScript::getSize)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler__setSamplerCallback, SamplerScript::_setSamplerCallback)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_sampleInternalAllocs, SamplerScript::sampleInternalAllocs)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_pauseSampling, SamplerScript::pauseSampling)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_stopSampling, SamplerScript::stopSampling)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_startSampling, SamplerScript::startSampling)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_sampler_clearSamples, SamplerScript::clearSamples)
        AVMTHUNK_NATIVE_METHOD(flash_sampler_NewObjectSample_object_get, avmplus::NewObjectSampleObject::get_object)
        AVMTHUNK_NATIVE_METHOD(flash_sampler_NewObjectSample_size_get, avmplus::NewObjectSampleObject::get_size)
        AVMTHUNK_NATIVE_METHOD(flash_trace_Trace_setLevel, avmplus::TraceClass::setLevel)
        AVMTHUNK_NATIVE_METHOD(flash_trace_Trace_getLevel, avmplus::TraceClass::getLevel)
        AVMTHUNK_NATIVE_METHOD(flash_trace_Trace_setListener, avmplus::TraceClass::setListener)
        AVMTHUNK_NATIVE_METHOD(flash_trace_Trace_getListener, avmplus::TraceClass::getListener)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_pr, avmshell::ShellWorkerClass::pr)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_private_internalGetState, avmshell::ShellWorkerObject::internalGetState)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_start, avmshell::ShellWorkerObject::start)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_isParentOf, avmshell::ShellWorkerObject::isParentOf)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_isPrimordial_get, avmshell::ShellWorkerObject::get_isPrimordial)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_setSharedProperty, avmshell::ShellWorkerObject::setSharedProperty)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_getSharedProperty, avmshell::ShellWorkerObject::getSharedProperty)
        AVMTHUNK_NATIVE_METHOD(flash_system_Worker_terminate, avmshell::ShellWorkerObject::terminate)
        AVMTHUNK_NATIVE_METHOD(flash_system_WorkerDomain_private_createWorkerFromByteArrayInternal, avmshell::ShellWorkerDomainObject::createWorkerFromByteArrayInternal)
        AVMTHUNK_NATIVE_METHOD(flash_system_WorkerDomain_listWorkers, avmshell::ShellWorkerDomainObject::listWorkers)
    AVMTHUNK_END_NATIVE_METHODS()

    AVMTHUNK_BEGIN_NATIVE_CLASSES(shell_toplevel)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmplus_CTest, CTestClass, avmplus::CTestClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_CTestClass, avmplus::CTestObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_CTestObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmplus_MI, MIClass, avmshell::MIClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_MIClass, avmshell::MIObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_MIObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmplus_System, SystemClass, avmshell::SystemClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_SystemClass, avmplus::SystemObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SystemObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmplus_File, FileClass, avmshell::FileClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_FileClass, avmplus::FileObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_FileObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_AbstractBase, AbstractBaseClass, avmshell::AbstractBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_AbstractBaseClass, avmshell::AbstractBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_AbstractBaseObject, false, false, true)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_RestrictedBase, RestrictedBaseClass, avmshell::RestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_RestrictedBaseClass, avmshell::RestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_RestrictedBaseObject, false, true, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_AbstractRestrictedBase, AbstractRestrictedBaseClass, avmshell::AbstractRestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_AbstractRestrictedBaseClass, avmshell::AbstractRestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_AbstractRestrictedBaseObject, false, true, true)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_CheckBase, CheckBaseClass, avmshell::CheckBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_CheckBaseClass, avmshell::CheckBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_CheckBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeBase, NativeBaseClass, avmshell::NativeBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeBaseClass, avmshell::NativeBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeBaseAS3, NativeBaseAS3Class, avmplus::NativeBaseAS3Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseAS3Class, avmplus::NativeBaseAS3Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseAS3Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_ShellCoreFriend1, ShellCoreFriend1Class, avmplus::ShellCoreFriend1Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ShellCoreFriend1Class, avmplus::ShellCoreFriend1Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ShellCoreFriend1Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_ShellCoreFriend2, ShellCoreFriend2Class, avmplus::ShellCoreFriend2Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ShellCoreFriend2Class, avmplus::ShellCoreFriend2Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ShellCoreFriend2Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_Capabilities, CapabilitiesClass, avmplus::CapabilitiesClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_CapabilitiesClass, avmplus::CapabilitiesObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_CapabilitiesObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class, public_classClass, avmplus::public_classClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_classClass, avmplus::public_classObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_classObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_0, public_class_AIR_1_0Class, avmplus::public_class_AIR_1_0Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_0Class, avmplus::public_class_AIR_1_0Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_0Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_FP_10_0, public_class_FP_10_0Class, avmplus::public_class_FP_10_0Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0Class, avmplus::public_class_FP_10_0Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_5, public_class_AIR_1_5Class, avmplus::public_class_AIR_1_5Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5Class, avmplus::public_class_AIR_1_5Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_5_1, public_class_AIR_1_5_1Class, avmplus::public_class_AIR_1_5_1Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_1Class, avmplus::public_class_AIR_1_5_1Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_1Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_FP_10_0_32, public_class_FP_10_0_32Class, avmplus::public_class_FP_10_0_32Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0_32Class, avmplus::public_class_FP_10_0_32Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0_32Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_5_2, public_class_AIR_1_5_2Class, avmplus::public_class_AIR_1_5_2Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_2Class, avmplus::public_class_AIR_1_5_2Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_2Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_0_FP_10_0, public_class_AIR_1_0_FP_10_0Class, avmplus::public_class_AIR_1_0_FP_10_0Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_0_FP_10_0Class, avmplus::public_class_AIR_1_0_FP_10_0Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_0_FP_10_0Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2, public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class, avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class, avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_public_class_FP_10_0_32_AIR_1_0_FP_10_0, public_class_FP_10_0_32_AIR_1_0_FP_10_0Class, avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class, avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeSubclassOfAbstractBase, NativeSubclassOfAbstractBaseClass, avmshell::NativeSubclassOfAbstractBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfAbstractBaseClass, avmshell::NativeSubclassOfAbstractBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfAbstractBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_SubclassOfAbstractBase, SubclassOfAbstractBaseClass, avmplus::SubclassOfAbstractBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfAbstractBaseClass, avmplus::SubclassOfAbstractBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfAbstractBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeSubclassOfRestrictedBase, NativeSubclassOfRestrictedBaseClass, avmshell::NativeSubclassOfRestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfRestrictedBaseClass, avmshell::NativeSubclassOfRestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfRestrictedBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_SubclassOfRestrictedBase, SubclassOfRestrictedBaseClass, avmplus::SubclassOfRestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfRestrictedBaseClass, avmplus::SubclassOfRestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfRestrictedBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeSubclassOfAbstractRestrictedBase, NativeSubclassOfAbstractRestrictedBaseClass, avmshell::NativeSubclassOfAbstractRestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfAbstractRestrictedBaseClass, avmshell::NativeSubclassOfAbstractRestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_NativeSubclassOfAbstractRestrictedBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_SubclassOfAbstractRestrictedBase, SubclassOfAbstractRestrictedBaseClass, avmplus::SubclassOfAbstractRestrictedBaseClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfAbstractRestrictedBaseClass, avmplus::SubclassOfAbstractRestrictedBaseObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SubclassOfAbstractRestrictedBaseObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeBaseExtender1, NativeBaseExtender1Class, avmplus::NativeBaseExtender1Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseExtender1Class, avmplus::NativeBaseExtender1Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseExtender1Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmshell_NativeBaseExtender2, NativeBaseExtender2Class, avmplus::NativeBaseExtender2Class, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseExtender2Class, avmplus::NativeBaseExtender2Object, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NativeBaseExtender2Object, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_avmplus_Domain, DomainClass, avmplus::DomainClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_DomainClass, avmplus::DomainObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_DomainObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_sampler_StackFrame, StackFrameClass, avmplus::StackFrameClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_StackFrameClass, avmplus::StackFrameObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_StackFrameObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_sampler_Sample, SampleClass, avmplus::SampleClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SampleClass, avmplus::SampleObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_SampleObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_sampler_ClassFactory, ClassFactoryClass, avmplus::ClassFactoryClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ClassFactoryClass, avmplus::ClassFactoryObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_ClassFactoryObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_sampler_NewObjectSample, NewObjectSampleClass, avmplus::NewObjectSampleClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NewObjectSampleClass, avmplus::NewObjectSampleObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_NewObjectSampleObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_sampler_DeleteObjectSample, DeleteObjectSampleClass, avmplus::DeleteObjectSampleClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_DeleteObjectSampleClass, avmplus::DeleteObjectSampleObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_DeleteObjectSampleObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_trace_Trace, TraceClass, avmplus::TraceClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_TraceClass, avmplus::TraceObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_TraceObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_Endian, EndianClass, avmplus::EndianClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_EndianClass, avmplus::EndianObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_EndianObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_WorkerState, WorkerStateClass, avmplus::WorkerStateClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_WorkerStateClass, avmplus::WorkerStateObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_WorkerStateObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_Worker, ShellWorkerClass, avmshell::ShellWorkerClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_ShellWorkerClass, avmshell::ShellWorkerObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_ShellWorkerObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_WorkerEvent, WorkerEventClass, avmplus::WorkerEventClass, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_WorkerEventClass, avmplus::WorkerEventObject, SlotOffsetsAndAsserts::kSlotsOffset_avmplus_WorkerEventObject, false, false, false)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_WorkerDomain, ShellWorkerDomainClass, avmshell::ShellWorkerDomainClass, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_ShellWorkerDomainClass, avmshell::ShellWorkerDomainObject, SlotOffsetsAndAsserts::kSlotsOffset_avmshell_ShellWorkerDomainObject, false, false, false)
    AVMTHUNK_END_NATIVE_CLASSES()

AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(shell_toplevel)

/* abc */
const uint8_t shell_toplevel_abc_data[18376] = {
  16,   0,  46,   0,   8,  42, 101,   0,   2,   1,   3,   4,   0,   8,   0,   0,
   0,   0,   0,   0, 232,  63,   0,   0,   0,   0,   0,   0, 240,  63,   0,   0,
   0,   0,   0,   0,   0,  64,   0,   0,   0,   0,   0,   0,   8,  64,   0,   0,
   0,   0,   0,   0,  16,  64,   0,   0,   0,   0,   0,   0,  20,  64,   0,   0,
   0,   0,   0,   0,  24,  64, 165,   3,   0,   4, 118, 111, 105, 100,   7,  66,
 111, 111, 108, 101,  97, 110,   6,  83, 121, 115, 116, 101, 109,  19, 115, 104,
 101, 108, 108,  95, 116, 111, 112, 108, 101, 118, 101, 108,  46,  97, 115,  36,
  49,   7,  97, 118, 109, 112, 108, 117, 115,   5, 100, 101, 111, 112, 116,   8,
 114, 101,  97, 100,  76, 105, 110, 101,   6,  83, 116, 114, 105, 110, 103,   8,
 103, 101, 116,  84, 105, 109, 101, 114,   4, 117, 105, 110, 116,   5, 116, 114,
  97,  99, 101,   6,  68, 111, 109,  97, 105, 110,  13,  99, 117, 114, 114, 101,
 110, 116,  68, 111, 109,  97, 105, 110,   8, 103, 101, 116,  67, 108,  97, 115,
 115,   5,  67, 108,  97, 115, 115,   8, 100, 101,  98, 117, 103, 103, 101, 114,
  13,  97, 118, 109, 112, 108, 117, 115,  58,  73,  84, 101, 115, 116,   4, 116,
 101, 115, 116,   5,  73,  84, 101, 115, 116,  13,  97, 118, 109, 112, 108, 117,
 115,  58,  67,  84, 101, 115, 116,   3, 238, 138, 148,   5,  67,  84, 101, 115,
 116,   6,  79,  98, 106, 101,  99, 116,  10,  97, 118, 109, 112, 108, 117, 115,
  58,  77,  73,   6,  78, 117, 109,  98, 101, 114,   4, 112, 108, 117, 115,   2,
  77,  73,  14,  97, 118, 109, 112, 108, 117, 115,  58,  83, 121, 115, 116, 101,
 109,   4,  97, 114, 103, 118,   7, 103, 101, 116,  65, 114, 103, 118,   3, 105,
 110, 116,   5,  65, 114, 114,  97, 121,   3,  88,  77,  76,  11,  95,  95,  65,
  83,  51,  95,  95,  46, 118, 101,  99,   6,  86, 101,  99, 116, 111, 114,   8,
  70, 117, 110,  99, 116, 105, 111, 110,   4, 101, 120, 105, 116,   3, 102, 111,
 111,   4, 101, 120, 101,  99,   3,  98,  97, 114,   4,  97, 116, 116, 114,   8,
 119, 104,  97, 116, 101, 118, 101, 114,   5, 115, 108, 101, 101, 112,  17, 103,
 101, 116,  65, 118, 109, 112, 108, 117, 115,  86, 101, 114, 115, 105, 111, 110,
  11, 103, 101, 116,  70, 101,  97, 116, 117, 114, 101, 115,  10, 103, 101, 116,
  82, 117, 110, 109, 111, 100, 101,   5, 119, 114, 105, 116, 101,  10, 105, 115,
  68, 101,  98, 117, 103, 103, 101, 114,  18, 103, 101, 116,  78,  97, 110, 111,
 115, 101,  99, 111, 110, 100,  84, 105, 109, 101, 114,  11, 116, 111, 116,  97,
 108,  77, 101, 109, 111, 114, 121,  10, 102, 114, 101, 101,  77, 101, 109, 111,
 114, 121,  13, 112, 114, 105, 118,  97, 116, 101,  77, 101, 109, 111, 114, 121,
  19, 102, 111, 114,  99, 101,  70, 117, 108, 108,  67, 111, 108, 108, 101,  99,
 116, 105, 111, 110,  15, 113, 117, 101, 117, 101,  67, 111, 108, 108, 101,  99,
 116, 105, 111, 110,  22, 104, 116, 116, 112,  58,  47,  47, 119, 119, 119,  46,
 101, 120,  97, 109, 112, 108, 101,  46,  99, 111, 109,   6, 110, 115, 116, 101,
 115, 116,   8, 105, 115,  71, 108, 111,  98,  97, 108,  10, 115, 119, 102,  86,
 101, 114, 115, 105, 111, 110,  10,  97, 112, 105,  86, 101, 114, 115, 105, 111,
 110,  10, 100, 105, 115, 112, 111, 115, 101,  88,  77,  76,  21, 115, 109,  97,
 115, 104,  79,  98, 106, 101,  99, 116,  86, 101,  99, 116, 111, 114,  83, 105,
 122, 101,  18, 115, 109,  97, 115, 104,  73, 110, 116,  86, 101,  99, 116, 111,
 114,  83, 105, 122, 101,  19, 115, 109,  97, 115, 104,  85,  73, 110, 116,  86,
 101,  99, 116, 111, 114,  83, 105, 122, 101,  21, 115, 109,  97, 115, 104,  68,
 111, 117,  98, 108, 101,  86, 101,  99, 116, 111, 114,  83, 105, 122, 101,  30,
 112,  97, 117, 115, 101,  70, 111, 114,  71,  67,  73, 102,  67, 111, 108, 108,
 101,  99, 116, 105, 111, 110,  73, 109, 109, 105, 110, 101, 110, 116,   7, 105,
 115,  54,  52,  98, 105, 116,   8, 105, 115,  73, 110, 116, 112, 116, 114,  14,
 114, 117, 110,  73, 110,  83,  97, 102, 101, 112, 111, 105, 110, 116,  18,  99,
  97, 110, 111, 110, 105,  99,  97, 108, 105, 122, 101,  78, 117, 109,  98, 101,
 114,  12,  97, 118, 109, 112, 108, 117, 115,  58,  70, 105, 108, 101,  11, 102,
 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,   9,  66, 121, 116, 101,  65,
 114, 114,  97, 121,   6, 101, 120, 105, 115, 116, 115,   4, 114, 101,  97, 100,
  13, 114, 101,  97, 100,  66, 121, 116, 101,  65, 114, 114,  97, 121,  14, 119,
 114, 105, 116, 101,  66, 121, 116, 101,  65, 114, 114,  97, 121,   4,  70, 105,
 108, 101,  21,  97, 118, 109, 115, 104, 101, 108, 108,  58,  65,  98, 115, 116,
 114,  97,  99, 116,  66,  97, 115, 101,   8,  97, 118, 109, 115, 104, 101, 108,
 108,  12,  65,  98, 115, 116, 114,  97,  99, 116,  66,  97, 115, 101,  23,  97,
 118, 109, 115, 104, 101, 108, 108,  58,  82, 101, 115, 116, 114, 105,  99, 116,
 101, 100,  66,  97, 115, 101,  14,  82, 101, 115, 116, 114, 105,  99, 116, 101,
 100,  66,  97, 115, 101,  31,  97, 118, 109, 115, 104, 101, 108, 108,  58,  65,
  98, 115, 116, 114,  97,  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101,
 100,  66,  97, 115, 101,  22,  65,  98, 115, 116, 114,  97,  99, 116,  82, 101,
 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  18,  97, 118, 109,
 115, 104, 101, 108, 108,  58,  67, 104, 101,  99, 107,  66,  97, 115, 101,   9,
  67, 104, 101,  99, 107,  66,  97, 115, 101,  19,  97, 118, 109, 115, 104, 101,
 108, 108,  58,  78,  97, 116, 105, 118, 101,  66,  97, 115, 101,  10,  78,  97,
 116, 105, 118, 101,  66,  97, 115, 101,  22,  97, 118, 109, 115, 104, 101, 108,
 108,  58,  78,  97, 116, 105, 118, 101,  66,  97, 115, 101,  65,  83,  51,  13,
  78,  97, 116, 105, 118, 101,  66,  97, 115, 101,  65,  83,  51,  25,  97, 118,
 109, 115, 104, 101, 108, 108,  58,  83, 104, 101, 108, 108,  67, 111, 114, 101,
  70, 114, 105, 101, 110, 100,  49,  16,  83, 104, 101, 108, 108,  67, 111, 114,
 101,  70, 114, 105, 101, 110, 100,  49,  25,  97, 118, 109, 115, 104, 101, 108,
 108,  58,  83, 104, 101, 108, 108,  67, 111, 114, 101,  70, 114, 105, 101, 110,
 100,  50,  16,  83, 104, 101, 108, 108,  67, 111, 114, 101,  70, 114, 105, 101,
 110, 100,  50,  25, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,
  58,  67,  97, 112,  97,  98, 105, 108, 105, 116, 105, 101, 115,   7,  65,  86,
  77,  80, 108, 117, 115,  12, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116,
 101, 109,  10, 112, 108,  97, 121, 101, 114,  84, 121, 112, 101,  12,  67,  97,
 112,  97,  98, 105, 108, 105, 116, 105, 101, 115,  21,  97, 118, 109, 115, 104,
 101, 108, 108,  58, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,
  10, 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,   3, 238, 138, 149,  18,
 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,  65,  73,  82,  95,  49,
  95,  48,   3,  65,  80,  73,   3,  54,  54,  49,   3, 238, 138, 150,  18, 112,
 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,  70,  80,  95,  49,  48,  95,
  48,   3,  54,  54,  50,   3, 238, 138, 151,  18, 112, 117,  98, 108, 105,  99,
  95, 118,  97, 114,  95,  65,  73,  82,  95,  49,  95,  53,   3,  54,  54,  51,
   3, 238, 138, 152,  20, 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,
  65,  73,  82,  95,  49,  95,  53,  95,  49,   3,  54,  54,  52,   3, 238, 138,
 153,  21, 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,  70,  80,  95,
  49,  48,  95,  48,  95,  51,  50,   3,  54,  54,  53,   3, 238, 138, 154,  20,
 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,  65,  73,  82,  95,  49,
  95,  53,  95,  50,   3,  54,  54,  54,  26, 112, 117,  98, 108, 105,  99,  95,
 118,  97, 114,  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,  49,
  48,  95,  48,  38, 112, 117,  98, 108, 105,  99,  95, 118,  97, 114,  95,  65,
  73,  82,  95,  49,  95,  53,  95,  49,  95,  70,  80,  95,  49,  48,  95,  48,
  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  37, 112, 117,  98, 108, 105,
  99,  95, 118,  97, 114,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,
  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,
  12, 112, 117,  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,  20, 112, 117,
  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,  95,  65,  73,  82,  95,  49,
  95,  48,  20, 112, 117,  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,  95,
  70,  80,  95,  49,  48,  95,  48,  20, 112, 117,  98, 108, 105,  99,  95,  99,
 111, 110, 115, 116,  95,  65,  73,  82,  95,  49,  95,  53,  22, 112, 117,  98,
 108, 105,  99,  95,  99, 111, 110, 115, 116,  95,  65,  73,  82,  95,  49,  95,
  53,  95,  49,  23, 112, 117,  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,
  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  22, 112, 117,  98, 108,
 105,  99,  95,  99, 111, 110, 115, 116,  95,  65,  73,  82,  95,  49,  95,  53,
  95,  50,  28, 112, 117,  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,  95,
  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,  40,
 112, 117,  98, 108, 105,  99,  95,  99, 111, 110, 115, 116,  95,  65,  73,  82,
  95,  49,  95,  53,  95,  49,  95,  70,  80,  95,  49,  48,  95,  48,  95,  65,
  73,  82,  95,  49,  95,  53,  95,  50,  39, 112, 117,  98, 108, 105,  99,  95,
  99, 111, 110, 115, 116,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,
  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,
  15, 112, 117,  98, 108, 105,  99,  95, 102, 117, 110,  99, 116, 105, 111, 110,
  23, 112, 117,  98, 108, 105,  99,  95, 102, 117, 110,  99, 116, 105, 111, 110,
  95,  65,  73,  82,  95,  49,  95,  48,  23, 112, 117,  98, 108, 105,  99,  95,
 102, 117, 110,  99, 116, 105, 111, 110,  95,  70,  80,  95,  49,  48,  95,  48,
  23, 112, 117,  98, 108, 105,  99,  95, 102, 117, 110,  99, 116, 105, 111, 110,
  95,  65,  73,  82,  95,  49,  95,  53,  25, 112, 117,  98, 108, 105,  99,  95,
 102, 117, 110,  99, 116, 105, 111, 110,  95,  65,  73,  82,  95,  49,  95,  53,
  95,  49,  26, 112, 117,  98, 108, 105,  99,  95, 102, 117, 110,  99, 116, 105,
 111, 110,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  25, 112, 117,
  98, 108, 105,  99,  95, 102, 117, 110,  99, 116, 105, 111, 110,  95,  65,  73,
  82,  95,  49,  95,  53,  95,  50,  31, 112, 117,  98, 108, 105,  99,  95, 102,
 117, 110,  99, 116, 105, 111, 110,  95,  65,  73,  82,  95,  49,  95,  48,  95,
  70,  80,  95,  49,  48,  95,  48,  43, 112, 117,  98, 108, 105,  99,  95, 102,
 117, 110,  99, 116, 105, 111, 110,  95,  65,  73,  82,  95,  49,  95,  53,  95,
  49,  95,  70,  80,  95,  49,  48,  95,  48,  95,  65,  73,  82,  95,  49,  95,
  53,  95,  50,  42, 112, 117,  98, 108, 105,  99,  95, 102, 117, 110,  99, 116,
 105, 111, 110,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  95,  65,
  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,  13, 112,
 117,  98, 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,  21, 112, 117,  98,
 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,  95,  65,  73,  82,  95,  49,
  95,  48,  21, 112, 117,  98, 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,
  95,  70,  80,  95,  49,  48,  95,  48,  21, 112, 117,  98, 108, 105,  99,  95,
 103, 101, 116, 115, 101, 116,  95,  65,  73,  82,  95,  49,  95,  53,  23, 112,
 117,  98, 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,  95,  65,  73,  82,
  95,  49,  95,  53,  95,  49,  24, 112, 117,  98, 108, 105,  99,  95, 103, 101,
 116, 115, 101, 116,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  23,
 112, 117,  98, 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,  95,  65,  73,
  82,  95,  49,  95,  53,  95,  50,  29, 112, 117,  98, 108, 105,  99,  95, 103,
 101, 116, 115, 101, 116,  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,
  95,  49,  48,  95,  48,  41, 112, 117,  98, 108, 105,  99,  95, 103, 101, 116,
 115, 101, 116,  95,  65,  73,  82,  95,  49,  95,  53,  95,  49,  95,  70,  80,
  95,  49,  48,  95,  48,  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  40,
 112, 117,  98, 108, 105,  99,  95, 103, 101, 116, 115, 101, 116,  95,  70,  80,
  95,  49,  48,  95,  48,  95,  51,  50,  95,  65,  73,  82,  95,  49,  95,  48,
  95,  70,  80,  95,  49,  48,  95,  48,  12, 112, 117,  98, 108, 105,  99,  95,
  99, 108,  97, 115, 115,  29,  97, 118, 109, 115, 104, 101, 108, 108,  58, 112,
 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,
  49,  95,  48,  20, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,
  95,  65,  73,  82,  95,  49,  95,  48,  29,  97, 118, 109, 115, 104, 101, 108,
 108,  58, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  70,
  80,  95,  49,  48,  95,  48,  20, 112, 117,  98, 108, 105,  99,  95,  99, 108,
  97, 115, 115,  95,  70,  80,  95,  49,  48,  95,  48,  29,  97, 118, 109, 115,
 104, 101, 108, 108,  58, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115,
 115,  95,  65,  73,  82,  95,  49,  95,  53,  20, 112, 117,  98, 108, 105,  99,
  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,  49,  95,  53,  31,  97,
 118, 109, 115, 104, 101, 108, 108,  58, 112, 117,  98, 108, 105,  99,  95,  99,
 108,  97, 115, 115,  95,  65,  73,  82,  95,  49,  95,  53,  95,  49,  22, 112,
 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,
  49,  95,  53,  95,  49,  32,  97, 118, 109, 115, 104, 101, 108, 108,  58, 112,
 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  70,  80,  95,  49,
  48,  95,  48,  95,  51,  50,  23, 112, 117,  98, 108, 105,  99,  95,  99, 108,
  97, 115, 115,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  31,  97,
 118, 109, 115, 104, 101, 108, 108,  58, 112, 117,  98, 108, 105,  99,  95,  99,
 108,  97, 115, 115,  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  22, 112,
 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,
  49,  95,  53,  95,  50,  37,  97, 118, 109, 115, 104, 101, 108, 108,  58, 112,
 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,
  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,  28, 112, 117,  98, 108,
 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,  49,  95,  48,
  95,  70,  80,  95,  49,  48,  95,  48,  49,  97, 118, 109, 115, 104, 101, 108,
 108,  58, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  65,
  73,  82,  95,  49,  95,  53,  95,  49,  95,  70,  80,  95,  49,  48,  95,  48,
  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  40, 112, 117,  98, 108, 105,
  99,  95,  99, 108,  97, 115, 115,  95,  65,  73,  82,  95,  49,  95,  53,  95,
  49,  95,  70,  80,  95,  49,  48,  95,  48,  95,  65,  73,  82,  95,  49,  95,
  53,  95,  50,  48,  97, 118, 109, 115, 104, 101, 108, 108,  58, 112, 117,  98,
 108, 105,  99,  95,  99, 108,  97, 115, 115,  95,  70,  80,  95,  49,  48,  95,
  48,  95,  51,  50,  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,
  49,  48,  95,  48,  39, 112, 117,  98, 108, 105,  99,  95,  99, 108,  97, 115,
 115,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  95,  65,  73,  82,
  95,  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,  16, 112, 117,  98,
 108, 105,  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,  24, 112, 117,
  98, 108, 105,  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,  95,  65,
  73,  82,  95,  49,  95,  48,  24, 112, 117,  98, 108, 105,  99,  95, 105, 110,
 116, 101, 114, 102,  97,  99, 101,  95,  70,  80,  95,  49,  48,  95,  48,  24,
 112, 117,  98, 108, 105,  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,
  95,  65,  73,  82,  95,  49,  95,  53,  26, 112, 117,  98, 108, 105,  99,  95,
 105, 110, 116, 101, 114, 102,  97,  99, 101,  95,  65,  73,  82,  95,  49,  95,
  53,  95,  49,  27, 112, 117,  98, 108, 105,  99,  95, 105, 110, 116, 101, 114,
 102,  97,  99, 101,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  26,
 112, 117,  98, 108, 105,  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,
  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  32, 112, 117,  98, 108, 105,
  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,  95,  65,  73,  82,  95,
  49,  95,  48,  95,  70,  80,  95,  49,  48,  95,  48,  44, 112, 117,  98, 108,
 105,  99,  95, 105, 110, 116, 101, 114, 102,  97,  99, 101,  95,  65,  73,  82,
  95,  49,  95,  53,  95,  49,  95,  70,  80,  95,  49,  48,  95,  48,  95,  65,
  73,  82,  95,  49,  95,  53,  95,  50,  43, 112, 117,  98, 108, 105,  99,  95,
 105, 110, 116, 101, 114, 102,  97,  99, 101,  95,  70,  80,  95,  49,  48,  95,
  48,  95,  51,  50,  95,  65,  73,  82,  95,  49,  95,  48,  95,  70,  80,  95,
  49,  48,  95,  48,  37,  97, 118, 109, 115, 104, 101, 108, 108,  58,  78,  97,
 116, 105, 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98,
 115, 116, 114,  97,  99, 116,  66,  97, 115, 101,  28,  78,  97, 116, 105, 118,
 101,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116, 114,
  97,  99, 116,  66,  97, 115, 101,  31,  97, 118, 109, 115, 104, 101, 108, 108,
  58,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116, 114,
  97,  99, 116,  66,  97, 115, 101,  22,  83, 117,  98,  99, 108,  97, 115, 115,
  79, 102,  65,  98, 115, 116, 114,  97,  99, 116,  66,  97, 115, 101,  39,  97,
 118, 109, 115, 104, 101, 108, 108,  58,  78,  97, 116, 105, 118, 101,  83, 117,
  98,  99, 108,  97, 115, 115,  79, 102,  82, 101, 115, 116, 114, 105,  99, 116,
 101, 100,  66,  97, 115, 101,  30,  78,  97, 116, 105, 118, 101,  83, 117,  98,
  99, 108,  97, 115, 115,  79, 102,  82, 101, 115, 116, 114, 105,  99, 116, 101,
 100,  66,  97, 115, 101,  33,  97, 118, 109, 115, 104, 101, 108, 108,  58,  83,
 117,  98,  99, 108,  97, 115, 115,  79, 102,  82, 101, 115, 116, 114, 105,  99,
 116, 101, 100,  66,  97, 115, 101,  24,  83, 117,  98,  99, 108,  97, 115, 115,
  79, 102,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,
  47,  97, 118, 109, 115, 104, 101, 108, 108,  58,  78,  97, 116, 105, 118, 101,
  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116, 114,  97,
  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,
  38,  78,  97, 116, 105, 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,  79,
 102,  65,  98, 115, 116, 114,  97,  99, 116,  82, 101, 115, 116, 114, 105,  99,
 116, 101, 100,  66,  97, 115, 101,  41,  97, 118, 109, 115, 104, 101, 108, 108,
  58,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116, 114,
  97,  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115,
 101,  32,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116,
 114,  97,  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97,
 115, 101,  28,  97, 118, 109, 115, 104, 101, 108, 108,  58,  78,  97, 116, 105,
 118, 101,  66,  97, 115, 101,  69, 120, 116, 101, 110, 100, 101, 114,  49,  19,
  78,  97, 116, 105, 118, 101,  66,  97, 115, 101,  69, 120, 116, 101, 110, 100,
 101, 114,  49,  28,  97, 118, 109, 115, 104, 101, 108, 108,  58,  78,  97, 116,
 105, 118, 101,  66,  97, 115, 101,  69, 120, 116, 101, 110, 100, 101, 114,  50,
   4, 102, 111, 111,  49,   4, 102, 111, 111,  50,  19,  78,  97, 116, 105, 118,
 101,  66,  97, 115, 101,  69, 120, 116, 101, 110, 100, 101, 114,  50,  11,  65,
  80,  73,  95,  65,  73,  82,  95,  49,  95,  48,  11,  65,  80,  73,  95,  70,
  80,  95,  49,  48,  95,  48,  11,  65,  80,  73,  95,  65,  73,  82,  95,  49,
  95,  53,  13,  65,  80,  73,  95,  65,  73,  82,  95,  49,  95,  53,  95,  49,
  14,  65,  80,  73,  95,  70,  80,  95,  49,  48,  95,  48,  95,  51,  50,  13,
  65,  80,  73,  95,  65,  73,  82,  95,  49,  95,  53,  95,  50,  10, 110, 115,
  95, 101, 120,  97, 109, 112, 108, 101,   6, 110,  97, 116, 105, 118, 101,   3,
  99, 108, 115,  19,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,
  77,  73,  67, 108,  97, 115, 115,   8, 105, 110, 115, 116,  97, 110,  99, 101,
  20,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  77,  73,  79,
  98, 106, 101,  99, 116,   7, 109, 101, 116, 104, 111, 100, 115,  24,  58,  58,
  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  77,  73,  79,  98, 106, 101,
  99, 116,  73, 109, 112, 108,  10,  97, 118, 109, 112, 108, 117, 115, 238, 138,
 148,  23,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  83, 121,
 115, 116, 101, 109,  67, 108,  97, 115, 115,   7,  99, 108,  97, 115, 115, 103,
  99,   5, 101, 120,  97,  99, 116,   4,  97, 117, 116, 111,   9,  99, 111, 110,
 115, 116, 114, 117,  99, 116,   4, 110, 111, 110, 101,  21,  58,  58,  97, 118,
 109, 115, 104, 101, 108, 108,  58,  58,  70, 105, 108, 101,  67, 108,  97, 115,
 115,  11,  97, 118, 109, 115, 104, 101, 108, 108, 238, 138, 148,  29,  58,  58,
  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  65,  98, 115, 116, 114,  97,
  99, 116,  66,  97, 115, 101,  67, 108,  97, 115, 115,  30,  58,  58,  97, 118,
 109, 115, 104, 101, 108, 108,  58,  58,  65,  98, 115, 116, 114,  97,  99, 116,
  66,  97, 115, 101,  79,  98, 106, 101,  99, 116,   2, 103,  99,   8,  97,  98,
 115, 116, 114,  97,  99, 116,  45,  58,  58,  97, 118, 109, 115, 104, 101, 108,
 108,  58,  58,  78,  97, 116, 105, 118, 101,  83, 117,  98,  99, 108,  97, 115,
 115,  79, 102,  65,  98, 115, 116, 114,  97,  99, 116,  66,  97, 115, 101,  67,
 108,  97, 115, 115,  46,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,
  58,  78,  97, 116, 105, 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,  79,
 102,  65,  98, 115, 116, 114,  97,  99, 116,  66,  97, 115, 101,  79,  98, 106,
 101,  99, 116,  31,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,
  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  67, 108,
  97, 115, 115,  32,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,
  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  79,  98,
 106, 101,  99, 116,  10, 114, 101, 115, 116, 114, 105,  99, 116, 101, 100,  47,
  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  78,  97, 116, 105,
 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  82, 101, 115, 116,
 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  67, 108,  97, 115, 115,  48,
  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  78,  97, 116, 105,
 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  82, 101, 115, 116,
 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  79,  98, 106, 101,  99, 116,
  39,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  65,  98, 115,
 116, 114,  97,  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,
  97, 115, 101,  67, 108,  97, 115, 115,  40,  58,  58,  97, 118, 109, 115, 104,
 101, 108, 108,  58,  58,  65,  98, 115, 116, 114,  97,  99, 116,  82, 101, 115,
 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,  79,  98, 106, 101,  99,
 116,  19,  97,  98, 115, 116, 114,  97,  99, 116,  45, 114, 101, 115, 116, 114,
 105,  99, 116, 101, 100,  55,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,
  58,  58,  78,  97, 116, 105, 118, 101,  83, 117,  98,  99, 108,  97, 115, 115,
  79, 102,  65,  98, 115, 116, 114,  97,  99, 116,  82, 101, 115, 116, 114, 105,
  99, 116, 101, 100,  66,  97, 115, 101,  67, 108,  97, 115, 115,  56,  58,  58,
  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  78,  97, 116, 105, 118, 101,
  83, 117,  98,  99, 108,  97, 115, 115,  79, 102,  65,  98, 115, 116, 114,  97,
  99, 116,  82, 101, 115, 116, 114, 105,  99, 116, 101, 100,  66,  97, 115, 101,
  79,  98, 106, 101,  99, 116,  26,  58,  58,  97, 118, 109, 115, 104, 101, 108,
 108,  58,  58,  67, 104, 101,  99, 107,  66,  97, 115, 101,  67, 108,  97, 115,
 115,  27,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  67, 104,
 101,  99, 107,  66,  97, 115, 101,  79,  98, 106, 101,  99, 116,   5,  99, 104,
 101,  99, 107,  27,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,
  78,  97, 116, 105, 118, 101,  66,  97, 115, 101,  67, 108,  97, 115, 115,  28,
  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  78,  97, 116, 105,
 118, 101,  66,  97, 115, 101,  79,  98, 106, 101,  99, 116,   6, 102, 114, 105,
 101, 110, 100,  19,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  83, 104,
 101, 108, 108,  67, 111, 114, 101,  43,  97, 118, 109, 115, 104, 101, 108, 108,
  58,  58,  83, 104, 101, 108, 108,  67, 111, 114, 101,  44,  97, 118, 109, 115,
 104, 101, 108, 108,  58,  58,  83, 104, 101, 108, 108,  84, 111, 112, 108, 101,
 118, 101, 108,  15, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,
 238, 138, 148,  14, 103, 101, 116,  67, 108,  97, 115, 115,  66, 121,  78,  97,
 109, 101,   5, 112, 114, 105, 110, 116,  11,  97, 118, 109, 115, 104, 101, 108,
 108, 238, 138, 149,  11,  97, 118, 109, 115, 104, 101, 108, 108, 238, 138, 150,
  11,  97, 118, 109, 115, 104, 101, 108, 108, 238, 138, 151,  11,  97, 118, 109,
 115, 104, 101, 108, 108, 238, 138, 152,  11,  97, 118, 109, 115, 104, 101, 108,
 108, 238, 138, 153,  11,  97, 118, 109, 115, 104, 101, 108, 108, 238, 138, 154,
  14,  97, 118, 109, 112, 108, 117, 115,  58,  68, 111, 109,  97, 105, 110,   4,
 105, 110, 105, 116,  11,  68, 111, 109,  97, 105, 110,  46,  97, 115,  36,  50,
   9, 108, 111,  97, 100,  66, 121, 116, 101, 115,  24,  77,  73,  78,  95,  68,
  79,  77,  65,  73,  78,  95,  77,  69,  77,  79,  82,  89,  95,  76,  69,  78,
  71,  84,  72,   4, 108, 111,  97, 100,  12, 100, 111, 109,  97, 105, 110,  77,
 101, 109, 111, 114, 121,  11,  68, 111, 109,  97, 105, 110,  67, 108,  97, 115,
 115,  12,  68, 111, 109,  97, 105, 110,  79,  98, 106, 101,  99, 116,   5,  81,
  78,  97, 109, 101,  19,  95, 103, 101, 116,  73, 110, 118, 111,  99,  97, 116,
 105, 111, 110,  67, 111, 117, 110, 116,  12,  83,  97, 109, 112, 108, 101, 114,
  46,  97, 115,  36,  51,  13, 102, 108,  97, 115, 104,  46, 115,  97, 109, 112,
 108, 101, 114,  11,  95, 103, 101, 116,  83,  97, 109, 112, 108, 101, 115,   1,
 102,   1, 101,   3, 114, 101, 116,  19,  95, 115, 101, 116,  83,  97, 109, 112,
 108, 101, 114,  67,  97, 108, 108,  98,  97,  99, 107,   7, 119, 114,  97, 112,
 112, 101, 114,  24, 102, 108,  97, 115, 104,  46, 115,  97, 109, 112, 108, 101,
 114,  58,  83, 116,  97,  99, 107,  70, 114,  97, 109, 101,   4, 110,  97, 109,
 101,   2,  40,  41,   4, 102, 105, 108, 101,   1,  91,   1,  58,   4, 108, 105,
 110, 101,   1,  93,   8, 115,  99, 114, 105, 112, 116,  73,  68,   8, 116, 111,
  83, 116, 114, 105, 110, 103,  10,  83, 116,  97,  99, 107,  70, 114,  97, 109,
 101,  20, 102, 108,  97, 115, 104,  46, 115,  97, 109, 112, 108, 101, 114,  58,
  83,  97, 109, 112, 108, 101,   4, 116, 105, 109, 101,   5, 115, 116,  97,  99,
 107,   6,  83,  97, 109, 112, 108, 101,  26, 102, 108,  97, 115, 104,  46, 115,
  97, 109, 112, 108, 101, 114,  58,  67, 108,  97, 115, 115,  70,  97,  99, 116,
 111, 114, 121,  15,  83, 116,  97,  99, 107,  70, 114,  97, 109, 101,  67, 108,
  97, 115, 115,  11,  83,  97, 109, 112, 108, 101,  67, 108,  97, 115, 115,  23,
  68, 101, 108, 101, 116, 101,  79,  98, 106, 101,  99, 116,  83,  97, 109, 112,
 108, 101,  67, 108,  97, 115, 115,  20,  78, 101, 119,  79,  98, 106, 101,  99,
 116,  83,  97, 109, 112, 108, 101,  67, 108,  97, 115, 115,  12,  67, 108,  97,
 115, 115,  70,  97,  99, 116, 111, 114, 121,  29, 102, 108,  97, 115, 104,  46,
 115,  97, 109, 112, 108, 101, 114,  58,  78, 101, 119,  79,  98, 106, 101,  99,
 116,  83,  97, 109, 112, 108, 101,   2, 105, 100,   4, 116, 121, 112, 101,   6,
 111,  98, 106, 101,  99, 116,   4, 115, 105, 122, 101,  15,  78, 101, 119,  79,
  98, 106, 101,  99, 116,  83,  97, 109, 112, 108, 101,  32, 102, 108,  97, 115,
 104,  46, 115,  97, 109, 112, 108, 101, 114,  58,  68, 101, 108, 101, 116, 101,
  79,  98, 106, 101,  99, 116,  83,  97, 109, 112, 108, 101,  18,  68, 101, 108,
 101, 116, 101,  79,  98, 106, 101,  99, 116,  83,  97, 109, 112, 108, 101,  16,
 102, 108,  97, 115, 104,  46, 115,  97, 109, 112, 108, 101, 114, 238, 138, 148,
  21,  78, 101, 119,  79,  98, 106, 101,  99, 116,  83,  97, 109, 112, 108, 101,
  79,  98, 106, 101,  99, 116,  12,  99, 108, 101,  97, 114,  83,  97, 109, 112,
 108, 101, 115,  27,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112,
 116,  58,  58,  99, 108, 101,  97, 114,  83,  97, 109, 112, 108, 101, 115,  13,
 115, 116,  97, 114, 116,  83,  97, 109, 112, 108, 105, 110, 103,  28,  83,  97,
 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,  58, 115, 116,  97,
 114, 116,  83,  97, 109, 112, 108, 105, 110, 103,  12, 115, 116, 111, 112,  83,
  97, 109, 112, 108, 105, 110, 103,  27,  83,  97, 109, 112, 108, 101, 114,  83,
  99, 114, 105, 112, 116,  58,  58, 115, 116, 111, 112,  83,  97, 109, 112, 108,
 105, 110, 103,  13, 112,  97, 117, 115, 101,  83,  97, 109, 112, 108, 105, 110,
 103,  28,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,
  58, 112,  97, 117, 115, 101,  83,  97, 109, 112, 108, 105, 110, 103,  20, 115,
  97, 109, 112, 108, 101,  73, 110, 116, 101, 114, 110,  97, 108,  65, 108, 108,
 111,  99, 115,  35,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112,
 116,  58,  58, 115,  97, 109, 112, 108, 101,  73, 110, 116, 101, 114, 110,  97,
 108,  65, 108, 108, 111,  99, 115,  18, 115, 101, 116,  83,  97, 109, 112, 108,
 101, 114,  67,  97, 108, 108,  98,  97,  99, 107,  34,  83,  97, 109, 112, 108,
 101, 114,  83,  99, 114, 105, 112, 116,  58,  58,  95, 115, 101, 116,  83,  97,
 109, 112, 108, 101, 114,  67,  97, 108, 108,  98,  97,  99, 107,   7, 103, 101,
 116,  83, 105, 122, 101,  22,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114,
 105, 112, 116,  58,  58, 103, 101, 116,  83, 105, 122, 101,  14, 103, 101, 116,
  77, 101, 109,  98, 101, 114,  78,  97, 109, 101, 115,  29,  83,  97, 109, 112,
 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,  58, 103, 101, 116,  77, 101,
 109,  98, 101, 114,  78,  97, 109, 101, 115,  10, 103, 101, 116,  83,  97, 109,
 112, 108, 101, 115,  26,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105,
 112, 116,  58,  58,  95, 103, 101, 116,  83,  97, 109, 112, 108, 101, 115,  14,
 103, 101, 116,  83,  97, 109, 112, 108, 101,  67, 111, 117, 110, 116,  29,  83,
  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,  58, 103, 101,
 116,  83,  97, 109, 112, 108, 101,  67, 111, 117, 110, 116,  18, 103, 101, 116,
  73, 110, 118, 111,  99,  97, 116, 105, 111, 110,  67, 111, 117, 110, 116,  24,
 103, 101, 116,  83, 101, 116, 116, 101, 114,  73, 110, 118, 111,  99,  97, 116,
 105, 111, 110,  67, 111, 117, 110, 116,  24, 103, 101, 116,  71, 101, 116, 116,
 101, 114,  73, 110, 118, 111,  99,  97, 116, 105, 111, 110,  67, 111, 117, 110,
 116,  34,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,
  58,  95, 103, 101, 116,  73, 110, 118, 111,  99,  97, 116, 105, 111, 110,  67,
 111, 117, 110, 116,  14, 105, 115,  71, 101, 116, 116, 101, 114,  83, 101, 116,
 116, 101, 114,  29,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112,
 116,  58,  58, 105, 115,  71, 101, 116, 116, 101, 114,  83, 101, 116, 116, 101,
 114,  16, 103, 101, 116,  76, 101, 120, 105,  99,  97, 108,  83,  99, 111, 112,
 101, 115,  31,  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,
  58,  58, 103, 101, 116,  76, 101, 120, 105,  99,  97, 108,  83,  99, 111, 112,
 101, 115,  12, 103, 101, 116,  83,  97, 118, 101, 100,  84, 104, 105, 115,  27,
  83,  97, 109, 112, 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,  58, 103,
 101, 116,  83,  97, 118, 101, 100,  84, 104, 105, 115,  15, 103, 101, 116,  77,
  97, 115, 116, 101, 114,  83, 116, 114, 105, 110, 103,  30,  83,  97, 109, 112,
 108, 101, 114,  83,  99, 114, 105, 112, 116,  58,  58, 103, 101, 116,  77,  97,
 115, 116, 101, 114,  83, 116, 114, 105, 110, 103,   3,  55,  49,  48,  17, 102,
 108,  97, 115, 104,  46, 116, 114,  97,  99, 101,  58,  84, 114,  97,  99, 101,
   3,  79,  70,  70,   7,  77,  69,  84,  72,  79,  68,  83,  17,  77,  69,  84,
  72,  79,  68,  83,  95,  87,  73,  84,  72,  95,  65,  82,  71,  83,  17,  77,
  69,  84,  72,  79,  68,  83,  95,  65,  78,  68,  95,  76,  73,  78,  69,  83,
  27,  77,  69,  84,  72,  79,  68,  83,  95,  65,  78,  68,  95,  76,  73,  78,
  69,  83,  95,  87,  73,  84,  72,  95,  65,  82,  71,  83,   4,  70,  73,  76,
  69,   8,  76,  73,  83,  84,  69,  78,  69,  82,   8, 115, 101, 116,  76, 101,
 118, 101, 108,   8, 103, 101, 116,  76, 101, 118, 101, 108,  11, 115, 101, 116,
  76, 105, 115, 116, 101, 110, 101, 114,  11, 103, 101, 116,  76, 105, 115, 116,
 101, 110, 101, 114,  11, 102, 108,  97, 115, 104,  46, 116, 114,  97,  99, 101,
   5,  84, 114,  97,  99, 101,  10,  84, 114,  97,  99, 101,  46,  97, 115,  36,
  52,  14, 102, 108,  97, 115, 104,  46, 116, 114,  97,  99, 101, 238, 138, 148,
  10,  84, 114,  97,  99, 101,  67, 108,  97, 115, 115,  18, 102, 108,  97, 115,
 104,  46, 117, 116, 105, 108, 115,  58,  69, 110, 100, 105,  97, 110,  10,  66,
  73,  71,  95,  69,  78,  68,  73,  65,  78,   9,  98, 105, 103,  69, 110, 100,
 105,  97, 110,  13,  76,  73,  84,  84,  76,  69,  95,  69,  78,  68,  73,  65,
  78,  12, 108, 105, 116, 116, 108, 101,  69, 110, 100, 105,  97, 110,   6,  69,
 110, 100, 105,  97, 110,  11,  69, 110, 100, 105,  97, 110,  46,  97, 115,  36,
  53,  14, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115, 238, 138, 148,
  24, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  87, 111,
 114, 107, 101, 114,  83, 116,  97, 116, 101,   3,  78,  69,  87,   3, 110, 101,
 119,   7,  82,  85,  78,  78,  73,  78,  71,   7, 114, 117, 110, 110, 105, 110,
 103,  10,  84,  69,  82,  77,  73,  78,  65,  84,  69,  68,  10, 116, 101, 114,
 109, 105, 110,  97, 116, 101, 100,   6,  70,  65,  73,  76,  69,  68,   6, 102,
  97, 105, 108, 101, 100,   7,  65,  66,  79,  82,  84,  69,  68,   7,  97,  98,
 111, 114, 116, 101, 100,   9,  69,  88,  67,  69,  80,  84,  73,  79,  78,   9,
 101, 120,  99, 101, 112, 116, 105, 111, 110,  11,  87, 111, 114, 107, 101, 114,
  46,  97, 115,  36,  54,   5,  69, 114, 114, 111, 114,  19, 110, 111, 116,  32,
  97, 110,  32, 101, 110, 117, 109,  32, 118,  97, 108, 117, 101,  58,  32,   4,
  99, 111, 100, 101,  11,  87, 111, 114, 107, 101, 114,  83, 116,  97, 116, 101,
  19, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  87, 111,
 114, 107, 101, 114,   9, 109,  95,  99, 117, 114, 114, 101, 110, 116,   6,  87,
 111, 114, 107, 101, 114,  16, 105, 110, 116, 101, 114, 110,  97, 108,  71, 101,
 116,  83, 116,  97, 116, 101,   7,  99, 117, 114, 114, 101, 110, 116,   2, 112,
 114,   5, 115, 116,  97, 116, 101,   5, 115, 116,  97, 114, 116,  10, 105, 115,
  80,  97, 114, 101, 110, 116,  79, 102,  12, 105, 115,  80, 114, 105, 109, 111,
 114, 100, 105,  97, 108,  17, 115, 101, 116,  83, 104,  97, 114, 101, 100,  80,
 114, 111, 112, 101, 114, 116, 121,  17, 103, 101, 116,  83, 104,  97, 114, 101,
 100,  80, 114, 111, 112, 101, 114, 116, 121,   9, 116, 101, 114, 109, 105, 110,
  97, 116, 101,  10, 109,  95,  98, 121, 116, 101,  67, 111, 100, 101,  24, 102,
 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  87, 111, 114, 107,
 101, 114,  69, 118, 101, 110, 116,  12,  87,  79,  82,  75,  69,  82,  95,  83,
  84,  65,  84,  69,  11, 119, 111, 114, 107, 101, 114,  83, 116,  97, 116, 101,
  15, 109,  95, 112, 114, 101, 118, 105, 111, 117, 115,  83, 116,  97, 116, 101,
  14, 109,  95,  99, 117, 114, 114, 101, 110, 116,  83, 116,  97, 116, 101,   8,
 109,  95, 116,  97, 114, 103, 101, 116,  12,  99, 117, 114, 114, 101, 110, 116,
  83, 116,  97, 116, 101,  13, 112, 114, 101, 118, 105, 111, 117, 115,  83, 116,
  97, 116, 101,   6, 116,  97, 114, 103, 101, 116,  11,  87, 111, 114, 107, 101,
 114,  69, 118, 101, 110, 116,  15, 102, 108,  97, 115, 104,  46, 115, 121, 115,
 116, 101, 109, 238, 138, 170,   3,  54,  56,  50,  28,  58,  58,  97, 118, 109,
 115, 104, 101, 108, 108,  58,  58,  83, 104, 101, 108, 108,  87, 111, 114, 107,
 101, 114,  67, 108,  97, 115, 115,  29,  58,  58,  97, 118, 109, 115, 104, 101,
 108, 108,  58,  58,  83, 104, 101, 108, 108,  87, 111, 114, 107, 101, 114,  79,
  98, 106, 101,  99, 116,  25, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116,
 101, 109,  58,  87, 111, 114, 107, 101, 114,  68, 111, 109,  97, 105, 110,  17,
  87, 111, 114, 107, 101, 114,  68, 111, 109,  97, 105, 110,  46,  97, 115,  36,
  55,  12,  87, 111, 114, 107, 101, 114,  68, 111, 109,  97, 105, 110,  33,  99,
 114, 101,  97, 116, 101,  87, 111, 114, 107, 101, 114,  70, 114, 111, 109,  66,
 121, 116, 101,  65, 114, 114,  97, 121,  73, 110, 116, 101, 114, 110,  97, 108,
  25,  99, 114, 101,  97, 116, 101,  87, 111, 114, 107, 101, 114,  70, 114, 111,
 109,  66, 121, 116, 101,  65, 114, 114,  97, 121,  26,  99, 114, 101,  97, 116,
 101,  87, 111, 114, 107, 101, 114,  70, 114, 111, 109,  80, 114, 105, 109, 111,
 114, 100, 105,  97, 108,  11, 108, 105, 115, 116,  87, 111, 114, 107, 101, 114,
 115,  34,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,  58,  83, 104,
 101, 108, 108,  87, 111, 114, 107, 101, 114,  68, 111, 109,  97, 105, 110,  67,
 108,  97, 115, 115,  35,  58,  58,  97, 118, 109, 115, 104, 101, 108, 108,  58,
  58,  83, 104, 101, 108, 108,  87, 111, 114, 107, 101, 114,  68, 111, 109,  97,
 105, 110,  79,  98, 106, 101,  99, 116, 140,   1,  22,   1,   5,   5,  23,   1,
  22,   6,  23,   6,   8,  18,   5,  21,  22,  22,  24,  21,   5,  25,  24,  25,
   5,  29,  24,  29,  26,  29,  26,  24,  22,  35,   8,  56,   5,  71,  22,  72,
  24,  71,   5,  79,  22,  80,  24,  79,   5,  82,  24,  82,   5,  84,  24,  84,
   5,  86,  24,  86,   5,  88,  24,  88,   5,  90,  24,  90,   5,  92,  24,  92,
   5,  94,  24,  94,   5,  96,  22,  98,  23,  98,  24,  96,  26,  96,   5, 101,
  22, 103,  22, 107,  22, 110,  22, 113,  22, 116,  22, 119,  24, 101,   5, 156,
   1,  24, 156,   1,   5, 158,   1,  24, 158,   1,   5, 160,   1,  24, 160,   1,
   5, 162,   1,  24, 162,   1,   5, 164,   1,  24, 164,   1,   5, 166,   1,  24,
 166,   1,   5, 168,   1,  24, 168,   1,   5, 170,   1,  24, 170,   1,   5, 172,
   1,  24, 172,   1,   5, 184,   1,  24, 184,   1,   5, 186,   1,  24, 186,   1,
   5, 188,   1,  24, 188,   1,   5, 190,   1,  24, 190,   1,   5, 192,   1,  24,
 192,   1,   5, 194,   1,  24, 194,   1,   5, 196,   1,  24, 196,   1,   5, 198,
   1,  24, 198,   1,  23,  80,  22, 216,   1,  22, 224,   1,  22, 249,   1,  22,
 252,   1,  22, 253,   1,  22, 254,   1,  22, 255,   1,  22, 128,   2,  22, 129,
   2,   5, 130,   2,   5, 132,   2,  24, 130,   2,  26, 130,   2,   5, 141,   2,
  22, 142,   2,  23, 142,   2,   5, 149,   2,  24, 149,   2,  26, 149,   2,   5,
 160,   2,  24, 160,   2,   5, 164,   2,  24, 164,   2,   5, 170,   2,  24, 170,
   2,   5, 176,   2,  24, 176,   2,  22, 178,   2,   5, 213,   2,  22, 225,   2,
  24, 213,   2,   5, 227,   2,  23, 225,   2,  22, 228,   2,   5, 230,   2,  24,
 230,   2,   5, 236,   2,  23,  72,  22, 237,   2,   5, 238,   2,   5, 251,   2,
  24, 238,   2,  26, 238,   2,   5, 128,   3,  24, 128,   3,  26, 128,   3,   5,
 142,   3,  24, 142,   3,  26, 142,   3,  22, 152,   3,   5, 156,   3,   5, 157,
   3,  24, 156,   3,  26, 156,   3,  62,   4,   1,   2,   3,   4,   4,   1,   2,
   4,   5,   1,   6,   1,   8,   8,   1,   2,   4,   5,  12,  13,  14,  15,   1,
  12,   1,  17,   1,  34,   1,  36,   9,   1,   2,   4,  15,  38,  39,  40,  41,
  42,   1,  44,   1,  45,   1,  46,   1,  47,   1,  48,   1,  49,   2,  44,  45,
   3,  45,  47,  49,   3,  44,  45,  48,   1,  81,   1,  83,   1,   5,   1,   4,
   1,  22,   4,   1,   2,  22,  85,   1,  39,   5,   1,   2,   4,  39,  40,   1,
  86,   1,  87,   1,  88,   1,  89,   1,  90,   1,  91,   1,  92,   1,  93,   1,
  94,   2,  89,  90,   3,  90,  92,  94,   3,  89,  90,  93,   8,   1,   4,   5,
  15,  95,  96,  97,  98,   1,  95,   4,   1,   4,   5,  96,   4,   1,  99, 100,
 101,   1, 101,   8,   1,  15,  99, 100, 101, 102, 103, 104,   1, 113,   4,   1,
 115, 117, 118,   1, 119,   4,   1,  19, 122, 123,   1, 124,   8,   1,  15,  39,
  40, 125, 126, 127, 128,   1,   8,   1,  15,  39,  40, 126, 129,   1, 130,   1,
 131,   1,   1, 129,   1,   8,   1,  15,  39,  40, 126, 132,   1, 133,   1, 134,
   1,   1, 132,   1,   1,  40,   4,   1,  39,  40, 126,   1, 135,   1,   8,   1,
  15,  39,  40, 136,   1, 137,   1, 138,   1, 139,   1,   1, 136,   1,   4,   1,
  39,  40, 137,   1, 142,   4,   7,   1,   2,   7,   1,   3,   9,   4,   1,   9,
   7,   1,   9,   8,   1,   7,   1,   9,   9,  10,   1,   7,   1,  11,   9,  12,
   1,   9,  13,   1,   9,  14,   1,   9,  15,   1,   7,   1,  16,   9,   4,   2,
   9,  17,   2,   9,  19,   3,   7,   5,  20,   9,  19,   4,   7,   5,  23,   7,
   1,  24,   7,   1,  26,   9,  27,   4,   7,   5,  28,   7,   1,  30,   9,  31,
   5,   7,   1,  32,   7,   1,  33,   7,   1,  34,   7,  16,  36,  29,  29,   1,
  20,  29,  29,   1,  26,  29,  29,   1,   8,  29,  29,   1,  21,   7,   1,  37,
   9,  38,   4,   9,  40,   4,   9,  44,   4,   9,  45,   4,   9,  46,   4,   9,
  47,   4,   9,  12,   4,   9,  48,   4,   9,  17,   4,   9,  49,   4,   9,  50,
   4,   9,  10,   4,   9,  31,   6,   9,  30,   4,   9,   8,   4,   9,  51,   4,
   9,  52,   4,   9,  53,   4,   9,  54,   4,   9,  55,   4,   9,  57,   7,   9,
  58,   4,   9,  59,   4,   9,  60,   4,   9,  61,   4,   9,   7,   4,   9,  62,
   4,   9,  63,   4,   9,  64,   4,   9,  65,   4,   9,  66,   4,   9,  67,   4,
   9,  68,   4,   9,  69,   4,   9,  70,   4,   7,   4,   4,   7,  19,  73,   9,
  74,   4,   9,  75,   4,   9,  76,   4,   9,  77,   4,   7,   4,  78,   7,  22,
  81,   7,  22,  83,   7,  22,  85,   7,  22,  87,   7,  22,  89,   7,  22,  91,
   7,  34,  39,   9,  39,   8,   7,  22,  93,   7,  36,  41,   9,  41,   9,   7,
  22,  95,   9,   4,  10,   9,  49,  10,   9,  99,   4,   7,  39, 100,   9, 102,
   4,   9, 104,  11,   9, 108,  12,   9, 111,  13,   9, 114,  14,   9, 117,  15,
   9, 120,  16,   9, 122,  17,   9, 123,  18,   9, 124,  19,   9, 125,   4,   9,
 126,  11,   9, 127,  12,   9, 128,   1,  13,   9, 129,   1,  14,   9, 130,   1,
  15,   9, 131,   1,  16,   9, 132,   1,  17,   9, 133,   1,  18,   9, 134,   1,
  19,   9, 135,   1,   4,   9, 136,   1,  11,   9, 137,   1,  12,   9, 138,   1,
  13,   9, 139,   1,  14,   9, 140,   1,  15,   9, 141,   1,  16,   9, 142,   1,
  17,   9, 143,   1,  18,   9, 144,   1,  19,   9, 145,   1,   4,   9, 146,   1,
  11,   9, 147,   1,  12,   9, 148,   1,  13,   9, 149,   1,  14,   9, 150,   1,
  15,   9, 151,   1,  16,   9, 152,   1,  17,   9, 153,   1,  18,   9, 154,   1,
  19,   7,  22, 155,   1,   7,  22, 157,   1,   7,  22, 159,   1,   7,  22, 161,
   1,   7,  22, 163,   1,   7,  22, 165,   1,   7,  22, 167,   1,   7,  22, 169,
   1,   7,  22, 171,   1,   7,  22, 173,   1,   7,  22, 174,   1,   7,  22, 175,
   1,   7,  22, 176,   1,   7,  22, 177,   1,   7,  22, 178,   1,   7,  22, 179,
   1,   7,  22, 180,   1,   7,  22, 181,   1,   7,  22, 182,   1,   7,  22, 183,
   1,   7,  22, 185,   1,   7,  22, 187,   1,   7,  22, 189,   1,   7,  22, 191,
   1,   7,  22, 193,   1,   7,  22, 195,   1,   9,  39,  20,   7,  22, 197,   1,
   9,  39,  21,   9, 199,   1,  21,   9, 200,   1,  21,   7,  22, 201,   1,   9,
  20,  22,   9,  23,  22,   9,  24,   2,   9,  28,  22,   9,   4,  23,   9,  78,
  23,   9,  81,  24,   9,  24,  25,   9, 185,   1,  24,   9,  81,  25,   9, 187,
   1,  24,   9,  83,  24,   9, 189,   1,  24,   9,  83,  25,   9, 191,   1,  24,
   9,  85,  24,   9, 193,   1,  24,   9,  85,  25,   9, 195,   1,  24,   9,  87,
  24,   9,  89,  24,   9, 197,   1,  24,   9,  89,  25,   9, 201,   1,  24,   9,
  91,  24,   9,  93,  24,   9,  95,  24,   9, 100,  26,   9,  24,  27,   9, 155,
   1,  24,   9, 157,   1,  24,   9, 159,   1,  24,   9, 161,   1,  24,   9, 163,
   1,  24,   9, 165,   1,  24,   9, 167,   1,  24,   9, 169,   1,  24,   9, 171,
   1,  24,   9, 173,   1,  24,   9, 174,   1,  24,   9, 175,   1,  24,   9, 176,
   1,  24,   9, 177,   1,  24,   9, 178,   1,  24,   9, 179,   1,  24,   9, 180,
   1,  24,   9, 181,   1,  24,   9, 182,   1,  24,   9, 183,   1,  24,   9, 202,
   1,  24,   7,  22, 202,   1,   9, 203,   1,  24,   7,  22, 203,   1,   9, 204,
   1,  24,   7,  22, 204,   1,   9, 205,   1,  24,   7,  22, 205,   1,   9, 206,
   1,  24,   7,  22, 206,   1,   9, 207,   1,  24,   7,  22, 207,   1,   9, 102,
  24,   7,  22, 102,   9, 104,  24,   7,  22, 104,   9, 108,  24,   7,  22, 108,
   9, 111,  24,   7,  22, 111,   9, 114,  24,   7,  22, 114,   9, 117,  24,   7,
  22, 117,   9, 120,  24,   7,  22, 120,   9, 122,  24,   7,  22, 122,   9, 123,
  24,   7,  22, 123,   9, 124,  24,   7,  22, 124,   9, 125,  24,   7,  22, 125,
   9, 126,  24,   7,  22, 126,   9, 127,  24,   7,  22, 127,   9, 128,   1,  24,
   7,  22, 128,   1,   9, 129,   1,  24,   7,  22, 129,   1,   9, 130,   1,  24,
   7,  22, 130,   1,   9, 131,   1,  24,   7,  22, 131,   1,   9, 132,   1,  24,
   7,  22, 132,   1,   9, 133,   1,  24,   7,  22, 133,   1,   9, 134,   1,  24,
   7,  22, 134,   1,   9, 208,   1,  22,   9,   4,  28,   9,  78,  28,   9,  17,
  28,   9,  81,  29,   9, 185,   1,  29,   9, 187,   1,  29,   9,  83,  29,   9,
 189,   1,  29,   9, 191,   1,  29,   9,  85,  29,   9, 193,   1,  29,   9, 195,
   1,  29,   9,  87,  29,   9,  89,  29,   9, 197,   1,  29,   9, 201,   1,  29,
   9,  91,  29,   9,  93,  29,   9,  95,  29,   9, 100,  30,   9, 250,   1,   4,
   9, 251,   1,   4,   9, 202,   1,  29,   9, 203,   1,  29,   9, 204,   1,  29,
   9, 205,   1,  29,   9, 206,   1,  29,   9, 207,   1,  29,   9, 102,  29,   9,
 104,  31,   9, 108,  32,   9, 111,  33,   9, 114,  34,   9, 117,  35,   9, 120,
  36,   9, 122,  37,   9, 123,  38,   9, 124,  39,   9, 125,  29,   9, 126,  31,
   9, 127,  32,   9, 128,   1,  33,   9, 129,   1,  34,   9, 130,   1,  35,   9,
 131,   1,  36,   9, 132,   1,  37,   9, 133,   1,  38,   9, 134,   1,  39,   9,
 135,   1,  29,   9, 136,   1,  31,   9, 137,   1,  32,   9, 138,   1,  33,   9,
 139,   1,  34,   9, 140,   1,  35,   9, 141,   1,  36,   9, 142,   1,  37,   9,
 143,   1,  38,   9, 144,   1,  39,   9, 145,   1,  29,   9, 146,   1,  31,   9,
 147,   1,  32,   9, 148,   1,  33,   9, 149,   1,  34,   9, 150,   1,  35,   9,
 151,   1,  36,   9, 152,   1,  37,   9, 153,   1,  38,   9, 154,   1,  39,   9,
 155,   1,  29,   9, 157,   1,  31,   9, 159,   1,  32,   9, 161,   1,  33,   9,
 163,   1,  34,   9, 165,   1,  35,   9, 167,   1,  36,   9, 169,   1,  37,   9,
 171,   1,  38,   9, 173,   1,  39,   9, 174,   1,  29,   9, 175,   1,  31,   9,
 176,   1,  32,   9, 177,   1,  33,   9, 178,   1,  34,   9, 179,   1,  35,   9,
 180,   1,  36,   9, 181,   1,  37,   9, 182,   1,  38,   9, 183,   1,  39,   7,
   4,  13,   9, 131,   2,  40,   9,  78,  40,   9,  76,  40,   9, 133,   2,  40,
   9,  14,   4,   9, 134,   2,   4,   9, 131,   2,  41,   9, 133,   2,   4,   9,
  15,   4,   9, 135,   2,   4,   9, 136,   2,   4,   9,  13,  23,   9,  24,  42,
   9,  13,  28,   7,   1, 139,   2,   9, 140,   2,  43,   9, 143,   2,  43,   9,
 144,   2,  43,   7,   1, 145,   2,   9, 146,   2,  44,   9, 147,   2,  43,   9,
 144,   2,  44,   9, 148,   2,  44,   9, 150,   2,  45,   9, 152,   2,  45,   9,
 155,   2,  45,   9, 150,   2,   4,   9, 152,   2,   4,   9, 155,   2,   4,   9,
 157,   2,   4,   9, 158,   2,   4,   7, 100, 159,   2,   9, 161,   2,   4,   9,
 162,   2,   4,   7, 100, 163,   2,   7,   1, 165,   2,   7,   1, 166,   2,   7,
   1, 167,   2,   7,   1, 168,   2,   9, 165,   2,   4,   9, 166,   2,   4,   9,
 167,   2,   4,   9, 168,   2,   4,   7, 101, 169,   2,   9, 171,   2,   4,   9,
 172,   2,   4,   9, 173,   2,   4,   9, 174,   2,   4,   7, 100, 175,   2,   7,
 100, 177,   2,   9,  24,  43,   9, 159,   2,  46,   9, 163,   2,  46,   9, 175,
   2,  46,   9, 177,   2,  46,   9, 180,   2,  46,   9, 182,   2,  46,   9, 184,
   2,  46,   9, 186,   2,  46,   9, 188,   2,  46,   9, 190,   2,  46,   9, 147,
   2,  44,   9, 192,   2,  46,   9, 194,   2,  46,   9, 196,   2,  46,   9, 143,
   2,  44,   9, 198,   2,  46,   9, 200,   2,  46,   9, 201,   2,  46,   9, 202,
   2,  46,   9, 140,   2,  44,   9, 204,   2,  46,   9, 206,   2,  46,   9, 208,
   2,  46,   9, 210,   2,  46,   9, 169,   2,  44,   7,   1, 214,   2,   7,   1,
 215,   2,   7,   1, 216,   2,   7,   1, 217,   2,   7,   1, 218,   2,   7,   1,
 219,   2,   7,   1, 220,   2,   9, 214,   2,   4,   9, 215,   2,   4,   9, 216,
   2,   4,   9, 217,   2,   4,   9, 218,   2,   4,   9, 219,   2,   4,   9, 220,
   2,   4,   9, 221,   2,   4,   9, 222,   2,   4,   9, 223,   2,   4,   9, 224,
   2,   4,   7, 115, 226,   2,   9,  24,  47,   9, 226,   2,  48,   7,   1, 231,
   2,   7,   1, 233,   2,   9, 231,   2,   4,   9, 233,   2,   4,   7,  19, 235,
   2,   9,  24,  49,   9, 235,   2,  50,   7,   1, 239,   2,   7,   1, 241,   2,
   7,   1, 243,   2,   7,   1, 245,   2,   7,   1, 247,   2,   7,   1, 249,   2,
   9, 239,   2,  51,   9, 241,   2,  51,   9, 243,   2,  51,   9, 245,   2,  51,
   9, 247,   2,  51,   9, 249,   2,  51,   9, 252,   2,  51,   9, 239,   2,   4,
   9, 241,   2,   4,   9, 243,   2,   4,   9, 245,   2,   4,   9, 247,   2,   4,
   9, 249,   2,   4,   9, 254,   2,   4,   7,  39, 255,   2,   9, 129,   3,  52,
   7,  39, 130,   3,   9, 131,   3,  52,   9, 132,   3,   4,   9, 133,   3,   4,
   9, 129,   3,  53,   9, 134,   3,   4,   9, 131,   3,  53,   9, 135,   3,   4,
   9, 136,   3,   4,   9, 137,   3,   4,   9, 138,   3,   4,   9, 139,   3,   4,
   9, 140,   3,   4,   9, 141,   3,  53,   7,   1, 143,   3,   9, 145,   3,  54,
   9, 146,   3,  54,   9, 147,   3,  54,   9, 143,   3,   4,   9, 148,   3,   4,
   9, 149,   3,   4,   9, 150,   3,   4,   9, 145,   3,  55,   9, 146,   3,  55,
   9, 147,   3,  56,   7,  39, 151,   3,   9, 255,   2,  26,   9,  24,  57,   9,
 130,   3,  26,   9, 151,   3,  26,   9, 255,   2,  58,   9, 130,   3,  30,   9,
 151,   3,  30,   9, 129,   3,  59,   7,  39, 158,   3,   9, 159,   3,  59,  29,
  29,   1, 226,   3,   9, 129,   3,  60,   9, 160,   3,   4,   9, 161,   3,   4,
   9, 159,   3,  60,   9, 162,   3,   4,   9,  24,  61,   9, 158,   3,  30, 153,
   2,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,
   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,
   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,
   0,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,
   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,
   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,
   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,
   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,
   2,   1,   0,   1,   1,   0,   1,   0,   0,   6,   1,   0,   0,   8,   1,   0,
   0,   0,   1,   4,   0,   0,   1,   4,   1,  13,   6,   1,   0,   0,   0,   1,
   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,
   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   1,  21,  21,
   1,  32,   0,   0,   1,   0,   0,   0,   1,   0,   1,   1,  26,   1,  32,   1,
  26,   6,   1,  32,   1,   1,  26,   1,  32,   0,   6,   1,  32,   0,   6,   1,
  32,   0,   6,   1,  32,   1,   1,  27,   1,  32,   1,   1,   6,   1,  32,   0,
   1,   1,  32,   0,   2,   1,  32,   0,  21,   1,  32,   0,   8,   1,  32,   0,
  27,   1,  32,   0,   6,   1,  32,   0,  21,   1,  32,   0,  21,   1,  32,   0,
  21,   1,  32,   0,   1,   1,  32,   0,   1,   1,  32,   0,   1,   1,  32,   1,
   2,  20,   1,  32,   0,  26,   1,  32,   0,  26,   1,  32,   1,   1,  28,   1,
  32,   1,   1,  26,   1,  32,   2,   1,  30,   8,   1,  32,   2,   1,  31,   8,
   1,  32,   2,   1,  32,   8,   1,  32,   2,   1,  33,   8,   1,  32,   1,   1,
  21,   1,  40,   1,   1,   6,   0,   2,   1,  32,   1,   2,   0,   1,  32,   1,
   1,  34,   1,  32,   1,   0,   0,   1,  32,   0,   0,   1,   0,   0,   0,   1,
   0,   1,   2,   6,   1,  32,   1,   6,   6,   1,  32,   2,   1,   6,   6,   1,
  32,   1,  71,   6,   1,  32,   2,   2,   6,  71,   1,  32,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   6,   1,   0,   0,   2,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,
   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,
   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,
   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,
   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,   0,   2,   1,   0,
   0,   2,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,
   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,
   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,   0,   1,   1,   0,   1,
   0,   1,   1,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0, 227,   2,   1,  32,   0,
   8,   1,  32,   1,   1, 227,   2,   1,  32,   1,   0, 227,   2,   1,   0,   2,
   0,  71,   8,   1,  40,   1,   3,   3,   1,  13,   6,   1,  32,   2,   0,   6,
   8,   1,   8,   1,   3,   3,   0,  71,   1,  32,   1,   0,  71,   1,  32,   0,
   0,   1,   0,   1,   6,   6,   1,  32,   1,  20,  34,   1,  32,   1,  27,  34,
   1,  32,   2,   2,  20, 242,   2,   1,  32,   3,  21,  20, 242,   2,   8,   1,
  32,   2,  21,  20, 242,   2,   1,   0,   2,  21,  20, 242,   2,   1,   0,   2,
  21,  20, 242,   2,   1,   0,   0,  21,   1,  32,   1,  20,  13,   1,  32,   0,
  20,   1,   0,   2,  20,  20,   2,   1,  40,   1,  10,  10,   1,  21,   0,   1,
  32,   1,   1,  34,   1,  32,   0,   0,   1,   2,   1,   1,  34,   1,   2,   1,
   1,   2,   1,  32,   0,   1,   1,  32,   0,   1,   1,  32,   0,   1,   1,  32,
   0,   1,   1,  32,   0,   0,   1,   0,   0,   6,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,  32,   0,  21,   1,  32,   0,   0,   1,   0,
   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   2,   0,  26,  26,   1,  40,   1,   4,   3,   1,  26,  26,   1,  40,   1,   4,
   3,   1,   0,  34,   1,  32,   0,  34,   1,  32,   0,   0,   1,   0,   0,   0,
   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,
   1,   0,   1,  26,   6,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,
 226,   3,   1,   0,   1,   1,   6,   1,  32,   0,   0,   1,   0,   0,   6,   1,
   0,   0,   6,   1,  32,   0,   1,   1,  32,   1,   2, 226,   3,   1,  32,   0,
   2,   1,  32,   2,   1,   6,   0,   1,  32,   1,   0,   6,   1,  32,   0,   2,
   1,  32,   0,   0,   1,   0,   2,   0,   6,   6,   1,   0,   0,   6,   1,   0,
   0,   6,   1,   0,   0,  20,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,
   0, 132,   4,   1,   0,   0,   0,   1,   0,   1, 226,   3,  71,   1,   0,   0,
 226,   3,   1,   0,   1, 226,   3,  71,   1,  32,   0, 134,   4,   1,  32,   0,
   0,   1,   0,  47,  39,   0,  41,   1,  42,  43, 105,   1,   0, 106, 105,   1,
   0, 109, 105,   1,   0, 112, 105,   1,   0, 115, 105,   1,   0, 118, 105,   1,
   0, 121, 105,   2,   0,   0, 106, 109, 105,   3,   0,   0,   0, 115, 109, 121,
 105,   3,   0,   0,   0, 118, 106, 109, 209,   1,   3, 210,   1, 212,   1, 214,
   1, 211,   1, 213,   1, 215,   1, 209,   1,   4, 210,   1, 218,   1, 214,   1,
 221,   1, 217,   1, 219,   1, 220,   1, 222,   1, 209,   1,   3, 210,   1, 214,
   1, 221,   1, 223,   1, 220,   1, 222,   1, 209,   1,   5, 210,   1, 212,   1,
 227,   1, 214,   1, 221,   1, 225,   1, 226,   1, 219,   1, 220,   1, 228,   1,
 209,   1,   4, 210,   1, 212,   1, 227,   1, 214,   1, 229,   1, 230,   1, 219,
   1, 220,   1, 209,   1,   5, 210,   1, 212,   1, 227,   1, 214,   1, 221,   1,
 231,   1, 232,   1, 219,   1, 220,   1, 233,   1, 209,   1,   4, 210,   1, 212,
   1, 227,   1, 214,   1, 234,   1, 235,   1, 219,   1, 220,   1, 209,   1,   5,
 210,   1, 212,   1, 227,   1, 214,   1, 221,   1, 236,   1, 237,   1, 219,   1,
 220,   1, 238,   1, 209,   1,   4, 210,   1, 212,   1, 227,   1, 214,   1, 239,
   1, 240,   1, 219,   1, 220,   1, 209,   1,   5, 210,   1, 212,   1, 227,   1,
 214,   1, 221,   1, 241,   1, 242,   1, 219,   1, 220,   1, 243,   1, 209,   1,
   5, 210,   1, 212,   1, 227,   1, 214,   1, 221,   1, 244,   1, 245,   1, 219,
   1, 220,   1, 209,   1, 209,   1,   1, 221,   1, 209,   1, 209,   1,   1, 246,
   1, 247,   1, 209,   1,   1, 246,   1, 248,   1, 209,   1,   4, 210,   1, 227,
   1, 212,   1, 214,   1, 137,   2, 219,   1, 138,   2, 220,   1, 209,   1,   3,
 210,   1, 212,   1, 214,   1, 168,   2, 179,   2, 220,   1, 209,   1,   1,   0,
 181,   2, 209,   1,   1,   0, 183,   2, 209,   1,   1,   0, 185,   2, 209,   1,
   1,   0, 187,   2, 209,   1,   1,   0, 189,   2, 209,   1,   1,   0, 191,   2,
 209,   1,   1,   0, 193,   2, 209,   1,   1,   0, 195,   2, 209,   1,   1,   0,
 197,   2, 209,   1,   1,   0, 199,   2, 209,   1,   1,   0, 203,   2, 209,   1,
   1,   0, 205,   2, 209,   1,   1,   0, 207,   2, 209,   1,   1,   0, 209,   2,
 209,   1,   1,   0, 211,   2, 105,   1,   0, 212,   2, 209,   1,   3, 210,   1,
 214,   1, 221,   1, 229,   2, 220,   1, 222,   1, 105,   1,   0, 153,   3, 209,
   1,   4, 210,   1, 212,   1, 214,   1, 221,   1, 154,   3, 155,   3, 220,   1,
 209,   1, 209,   1,   3, 210,   1, 212,   1, 214,   1, 163,   3, 164,   3, 220,
   1,  54,  17,   0,   5,   0,  39,   1,  16,   1,   0,  38,  19,  20,   9,   9,
   0,  42,   1,  18,   1,   0,  41,  23,  20,   9,  11,   0,  45,   1,  22,   1,
   0,  44,  70,  20,   9,  13,   0,  81,   0,  76,  20,   9,  20,   0,  88,   0,
  77,  20,   9,  23,   0,  90,   0,  78,  20,   9,  25,   0,  92,   0,  79,  20,
   9,  27,   0,  94,   0,  80,  20,   9,  29,   0,  96,   0,  81,  20,   9,  31,
   0,  98,   0,  82,  20,   9,  33,   0, 100,   0,  85,  20,   9,  35,   0, 102,
   0,  88,  20,   9,  37,   0, 104,   0,  92,  20,  11,  41,   0, 108,   0, 133,
   1,  20,   9,  50,   0, 140,   1,  50,  93,   0,   0,   2,  11,  11,  94,  64,
   0,   2,  11,  11,   1,   2,  95,  64,   0,   2,  11,  11,   1,   3,  96,  64,
   0,   2,  11,  11,   1,   4,  97,  64,   0,   2,  11,  11,   1,   5,  98,  64,
   0,   2,  11,  11,   1,   6,  99,  64,   0,   2,  11,  11,   1,   7, 100,  64,
   0,   2,  11,  11,   1,   8, 101,  64,   0,   2,  11,  11,   1,   9, 102,  64,
   0,   2,  11,  11,   1,  10, 103,   6,   0,   2,  11,  11, 104,  70,   0,   2,
  11,  11,   1,   2, 105,  70,   0,   2,  11,  11,   1,   3, 106,  70,   0,   2,
  11,  11,   1,   4, 107,  70,   0,   2,  11,  11,   1,   5, 108,  70,   0,   2,
  11,  11,   1,   6, 109,  70,   0,   2,  11,  11,   1,   7, 110,  70,   0,   2,
  11,  11,   1,   8, 111,  70,   0,   2,  11,  11,   1,   9, 112,  70,   0,   2,
  11,  11,   1,  10, 113,   1,   0, 110, 114,  65,   0, 111,   1,   2, 115,  65,
   0, 112,   1,   3, 116,  65,   0, 113,   1,   4, 117,  65,   0, 114,   1,   5,
 118,  65,   0, 115,   1,   6, 119,  65,   0, 116,   1,   7, 120,  65,   0, 117,
   1,   8, 121,  65,   0, 118,   1,   9, 122,  65,   0, 119,   1,  10, 123,   2,
   0, 120, 124,  66,   0, 121,   1,   2, 125,  66,   0, 122,   1,   3, 126,  66,
   0, 123,   1,   4, 127,  66,   0, 124,   1,   5, 128,   1,  66,   0, 125,   1,
   6, 129,   1,  66,   0, 126,   1,   7, 130,   1,  66,   0, 127,   1,   8, 131,
   1,  66,   0, 128,   1,   1,   9, 132,   1,  66,   0, 129,   1,   1,  10, 123,
   3,   0, 130,   1, 124,  67,   0, 131,   1,   1,   2, 125,  67,   0, 132,   1,
   1,   3, 126,  67,   0, 133,   1,   1,   4, 127,  67,   0, 134,   1,   1,   5,
 128,   1,  67,   0, 135,   1,   1,   6, 129,   1,  67,   0, 136,   1,   1,   7,
 130,   1,  67,   0, 137,   1,   1,   8, 131,   1,  67,   0, 138,   1,   1,   9,
 132,   1,  67,   0, 139,   1,   1,  10, 134,   1,  20,   9,  52,   0, 142,   1,
   0, 135,   1,  20,   9,  54,   0, 144,   1,   0, 136,   1,  20,   9,  56,   0,
 146,   1,   0, 137,   1,  20,   9,  58,   0, 148,   1,   0, 138,   1,  20,   9,
  60,   0, 150,   1,   0, 139,   1,  20,   9,  62,   0, 152,   1,   0, 140,   1,
  20,   9,  64,   0, 154,   1,   0, 141,   1,  20,   9,  66,   0, 156,   1,   0,
 142,   1,  20,   9,  68,   0, 158,   1,   0, 143,   1,   0,   5,   0, 160,   1,
   0, 144,   1,   0,   5,   0, 162,   1,   0, 145,   1,   0,   5,   0, 164,   1,
   0, 146,   1,   0,   5,   0, 166,   1,   0, 147,   1,   0,   5,   0, 168,   1,
   0, 148,   1,   0,   5,   0, 170,   1,   0, 149,   1,   0,   5,   0, 172,   1,
   0, 150,   1,   0,   5,   0, 174,   1,   0, 151,   1,   0,   5,   0, 176,   1,
   0, 152,   1,   0,   5,   0, 178,   1,   0, 153,   1,  77,   9,  70,   0, 180,
   1,   0, 154,   1,  77,   9,  72,   0, 182,   1,   0, 155,   1,  78,   9,  74,
   0, 184,   1,   0, 156,   1,  78,   9,  76,   0, 186,   1,   0, 157,   1,  79,
   9,  78,   0, 188,   1,   0, 158,   1,  79,   9,  80,   0, 190,   1,   0, 160,
   1,  81,   9,  82,   0, 192,   1,   1, 159,   1,   0,   0,  26,   0, 164,   1,
  81,   9,  84,   0, 194,   1,   3, 161,   1,   0,   0,  26,   0, 162,   1,   0,
   0,  26,   0, 163,   1,   0,   0,  26,   0, 227,   2,  20,   9,  97,   0, 200,
   1,   6, 234,   2,   1,   0, 199,   1, 235,   2,   1,   0, 201,   1, 236,   2,
   1,   0, 202,   1, 237,   2,   1,   0, 203,   1, 238,   2,   2,   0, 204,   1,
 238,   2,   3,   0, 205,   1, 131,   3,  20,  11, 103,   0, 230,   1,   5, 254,
   2,   6,   0,   6,   0, 255,   2,   6,   0,   6,   0, 128,   3,   6,   0,   8,
   0, 129,   3,   6,   0,  21,   0, 130,   3,   1,   0, 229,   1, 134,   3,  20,
   9, 106,   0, 232,   1,   2, 132,   3,   6,   0,  21,   0, 133,   3,   6,   0,
  27,   0, 143,   3,  20,  11, 108,   0, 234,   1,   0, 148,   3, 134,   3,  11,
 110,   0, 238,   1,   4, 144,   3,   6,   0,  21,   0, 145,   3,   6,   0,  13,
   0, 146,   3,   2,   0, 236,   1, 147,   3,   2,   0, 237,   1, 149,   3, 134,
   3,  11, 112,   0, 240,   1,   2, 144,   3,   6,   0,  21,   0, 147,   3,   6,
   0,  21,   0, 194,   3,  20,   9, 116,   0, 247,   1,   0, 201,   3,  20,   9,
 121,   0, 250,   1,   0, 224,   3,  20,  11, 127,   0, 254,   1,   0, 226,   3,
  20,  11, 130,   1,   0, 130,   2,   9, 231,   3,   2,   0, 131,   2, 232,   3,
   1,   0, 132,   2, 233,   3,   1,   0, 133,   2, 234,   3,   1,   0, 134,   2,
 235,   3,   2,   0, 135,   2, 236,   3,   1,   0, 136,   2, 237,   3,   1,   0,
 137,   2, 238,   3,   1,   0, 138,   2, 239,   3,   0,   0,  71,   0, 251,   3,
  20,  11, 133,   1,   0, 140,   2,   6, 245,   3,   2,   0, 141,   2, 246,   3,
   2,   0, 142,   2, 247,   3,   2,   0, 143,   2, 248,   3,   0,   0,   6,   0,
 249,   3,   0,   0,   6,   0, 250,   3,   0,   0,  20,   0, 132,   4,  20,  11,
 138,   1,   0, 147,   2,   4, 136,   4,   1,   0, 148,   2, 137,   4,   1,   0,
 149,   2, 138,   4,   1,   0, 150,   2, 139,   4,   1,   0, 151,   2,  37,   0,
  40,   0,  43,   0,  46,  35,  35,  81,   3,  47,   1,   0,  36,  81,   4,  48,
   1,   1,  37,  17,   5,  49,  38,  17,   6,  50,  39,  17,   7,  51,  40,  17,
   8,  52,  41,  17,   9,  53,  42,  17,  10,  54,  43,  17,  11,  55,  44,  17,
  12,  56,  45,  17,  13,  57,  46,  17,  14,  58,  47,  17,  15,  59,  48,   6,
   1,  27,   0,  49,  17,  16,  60,  50,  18,  17,  61,  51,  18,  18,  62,  52,
  18,  19,  63,  53,  17,  20,  64,  54,  17,  21,  65,  55,  17,  22,  66,  56,
  17,  23,  67,  57,  18,  24,  68,  58,  18,  25,  69,  59,  17,  26,  70,  60,
  17,  27,  71,  61,  17,  28,  72,  62,  17,  29,  73,  63,  17,  30,  74,  64,
  17,  31,  75,  65,  17,  32,  76,  66,  17,  33,  77,  67,  17,  34,  78,  68,
  17,  35,  79,  69,  17,  36,  80,  82,   5,  72,  17,   3,  83,  73,  17,   4,
  84,  42,  17,   5,  85,  74,  17,   6,  86,  75,  17,   7,  87,  89,   0,  91,
   0,  93,   0,  95,   0,  97,   0,  99,   0, 101,   1,  84,   0,   1,  26,   1,
   3, 103,   1,  87,   0,   1,  26,   2,   3, 105,   2,  91,  18,   3, 106,  44,
  18,   4, 107, 109,   0, 141,   1,   0, 143,   1,   0, 145,   1,   0, 147,   1,
   0, 149,   1,   0, 151,   1,   0, 153,   1,   0, 155,   1,   0, 157,   1,   0,
 159,   1,   0, 161,   1,   0, 163,   1,   0, 165,   1,   0, 167,   1,   0, 169,
   1,   0, 171,   1,   0, 173,   1,   0, 175,   1,   0, 177,   1,   0, 179,   1,
   0, 181,   1,   0, 183,   1,   0, 185,   1,   0, 187,   1,   0, 189,   1,   0,
 191,   1,   0, 193,   1,   0, 196,   1,   2, 232,   2,  18,   3, 197,   1, 233,
   2,  18,   4, 198,   1, 228,   1,   0, 231,   1,   0, 233,   1,   4, 139,   3,
   6,   1,  13,   0, 140,   3,   6,   2,  13,   0, 141,   3,   6,   3,  13,   0,
 142,   3,   6,   4,  13,   0, 235,   1,   0, 239,   1,   0, 242,   1,  11, 183,
   3,   6,   1,  26,   3,   3, 184,   3,   6,   2,  26,   5,   3, 185,   3,   6,
   3,  26,   4,   3, 186,   3,   6,   4,  26,   6,   3, 187,   3,   6,   5,  26,
   7,   3, 188,   3,   6,   6,   0,   5,   3, 189,   3,   6,   7,   0,   4,   3,
 190,   3,  17,   3, 243,   1, 191,   3,  17,   4, 244,   1, 192,   3,  17,   5,
 245,   1, 193,   3,  17,   6, 246,   1, 249,   1,   2, 199,   3,   6,   1,   6,
 232,   2,   1, 200,   3,   6,   2,   6, 234,   2,   1, 252,   1,   7, 217,   3,
   6,   1,   6, 240,   2,   1, 218,   3,   6,   2,   6, 242,   2,   1, 219,   3,
   6,   3,   6, 244,   2,   1, 220,   3,   6,   4,   6, 246,   2,   1, 221,   3,
   6,   5,   6, 248,   2,   1, 222,   3,   6,   6,   6, 250,   2,   1, 223,   3,
  17,   3, 253,   1, 255,   1,   3, 228,   3,  18,   3, 128,   2, 229,   3,  17,
   4, 129,   2, 230,   3,   0,   1, 226,   3,   0, 139,   2,   1, 244,   3,   6,
   1,   6, 144,   3,   1, 145,   2,   2, 228,   3,  18,   3, 146,   2, 135,   4,
   0,   1, 132,   4,   0,   7, 206,   1,   1, 241,   2,  68,   0,  42,   1,  25,
 241,   1,  25, 151,   3,   4,   1,  43, 152,   3,   4,   2,  44, 153,   3,  68,
   3,  46,   1,  26, 154,   3,   4,   4,  47, 155,   3,  65,  38, 227,   1,   1,
  27, 156,   3,  65,  39, 226,   1,   1,  28, 157,   3,  65,  40, 225,   1,   1,
  29, 158,   3,  65,  41, 224,   1,   1,  30, 159,   3,  65,  42, 223,   1,   1,
  31, 160,   3,   1,  43, 222,   1, 161,   3,  65,  44, 220,   1,   1,  32, 162,
   3,  65,  45, 219,   1,   1,  33, 163,   3,  65,  46, 218,   1,   1,  34, 164,
   3,   1,  47, 217,   1, 165,   3,  65,  48, 216,   1,   1,  35, 166,   3,  65,
  49, 215,   1,   1,  36, 167,   3,   1,  50, 214,   1, 168,   3,   1,  51, 213,
   1, 169,   3,   1,  52, 212,   1, 170,   3,  65,  53, 211,   1,   1,  37, 171,
   3,  65,  54, 210,   1,   1,  38, 172,   3,  65,  55, 209,   1,   1,  39, 173,
   3,  65,  56, 208,   1,   1,  40, 174,   3,  65,  57, 207,   1,   1,  41, 175,
   3,  68,   5,  45,   1,  42, 248,   1,   1, 196,   3,  68,   1,  48,   1,  43,
 251,   1,   1, 203,   3,   4,   1,  49, 144,   2,   3, 128,   4,  68,   0,  50,
   1,  44, 129,   4,  68,   0,  51,   1,  45, 130,   4,   4,   0,  52, 152,   2,
   1, 141,   4,  68,   1,  53,   1,  46, 195,   1, 106, 138,   2,   6,   0,   0,
  17,   8, 165,   1,   4,   0,   0, 166,   1,   4,   0,   1, 168,   1,  68,   0,
   2,   1,  11, 139,   2,  68,   0,   3,   1,  12, 140,   2,  68,   0,   4,   1,
  13, 141,   2,   1,   1,  36, 142,   2,  68,   0,   5,   1,  14, 143,   2,  68,
   0,  34,   1,  15, 144,   2,   4,   0,  35, 145,   2,  68,   0,   6,   1,  16,
 146,   2,  68,   0,  36,   1,  17, 147,   2,   4,   0,  37, 148,   2,  68,   0,
   7,   1,  18, 149,   2,  68,   0,  38,   1,  19, 150,   2,   4,   0,  39, 151,
   2,  68,   0,   8,   1,  20, 152,   2,  68,   0,   9,   1,  21, 153,   2,   4,
   0,  40, 154,   2,   4,   0,  41, 155,   2,  68,   0,  10,   1,  22, 156,   2,
  68,   0,  11,   1,  23, 157,   2,  68,   0,  12,   1,  24, 158,   2,   4,   0,
  13, 159,   2,   1,   2,  35, 160,   2,   1,   3,  34,  41,   1,   4,  33,  46,
   1,   5,  32,  49,   1,   6,  31,  60,   1,   7,  30, 161,   2,   6,   0,   0,
   2,   6, 162,   2,   6,   0,   0,   3,   6, 163,   2,   6,   0,   0,   4,   6,
 164,   2,   6,   0,   0,   5,   6, 165,   2,   6,   0,   0,   6,   6, 166,   2,
   6,   0,   0,   7,   6, 167,   2,   0,   0,   2,   0, 168,   2,  64,   0,   2,
   0,   1,   2, 169,   2,  64,   0,   2,   0,   1,   3, 170,   2,  64,   0,   2,
   0,   1,   4, 171,   2,  64,   0,   2,   0,   1,   5, 172,   2,  64,   0,   2,
   0,   1,   6, 173,   2,  64,   0,   2,   0,   1,   7, 174,   2,  64,   0,   2,
   0,   1,   8, 175,   2,  64,   0,   2,   0,   1,   9, 176,   2,  64,   0,   2,
   0,   1,  10, 177,   2,   6,   0,   2,  11,  11, 178,   2,  70,   0,   2,  11,
  11,   1,   2, 179,   2,  70,   0,   2,  11,  11,   1,   3, 180,   2,  70,   0,
   2,  11,  11,   1,   4, 181,   2,  70,   0,   2,  11,  11,   1,   5, 182,   2,
  70,   0,   2,  11,  11,   1,   6, 183,   2,  70,   0,   2,  11,  11,   1,   7,
 184,   2,  70,   0,   2,  11,  11,   1,   8, 185,   2,  70,   0,   2,  11,  11,
   1,   9, 186,   2,  70,   0,   2,  11,  11,   1,  10, 187,   2,   1,   8,  29,
 188,   2,  65,   9,  28,   1,   2, 189,   2,  65,  10,  27,   1,   3, 190,   2,
  65,  11,  26,   1,   4, 191,   2,  65,  12,  25,   1,   5, 192,   2,  65,  13,
  24,   1,   6, 193,   2,  65,  14,  23,   1,   7, 194,   2,  65,  15,  22,   1,
   8, 195,   2,  65,  16,  21,   1,   9, 196,   2,  65,  17,  20,   1,  10, 197,
   2,   2,  18,  19, 198,   2,  66,  19,  18,   1,   2, 199,   2,  66,  20,  17,
   1,   3, 200,   2,  66,  21,  16,   1,   4, 201,   2,  66,  22,  15,   1,   5,
 202,   2,  66,  23,  14,   1,   6, 203,   2,  66,  24,  13,   1,   7, 204,   2,
  66,  25,  12,   1,   8, 205,   2,  66,  26,  11,   1,   9, 206,   2,  66,  27,
  10,   1,  10, 197,   2,   3,  28,   9, 198,   2,  67,  29,   8,   1,   2, 199,
   2,  67,  30,   7,   1,   3, 200,   2,  67,  31,   6,   1,   4, 201,   2,  67,
  32,   5,   1,   5, 202,   2,  67,  33,   4,   1,   6, 203,   2,  67,  34,   3,
   1,   7, 204,   2,  67,  35,   2,   1,   8, 205,   2,  67,  36,   1,   1,   9,
 206,   2,  67,  37,   0,   1,  10, 207,   2,   4,   0,  14, 208,   2,  68,   0,
  15,   1,   2, 209,   2,  68,   0,  16,   1,   3, 210,   2,  68,   0,  17,   1,
   4, 211,   2,  68,   0,  18,   1,   5, 212,   2,  68,   0,  19,   1,   6, 213,
   2,  68,   0,  20,   1,   7, 214,   2,  68,   0,  21,   1,   8, 215,   2,  68,
   0,  22,   1,   9, 216,   2,  68,   0,  23,   1,  10, 217,   2,   4,   0,  24,
 218,   2,  68,   0,  25,   1,   2, 219,   2,  68,   0,  26,   1,   3, 220,   2,
  68,   0,  27,   1,   4, 221,   2,  68,   0,  28,   1,   5, 222,   2,  68,   0,
  29,   1,   6, 223,   2,  68,   0,  30,   1,   7, 224,   2,  68,   0,  31,   1,
   8, 225,   2,  68,   0,  32,   1,   9, 226,   2,  68,   0,  33,   1,  10, 191,
   1,   0,   1,   2,   1,   2,   3, 208,  48,  71,   0,   0,   1,   1,   2,   1,
   2,   3, 208,  48,  71,   0,   0,   2,   1,   2,   1,   2,   3, 208,  48,  71,
   0,   0,   3,   1,   2,   1,   2,   3, 208,  48,  71,   0,   0,   4,   1,   2,
   1,   2,   3, 208,  48,  71,   0,   0,   5,   1,   2,   1,   2,   3, 208,  48,
  71,   0,   0,   6,   1,   2,   1,   2,   3, 208,  48,  71,   0,   0,   7,   1,
   2,   1,   2,   3, 208,  48,  71,   0,   0,   8,   1,   2,   1,   2,   3, 208,
  48,  71,   0,   0,   9,   1,   2,   1,   2,   3, 208,  48,  71,   0,   0,  10,
   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  11,   1,   1,   1,   2,
   4, 208,  48,  38,  72,   0,   0,  12,   1,   1,   1,   2,   4, 208,  48,  38,
  72,   0,   0,  13,   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  14,
   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  15,   1,   1,   1,   2,
   4, 208,  48,  38,  72,   0,   0,  16,   1,   1,   1,   2,   4, 208,  48,  38,
  72,   0,   0,  17,   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  18,
   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  19,   1,   1,   1,   2,
   4, 208,  48,  38,  72,   0,   0,  20,   1,   1,   1,   2,   4, 208,  48,  38,
  72,   0,   0,  21,   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  22,
   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  23,   1,   1,   1,   2,
   4, 208,  48,  38,  72,   0,   0,  24,   1,   1,   1,   2,   4, 208,  48,  38,
  72,   0,   0,  25,   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  26,
   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  27,   1,   1,   1,   2,
   4, 208,  48,  38,  72,   0,   0,  28,   1,   1,   1,   2,   4, 208,  48,  38,
  72,   0,   0,  29,   1,   1,   1,   2,   4, 208,  48,  38,  72,   0,   0,  30,
   2,   2,   1,   2,  12, 208,  48,  93,   3, 102,   3, 209,  70,   4,   1,  41,
  71,   0,   0,  31,   1,   1,   1,   2,  10, 208,  48,  93,   3, 102,   3,  70,
   5,   0,  72,   0,   0,  32,   1,   1,   1,   2,  10, 208,  48,  93,   3, 102,
   3,  70,   7,   0,  72,   0,   0,  33,   2,   2,   1,   2,  12, 208,  48,  93,
   3, 102,   3, 209,  70,   9,   1,  41,  71,   0,   0,  34,   2,   2,   1,   2,
  12, 208,  48,  93,   3, 102,   3, 209,  70,   9,   1,  41,  71,   0,   0,  35,
   2,   2,   1,   2,  13, 208,  48,  93,  10, 102,  10, 102,  11, 209,  70,  12,
   1,  72,   0,   0,  36,   1,   1,   1,   2,  11, 208,  48,  93,  14, 102,  14,
  70,  15,   0,  41,  71,   0,   0,  37,   0,   1,   3,   3,   1,  71,   0,   0,
  40,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  41,   1,   1,   4,   5,
   3, 208,  48,  71,   0,   0,  42,   1,   1,   4,   5,   6, 208,  48, 208,  73,
   0,  71,   0,   0,  43,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  45,
   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  46,   2,   1,
   3,   4,  12, 208,  48,  94,  24,  93,  25,  70,  25,   0, 104,  24,  71,   0,
   0,  81,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  82,
   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  88,   1,   1,   4,   5,   6,
 208,  48, 208,  73,   0,  71,   0,   0,  89,   1,   1,   3,   4,   3, 208,  48,
  71,   0,   0,  90,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,
   0,  91,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  92,   1,   1,   4,
   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  93,   1,   1,   3,   4,   3,
 208,  48,  71,   0,   0,  94,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,
  71,   0,   0,  95,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  96,   1,
   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  97,   1,   1,   3,
   4,   3, 208,  48,  71,   0,   0,  98,   1,   1,   4,   5,   6, 208,  48, 208,
  73,   0,  71,   0,   0,  99,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,
 100,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 101,   2,
   1,   3,   4,   9, 208,  48,  94,  83,  36,  42,  97,  83,  71,   0,   0, 102,
   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 103,   2,   1,
   3,   4,   9, 208,  48,  94,  86,  36, 101,  97,  86,  71,   0,   0, 104,   1,
   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 105,   1,   1,   3,
   4,   3, 208,  48,  71,   0,   0, 106,   1,   1,   3,   4,   5, 208,  48,  44,
  97,  72,   0,   0, 107,   1,   1,   3,   4,  10, 208,  48,  93,  89, 102,  89,
  70,  90,   0,  72,   0,   0, 108,   1,   1,   4,   5,   6, 208,  48, 208,  73,
   0,  71,   0,   0, 109,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 110,
   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 111,   1,   1,   4,   5,
   4, 208,  48,  38,  72,   0,   0, 112,   1,   1,   4,   5,   4, 208,  48,  38,
  72,   0,   0, 113,   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 114,
   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 115,   1,   1,   4,   5,
   4, 208,  48,  38,  72,   0,   0, 116,   1,   1,   4,   5,   4, 208,  48,  38,
  72,   0,   0, 117,   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 118,
   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 119,   1,   1,   4,   5,
   4, 208,  48,  38,  72,   0,   0, 120,   1,   1,   4,   5,   4, 208,  48,  38,
  72,   0,   0, 121,   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 122,
   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 123,   1,   1,   4,   5,
   4, 208,  48,  38,  72,   0,   0, 124,   1,   1,   4,   5,   4, 208,  48,  38,
  72,   0,   0, 125,   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 126,
   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,   0, 127,   1,   1,   4,   5,
   4, 208,  48,  38,  72,   0,   0, 128,   1,   1,   1,   4,   5,   4, 208,  48,
  38,  72,   0,   0, 129,   1,   1,   1,   4,   5,   4, 208,  48,  38,  72,   0,
   0, 130,   1,   1,   2,   4,   5,   3, 208,  48,  71,   0,   0, 131,   1,   1,
   2,   4,   5,   3, 208,  48,  71,   0,   0, 132,   1,   1,   2,   4,   5,   3,
 208,  48,  71,   0,   0, 133,   1,   1,   2,   4,   5,   3, 208,  48,  71,   0,
   0, 134,   1,   1,   2,   4,   5,   3, 208,  48,  71,   0,   0, 135,   1,   1,
   2,   4,   5,   3, 208,  48,  71,   0,   0, 136,   1,   1,   2,   4,   5,   3,
 208,  48,  71,   0,   0, 137,   1,   1,   2,   4,   5,   3, 208,  48,  71,   0,
   0, 138,   1,   1,   2,   4,   5,   3, 208,  48,  71,   0,   0, 139,   1,   1,
   2,   4,   5,   3, 208,  48,  71,   0,   0, 140,   1,   1,   1,   4,   5,   6,
 208,  48, 208,  73,   0,  71,   0,   0, 141,   1,   1,   1,   3,   4,   3, 208,
  48,  71,   0,   0, 142,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,
  71,   0,   0, 143,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 144,
   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 145,   1,
   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 146,   1,   1,   1,   4,   5,
   6, 208,  48, 208,  73,   0,  71,   0,   0, 147,   1,   1,   1,   3,   4,   3,
 208,  48,  71,   0,   0, 148,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,
   0,  71,   0,   0, 149,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,
 150,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 151,
   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 152,   1,   1,   1,   4,
   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 153,   1,   1,   1,   3,   4,
   3, 208,  48,  71,   0,   0, 154,   1,   1,   1,   4,   5,   6, 208,  48, 208,
  73,   0,  71,   0,   0, 155,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,
   0, 156,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,
 157,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 158,   1,   1,   1,
   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 159,   1,   0,   1,   3,
   3,   1,  71,   0,   0, 161,   1,   0,   1,   3,   3,   1,  71,   0,   0, 163,
   1,   0,   1,   3,   3,   1,  71,   0,   0, 165,   1,   0,   1,   3,   3,   1,
  71,   0,   0, 167,   1,   0,   1,   3,   3,   1,  71,   0,   0, 169,   1,   0,
   1,   3,   3,   1,  71,   0,   0, 171,   1,   0,   1,   3,   3,   1,  71,   0,
   0, 173,   1,   0,   1,   3,   3,   1,  71,   0,   0, 175,   1,   0,   1,   3,
   3,   1,  71,   0,   0, 177,   1,   0,   1,   3,   3,   1,  71,   0,   0, 179,
   1,   1,   1,   4,   5,   3, 208,  48,  71,   0,   0, 180,   1,   1,   1,   5,
   6,   6, 208,  48, 208,  73,   0,  71,   0,   0, 181,   1,   1,   1,   4,   5,
   3, 208,  48,  71,   0,   0, 182,   1,   1,   1,   5,   6,   6, 208,  48, 208,
  73,   0,  71,   0,   0, 183,   1,   1,   1,   4,   5,   3, 208,  48,  71,   0,
   0, 184,   1,   1,   1,   5,   6,   6, 208,  48, 208,  73,   0,  71,   0,   0,
 185,   1,   1,   1,   4,   5,   3, 208,  48,  71,   0,   0, 186,   1,   1,   1,
   5,   6,   6, 208,  48, 208,  73,   0,  71,   0,   0, 187,   1,   1,   1,   4,
   5,   3, 208,  48,  71,   0,   0, 188,   1,   1,   1,   5,   6,   6, 208,  48,
 208,  73,   0,  71,   0,   0, 189,   1,   1,   1,   4,   5,   3, 208,  48,  71,
   0,   0, 190,   1,   1,   1,   5,   6,   6, 208,  48, 208,  73,   0,  71,   0,
   0, 191,   1,   1,   1,   4,   5,   3, 208,  48,  71,   0,   0, 192,   1,   1,
   1,   5,   6,   6, 208,  48, 208,  73,   0,  71,   0,   0, 193,   1,   1,   1,
   4,   5,   3, 208,  48,  71,   0,   0, 194,   1,   1,   1,   5,   6,   6, 208,
  48, 208,  73,   0,  71,   0,   0, 195,   1,   3,   1,   1,   4, 206,   7, 208,
  48,  93, 165,   1,  32,  88,   0, 104,  17,  93, 166,   1,  93,  20, 102,  20,
  48,  93, 167,   1, 102, 167,   1,  88,   1,  29, 104,  19,  93, 168,   1,  93,
  20, 102,  20,  48,  93, 167,   1, 102, 167,   1,  88,   2,  29, 104,  23,  93,
 169,   1,  93,  20, 102,  20,  48,  93, 167,   1, 102, 167,   1,  88,   3,  29,
 104,  70,  93, 170,   1,  93,  20, 102,  20,  48,  93, 167,   1, 102, 167,   1,
  88,   4,  29, 104,  76,  93, 171,   1,  93,  20, 102,  20,  48,  93, 172,   1,
 102, 172,   1,  88,   5,  29, 104,  77,  93, 173,   1,  93,  20, 102,  20,  48,
  93,  77, 102,  77,  48,  93, 174,   1, 102, 174,   1,  88,  34,  29,  29, 104,
 153,   1,  93, 175,   1,  93,  20, 102,  20,  48,  93,  77, 102,  77,  48,  93,
 174,   1, 102, 174,   1,  88,  35,  29,  29, 104, 154,   1,  93, 176,   1,  93,
  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,   6,  29, 104,  78,  93,
 177,   1,  93,  20, 102,  20,  48,  93,  78, 102,  78,  48,  93, 178,   1, 102,
 178,   1,  88,  36,  29,  29, 104, 155,   1,  93, 179,   1,  93,  20, 102,  20,
  48,  93,  78, 102,  78,  48,  93, 178,   1, 102, 178,   1,  88,  37,  29,  29,
 104, 156,   1,  93, 180,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102, 172,
   1,  88,   7,  29, 104,  79,  93, 181,   1,  93,  20, 102,  20,  48,  93,  79,
 102,  79,  48,  93, 182,   1, 102, 182,   1,  88,  38,  29,  29, 104, 157,   1,
  93, 183,   1,  93,  20, 102,  20,  48,  93,  79, 102,  79,  48,  93, 182,   1,
 102, 182,   1,  88,  39,  29,  29, 104, 158,   1,  93, 184,   1,  93,  20, 102,
  20,  48,  93, 172,   1, 102, 172,   1,  88,   8,  29, 104,  80,  93, 185,   1,
  93,  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,   9,  29, 104,  81,
  93, 186,   1,  93,  20, 102,  20,  48,  93,  81, 102,  81,  48,  93, 187,   1,
 102, 187,   1,  88,  40,  29,  29, 104, 160,   1,  93, 188,   1,  93,  20, 102,
  20,  48,  93,  81, 102,  81,  48,  93, 187,   1, 102, 187,   1,  88,  41,  29,
  29, 104, 164,   1,  93, 189,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102,
 172,   1,  88,  10,  29, 104,  82,  93, 190,   1,  93,  20, 102,  20,  48,  93,
 172,   1, 102, 172,   1,  88,  11,  29, 104,  85,  93, 191,   1,  93,  20, 102,
  20,  48,  93, 172,   1, 102, 172,   1,  88,  12,  29, 104,  88,  93, 192,   1,
  93,  20, 102,  20,  48,  93, 193,   1, 102, 193,   1,  88,  13,  29, 104,  92,
  93, 194,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,  14,
  29, 104, 133,   1,  93, 195,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102,
 172,   1,  88,  15,  29, 104, 134,   1,  93, 196,   1,  93,  20, 102,  20,  48,
  93, 172,   1, 102, 172,   1,  88,  16,  29, 104, 135,   1,  93, 197,   1,  93,
  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,  17,  29, 104, 136,   1,
  93, 198,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,  18,
  29, 104, 137,   1,  93, 199,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102,
 172,   1,  88,  19,  29, 104, 138,   1,  93, 200,   1,  93,  20, 102,  20,  48,
  93, 172,   1, 102, 172,   1,  88,  20,  29, 104, 139,   1,  93, 201,   1,  93,
  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,  21,  29, 104, 140,   1,
  93, 202,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102, 172,   1,  88,  22,
  29, 104, 141,   1,  93, 203,   1,  93,  20, 102,  20,  48,  93, 172,   1, 102,
 172,   1,  88,  23,  29, 104, 142,   1,  93, 204,   1,  32,  88,  24, 104, 143,
   1,  93, 205,   1,  32,  88,  25, 104, 144,   1,  93, 206,   1,  32,  88,  26,
 104, 145,   1,  93, 207,   1,  32,  88,  27, 104, 146,   1,  93, 208,   1,  32,
  88,  28, 104, 147,   1,  93, 209,   1,  32,  88,  29, 104, 148,   1,  93, 210,
   1,  32,  88,  30, 104, 149,   1,  93, 211,   1,  32,  88,  31, 104, 150,   1,
  93, 212,   1,  32,  88,  32, 104, 151,   1,  93, 213,   1,  32,  88,  33, 104,
 152,   1,  93, 214,   1,  37, 149,   5,  37, 148,   5, 161, 104, 215,   1,  93,
 216,   1,  37, 150,   5,  37, 148,   5, 161, 104, 217,   1,  93, 218,   1,  37,
 151,   5,  37, 148,   5, 161, 104, 219,   1,  93, 220,   1,  37, 152,   5,  37,
 148,   5, 161, 104, 221,   1,  93, 222,   1,  37, 153,   5,  37, 148,   5, 161,
 104, 223,   1,  93, 224,   1,  37, 154,   5,  37, 148,   5, 161, 104, 225,   1,
  93, 226,   1,  38,  97, 227,   1,  93, 228,   1,  38,  97, 229,   1,  93, 230,
   1,  38,  97, 231,   1,  93, 232,   1,  38,  97, 233,   1,  93, 234,   1,  38,
  97, 235,   1,  93, 236,   1,  38,  97, 237,   1,  93, 238,   1,  38,  97, 239,
   1,  93, 240,   1,  38,  97, 241,   1,  93, 242,   1,  38,  97, 243,   1,  93,
 244,   1,  38,  97, 245,   1,  93, 246,   1,  38, 104, 247,   1,  93, 248,   1,
  38, 104, 249,   1,  93, 250,   1,  38, 104, 251,   1,  93, 252,   1,  38, 104,
 253,   1,  93, 254,   1,  38, 104, 255,   1,  93, 128,   2,  38, 104, 129,   2,
  93, 130,   2,  38, 104, 131,   2,  93, 132,   2,  38, 104, 133,   2,  93, 134,
   2,  38, 104, 135,   2,  93, 136,   2,  38, 104, 137,   2,  71,   0,   0, 196,
   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 200,   1,   2,   2,   4,
   5,  13, 208,  48, 208,  73,   0, 208, 209,  70, 228,   2,   1,  41,  71,   0,
   0, 203,   1,   3,   3,   4,   5,  20, 208,  48, 208,  93, 229,   2, 102, 229,
   2, 209,  70, 230,   2,   1, 210,  70, 231,   2,   2,  72,   0,   0, 206,   1,
   2,   1,   1,   3,  23, 208,  48,  93, 239,   2,  93,  20, 102,  20,  48,  93,
 240,   2, 102, 240,   2,  88,  42,  29, 104, 227,   2,  71,   0,   0, 212,   1,
   4,   3,   1,   2,  14, 208,  48,  93, 243,   2, 209, 210,  36,   1,  70, 243,
   2,   3,  72,   0,   0, 213,   1,   4,   3,   1,   2,  14, 208,  48,  93, 243,
   2, 209, 210,  36,   2,  70, 243,   2,   3,  72,   0,   0, 214,   1,   4,   3,
   1,   2,  14, 208,  48,  93, 243,   2, 209, 210,  36,   0,  70, 243,   2,   3,
  72,   0,   0, 217,   1,   2,   1,   1,   2,  13, 208,  48,  93, 244,   2, 100,
 108,   5,  70, 244,   2,   1,  72,   0,   0, 221,   1,   3,   3,   3,   6,  47,
  87,  42, 213,  48, 101,   0,  38, 118, 109,   1,  93, 245,   2,  76, 245,   2,
   0,  41,  16,  20,   0,   0, 209,  48,  90,   0,  42, 214,  42,  48,  43, 109,
   1, 101,   0,  39, 118, 109,   1,  29,   8,   2, 101,   0, 108,   1,  72,   1,
  10,  18,  22,   0, 246,   2,   1, 247,   2,   0,   1,   2,   0, 222,   1,   2,
   3,   2,   4,  60, 208,  48,  87,  42, 214,  48, 101,   1,  33, 130, 109,   2,
 101,   1, 209, 109,   1, 101,   1, 108,   1,  32,  19,  24,   0,   0, 101,   1,
  64, 221,   1, 130, 109,   2,  93, 248,   2, 101,   1, 108,   2,  70, 248,   2,
   1,  41,  16,   9,   0,   0,  93, 248,   2,  32,  70, 248,   2,   1,  41,  71,
   0,   2, 249,   2,   0,   1,  34,   0, 250,   2,   0,   2,   0,   0, 228,   1,
   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 229,   1,   3,   1,   4,   5,
  50, 208,  48, 208, 102, 251,   2,  44, 151,   2, 160, 208, 102, 252,   2, 118,
  18,  26,   0,   0,  44, 153,   2, 208, 102, 252,   2, 160,  44, 154,   2, 160,
 208, 102, 253,   2, 160,  44, 156,   2, 160, 130,  16,   3,   0,   0,  44,   1,
 130, 160,  72,   0,   0, 230,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,
   0,  71,   0,   0, 231,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,
 232,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 233,
   1,   2,   1,   3,   4,  39, 208,  48,  94, 135,   3, 100, 108,   1, 104, 135,
   3,  94, 136,   3, 100, 108,   2, 104, 136,   3,  94, 137,   3, 100, 108,   4,
 104, 137,   3,  94, 138,   3, 100, 108,   3, 104, 138,   3,  71,   0,   0, 234,
   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 235,   1,
   1,   1,   4,   5,   3, 208,  48,  71,   0,   0, 238,   1,   1,   1,   5,   6,
   6, 208,  48, 208,  73,   0,  71,   0,   0, 239,   1,   1,   1,   4,   5,   3,
 208,  48,  71,   0,   0, 240,   1,   1,   1,   5,   6,   6, 208,  48, 208,  73,
   0,  71,   0,   0, 241,   1,   2,   1,   1,   4, 108, 208,  48, 101,   0,  93,
  20, 102,  20,  48,  93, 150,   3, 102, 150,   3,  88,  43,  29, 104, 131,   3,
 101,   0,  93,  20, 102,  20,  48,  93, 150,   3, 102, 150,   3,  88,  44,  29,
 104, 134,   3, 101,   0,  93,  20, 102,  20,  48,  93, 134,   3, 102, 134,   3,
  48, 100, 108,   2,  88,  46,  29,  29, 104, 148,   3, 101,   0,  93,  20, 102,
  20,  48,  93, 134,   3, 102, 134,   3,  48, 100, 108,   2,  88,  47,  29,  29,
 104, 149,   3, 101,   0,  93,  20, 102,  20,  48,  93, 150,   3, 102, 150,   3,
  88,  45,  29, 104, 143,   3,  71,   0,   0, 242,   1,   2,   1,   3,   4,  59,
 208,  48,  94, 176,   3,  36,   0, 104, 176,   3,  94, 177,   3,  36,   1, 104,
 177,   3,  94, 178,   3,  36,   2, 104, 178,   3,  94, 179,   3,  36,   3, 104,
 179,   3,  94, 180,   3,  36,   4, 104, 180,   3,  94, 181,   3,  36,   1, 104,
 181,   3,  94, 182,   3,  36,   2, 104, 182,   3,  71,   0,   0, 247,   1,   1,
   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 248,   1,   2,   1,
   1,   3,  22, 208,  48, 101,   0,  93,  20, 102,  20,  48,  93, 195,   3, 102,
 195,   3,  88,  48,  29, 104, 194,   3,  71,   0,   0, 249,   1,   2,   1,   3,
   4,  21, 208,  48,  94, 197,   3,  44, 232,   2, 104, 197,   3,  94, 198,   3,
  44, 234,   2, 104, 198,   3,  71,   0,   0, 250,   1,   1,   1,   4,   5,   6,
 208,  48, 208,  73,   0,  71,   0,   0, 251,   1,   2,   1,   1,   3,  22, 208,
  48, 101,   0,  93,  20, 102,  20,  48,  93, 202,   3, 102, 202,   3,  88,  49,
  29, 104, 201,   3,  71,   0,   0, 252,   1,   2,   1,   3,   4,  57, 208,  48,
  94, 204,   3,  44, 240,   2, 104, 204,   3,  94, 205,   3,  44, 242,   2, 104,
 205,   3,  94, 206,   3,  44, 244,   2, 104, 206,   3,  94, 207,   3,  44, 246,
   2, 104, 207,   3,  94, 208,   3,  44, 248,   2, 104, 208,   3,  94, 209,   3,
  44, 250,   2, 104, 209,   3,  71,   0,   0, 253,   1,   3,   2,   3,   4,  99,
 208,  48, 209,  93, 210,   3, 102, 210,   3,  20,   3,   0,   0,  36,   1,  72,
 209,  93, 211,   3, 102, 211,   3,  20,   3,   0,   0,  36,   2,  72, 209,  93,
 212,   3, 102, 212,   3,  20,   3,   0,   0,  36,   3,  72, 209,  93, 213,   3,
 102, 213,   3,  20,   3,   0,   0,  36,   4,  72, 209,  93, 214,   3, 102, 214,
   3,  20,   3,   0,   0,  36,   5,  72, 209,  93, 215,   3, 102, 215,   3,  20,
   3,   0,   0,  36,   6,  72,  93, 216,   3,  44, 253,   2, 209, 160,  70, 216,
   3,   1,   3,   0,   0, 254,   1,   1,   1,   4,   5,   6, 208,  48, 208,  73,
   0,  71,   0,   0, 255,   1,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,
 128,   2,   1,   1,   3,   4,   9, 208,  48,  93, 225,   3, 102, 225,   3,  72,
   0,   0, 130,   2,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,
   0, 131,   2,   1,   1,   4,   5,   8, 208,  48, 208,  70, 227,   3,   0,  72,
   0,   0, 139,   2,   2,   1,   3,   4,  12, 208,  48,  94, 240,   3,  44, 144,
   3, 104, 240,   3,  71,   0,   0, 140,   2,   2,   3,   4,   5,  16, 208,  48,
 208,  73,   0, 208, 209, 104, 241,   3, 208, 210, 104, 242,   3,  71,   0,   0,
 141,   2,   1,   1,   4,   5,   7, 208,  48, 208, 102, 242,   3,  72,   0,   0,
 142,   2,   1,   1,   4,   5,   7, 208,  48, 208, 102, 241,   3,  72,   0,   0,
 143,   2,   1,   1,   4,   5,   7, 208,  48, 208, 102, 243,   3,  72,   0,   0,
 144,   2,   2,   1,   1,   3,  63, 208,  48,  93, 252,   3,  93,  20, 102,  20,
  48,  93, 253,   3, 102, 253,   3,  88,  50,  29, 104, 224,   3,  93, 254,   3,
  93,  20, 102,  20,  48,  93, 253,   3, 102, 253,   3,  88,  51,  29, 104, 226,
   3,  93, 255,   3,  93,  20, 102,  20,  48,  93, 253,   3, 102, 253,   3,  88,
  52,  29, 104, 251,   3,  71,   0,   0, 145,   2,   1,   1,   3,   4,   3, 208,
  48,  71,   0,   0, 146,   2,   1,   1,   3,   4,   9, 208,  48,  93, 131,   4,
 102, 131,   4,  72,   0,   0, 147,   2,   1,   1,   4,   5,   6, 208,  48, 208,
  73,   0,  71,   0,   0, 148,   2,   2,   2,   4,   5,   9, 208,  48, 208, 209,
  70, 133,   4,   1,  72,   0,   0, 149,   2,   2,   1,   4,   5,   9, 208,  48,
 208,  32,  70, 133,   4,   1,  72,   0,   0, 152,   2,   2,   1,   1,   3,  22,
 208,  48, 101,   0,  93,  20, 102,  20,  48,  93, 140,   4, 102, 140,   4,  88,
  53,  29, 104, 132,   4,  71,   0,   0};


/* versioned_uris */
const char* const shell_toplevel_versioned_uris[] = {
    "__AS3__.vec", // [660]
    "avm2.intrinsics.memory", // [684]
    "avmplus", // [660]
    "avmshell", // [660, 661, 662, 663, 664, 665, 666]
    "flash.concurrent", // [684]
    "flash.errors", // [660]
    "flash.net", // [660]
    "flash.sampler", // [660]
    "flash.system", // [660, 682]
    "flash.trace", // [660]
    "flash.utils", // [660]
    NULL
};

#ifdef VMCFG_AOT
extern "C" const struct {
    const char* const n_0; avmplus::DomainClass* const m_0;
    const char* const n_1; avmplus::DomainObject* const m_1;
    const char* const n_2; avmplus::NewObjectSampleClass* const m_2;
    const char* const n_3; avmplus::NewObjectSampleObject* const m_3;
    const char* const n_4; avmplus::TraceClass* const m_4;
    const char* const n_5; avmshell::AbstractBaseClass* const m_5;
    const char* const n_6; avmshell::AbstractBaseObject* const m_6;
    const char* const n_7; avmshell::AbstractRestrictedBaseClass* const m_7;
    const char* const n_8; avmshell::AbstractRestrictedBaseObject* const m_8;
    const char* const n_9; avmshell::CheckBaseClass* const m_9;
    const char* const n_10; avmshell::CheckBaseObject* const m_10;
    const char* const n_11; avmshell::FileClass* const m_11;
    const char* const n_12; avmshell::MIClass* const m_12;
    const char* const n_13; avmshell::MIObject* const m_13;
    const char* const n_14; avmshell::NativeBaseClass* const m_14;
    const char* const n_15; avmshell::NativeBaseObject* const m_15;
    const char* const n_16; avmshell::NativeSubclassOfAbstractBaseClass* const m_16;
    const char* const n_17; avmshell::NativeSubclassOfAbstractBaseObject* const m_17;
    const char* const n_18; avmshell::NativeSubclassOfAbstractRestrictedBaseClass* const m_18;
    const char* const n_19; avmshell::NativeSubclassOfAbstractRestrictedBaseObject* const m_19;
    const char* const n_20; avmshell::NativeSubclassOfRestrictedBaseClass* const m_20;
    const char* const n_21; avmshell::NativeSubclassOfRestrictedBaseObject* const m_21;
    const char* const n_22; avmshell::RestrictedBaseClass* const m_22;
    const char* const n_23; avmshell::RestrictedBaseObject* const m_23;
    const char* const n_24; avmshell::ShellWorkerClass* const m_24;
    const char* const n_25; avmshell::ShellWorkerDomainClass* const m_25;
    const char* const n_26; avmshell::ShellWorkerDomainObject* const m_26;
    const char* const n_27; avmshell::ShellWorkerObject* const m_27;
    const char* const n_28; avmshell::SystemClass* const m_28;
} aotABCTypes_shell_toplevel = {
    "DomainClass", 0,
    "DomainObject", 0,
    "NewObjectSampleClass", 0,
    "NewObjectSampleObject", 0,
    "TraceClass", 0,
    "::avmshell::AbstractBaseClass", 0,
    "::avmshell::AbstractBaseObject", 0,
    "::avmshell::AbstractRestrictedBaseClass", 0,
    "::avmshell::AbstractRestrictedBaseObject", 0,
    "::avmshell::CheckBaseClass", 0,
    "::avmshell::CheckBaseObject", 0,
    "::avmshell::FileClass", 0,
    "::avmshell::MIClass", 0,
    "::avmshell::MIObject", 0,
    "::avmshell::NativeBaseClass", 0,
    "::avmshell::NativeBaseObject", 0,
    "::avmshell::NativeSubclassOfAbstractBaseClass", 0,
    "::avmshell::NativeSubclassOfAbstractBaseObject", 0,
    "::avmshell::NativeSubclassOfAbstractRestrictedBaseClass", 0,
    "::avmshell::NativeSubclassOfAbstractRestrictedBaseObject", 0,
    "::avmshell::NativeSubclassOfRestrictedBaseClass", 0,
    "::avmshell::NativeSubclassOfRestrictedBaseObject", 0,
    "::avmshell::RestrictedBaseClass", 0,
    "::avmshell::RestrictedBaseObject", 0,
    "::avmshell::ShellWorkerClass", 0,
    "::avmshell::ShellWorkerDomainClass", 0,
    "::avmshell::ShellWorkerDomainObject", 0,
    "::avmshell::ShellWorkerObject", 0,
    "::avmshell::SystemClass", 0,
};
#endif
} }
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::CTestClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::CTestClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::CTestClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_CTestClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::CTestClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::CTestObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::CTestClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::CTestClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_CTestClass
    m_slots_CTestClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::CTestClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::CTestObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::CTestObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_CTestObject
    m_slots_CTestObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::CTestObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::MIClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::MIClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmshell::MIClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_MIClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::MIClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), cls->getExtraSize()) avmshell::MIObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::MIClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::MIObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::SystemClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::SystemClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_SystemClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::SystemClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SystemObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::SystemObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SystemObject
    m_slots_SystemObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SystemObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::FileClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmshell::FileClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_FileClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::FileClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::FileObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::FileObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_FileObject
    m_slots_FileObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::FileObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::AbstractBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::AbstractBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_AbstractBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::AbstractBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::AbstractBaseObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::RestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::RestrictedBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::RestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_RestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::RestrictedBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::RestrictedBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::RestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::RestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::AbstractRestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::AbstractRestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_AbstractRestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::AbstractRestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::AbstractRestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::CheckBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::CheckBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::CheckBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_CheckBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::CheckBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    avmshell::CheckBaseClass::preCreateInstanceCheck(cls);
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::CheckBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::CheckBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::CheckBaseObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::NativeBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::NativeBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_NativeBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::NativeBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::NativeBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeBaseObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::NativeBaseAS3Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::NativeBaseAS3Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_NativeBaseAS3Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::NativeBaseAS3Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::NativeBaseAS3Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseAS3Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::NativeBaseAS3Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseAS3Class
    m_slots_NativeBaseAS3Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseAS3Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseAS3Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::NativeBaseAS3Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseAS3Object
    m_slots_NativeBaseAS3Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseAS3Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::ShellCoreFriend1Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::ShellCoreFriend1Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::ShellCoreFriend1Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_ShellCoreFriend1Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::ShellCoreFriend1Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::ShellCoreFriend1Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ShellCoreFriend1Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::ShellCoreFriend1Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ShellCoreFriend1Class
    m_slots_ShellCoreFriend1Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::ShellCoreFriend1Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ShellCoreFriend1Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::ShellCoreFriend1Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ShellCoreFriend1Object
    m_slots_ShellCoreFriend1Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::ShellCoreFriend1Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::ShellCoreFriend2Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::ShellCoreFriend2Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::ShellCoreFriend2Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_ShellCoreFriend2Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::ShellCoreFriend2Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::ShellCoreFriend2Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ShellCoreFriend2Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::ShellCoreFriend2Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ShellCoreFriend2Class
    m_slots_ShellCoreFriend2Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::ShellCoreFriend2Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ShellCoreFriend2Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::ShellCoreFriend2Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ShellCoreFriend2Object
    m_slots_ShellCoreFriend2Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::ShellCoreFriend2Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::CapabilitiesClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::CapabilitiesClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::CapabilitiesClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_CapabilitiesClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::CapabilitiesClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::CapabilitiesObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::CapabilitiesClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::CapabilitiesClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_CapabilitiesClass
    m_slots_CapabilitiesClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::CapabilitiesClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::CapabilitiesObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::CapabilitiesObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_CapabilitiesObject
    m_slots_CapabilitiesObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::CapabilitiesObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_classClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_classClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_classClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_classClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_classClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_classObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_classClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_classClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_classClass
    m_slots_public_classClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_classClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_classObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_classObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_classObject
    m_slots_public_classObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_classObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_0Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_0Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_0Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_0Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_0Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_0Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_0Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_0Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_0Class
    m_slots_public_class_AIR_1_0Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_0Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_0Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_0Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_0Object
    m_slots_public_class_AIR_1_0Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_0Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_FP_10_0Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_FP_10_0Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_FP_10_0Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_FP_10_0Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_FP_10_0Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0Class
    m_slots_public_class_FP_10_0Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0Object
    m_slots_public_class_FP_10_0Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_5Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_5Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_5Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_5Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_5Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5Class
    m_slots_public_class_AIR_1_5Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5Object
    m_slots_public_class_AIR_1_5Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_5_1Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_5_1Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_5_1Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_1Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_5_1Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_5_1Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_1Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_1Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_1Class
    m_slots_public_class_AIR_1_5_1Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_1Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_1Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_1Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_1Object
    m_slots_public_class_AIR_1_5_1Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_1Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_FP_10_0_32Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_FP_10_0_32Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_FP_10_0_32Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0_32Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_FP_10_0_32Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_FP_10_0_32Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0_32Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0_32Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0_32Class
    m_slots_public_class_FP_10_0_32Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0_32Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0_32Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0_32Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0_32Object
    m_slots_public_class_FP_10_0_32Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0_32Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_5_2Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_5_2Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_5_2Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_2Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_5_2Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_5_2Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_2Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_2Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_2Class
    m_slots_public_class_AIR_1_5_2Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_2Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_2Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_2Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_2Object
    m_slots_public_class_AIR_1_5_2Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_2Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_0_FP_10_0Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_0_FP_10_0Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_0_FP_10_0Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_0_FP_10_0Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_0_FP_10_0Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_0_FP_10_0Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_0_FP_10_0Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_0_FP_10_0Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_0_FP_10_0Class
    m_slots_public_class_AIR_1_0_FP_10_0Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_0_FP_10_0Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_0_FP_10_0Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_0_FP_10_0Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_0_FP_10_0Object
    m_slots_public_class_AIR_1_0_FP_10_0Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_0_FP_10_0Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class
    m_slots_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object
    m_slots_public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_AIR_1_5_1_FP_10_0_AIR_1_5_2Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class
    m_slots_public_class_FP_10_0_32_AIR_1_0_FP_10_0Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Object::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_public_class_FP_10_0_32_AIR_1_0_FP_10_0Object
    m_slots_public_class_FP_10_0_32_AIR_1_0_FP_10_0Object.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::public_class_FP_10_0_32_AIR_1_0_FP_10_0Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::NativeSubclassOfAbstractBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::NativeSubclassOfAbstractBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::NativeSubclassOfAbstractBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfAbstractBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::NativeSubclassOfAbstractBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::NativeSubclassOfAbstractBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfAbstractBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfAbstractBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::AbstractBaseObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::SubclassOfAbstractBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::SubclassOfAbstractBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::SubclassOfAbstractBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_SubclassOfAbstractBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::SubclassOfAbstractBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::SubclassOfAbstractBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfAbstractBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::SubclassOfAbstractBaseClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfAbstractBaseClass
    m_slots_SubclassOfAbstractBaseClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfAbstractBaseClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfAbstractBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::AbstractBaseObject::construct(argc, argv); } )
bool avmplus::SubclassOfAbstractBaseObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfAbstractBaseObject
    m_slots_SubclassOfAbstractBaseObject.gcTracePrivateProperties(gc);
#endif
    avmshell::AbstractBaseObject::gcTrace(gc, 0);
    (void)(avmshell_AbstractBaseObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfAbstractBaseObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmshell::AbstractBaseObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::NativeSubclassOfRestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::NativeSubclassOfRestrictedBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::NativeSubclassOfRestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfRestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::NativeSubclassOfRestrictedBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::NativeSubclassOfRestrictedBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfRestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfRestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::RestrictedBaseObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::SubclassOfRestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::SubclassOfRestrictedBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::SubclassOfRestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_SubclassOfRestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::SubclassOfRestrictedBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::SubclassOfRestrictedBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfRestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::SubclassOfRestrictedBaseClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfRestrictedBaseClass
    m_slots_SubclassOfRestrictedBaseClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfRestrictedBaseClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfRestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::RestrictedBaseObject::construct(argc, argv); } )
bool avmplus::SubclassOfRestrictedBaseObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfRestrictedBaseObject
    m_slots_SubclassOfRestrictedBaseObject.gcTracePrivateProperties(gc);
#endif
    avmshell::RestrictedBaseObject::gcTrace(gc, 0);
    (void)(avmshell_RestrictedBaseObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfRestrictedBaseObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmshell::RestrictedBaseObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::NativeSubclassOfAbstractRestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::NativeSubclassOfAbstractRestrictedBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmshell::NativeSubclassOfAbstractRestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_NativeSubclassOfAbstractRestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::NativeSubclassOfAbstractRestrictedBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmshell::NativeSubclassOfAbstractRestrictedBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfAbstractRestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::NativeSubclassOfAbstractRestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::AbstractRestrictedBaseObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::SubclassOfAbstractRestrictedBaseClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::SubclassOfAbstractRestrictedBaseClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::SubclassOfAbstractRestrictedBaseClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_SubclassOfAbstractRestrictedBaseClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::SubclassOfAbstractRestrictedBaseClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::SubclassOfAbstractRestrictedBaseObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfAbstractRestrictedBaseClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::SubclassOfAbstractRestrictedBaseClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfAbstractRestrictedBaseClass
    m_slots_SubclassOfAbstractRestrictedBaseClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfAbstractRestrictedBaseClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SubclassOfAbstractRestrictedBaseObject::construct(int argc, avmplus::Atom* argv) { return avmshell::AbstractRestrictedBaseObject::construct(argc, argv); } )
bool avmplus::SubclassOfAbstractRestrictedBaseObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SubclassOfAbstractRestrictedBaseObject
    m_slots_SubclassOfAbstractRestrictedBaseObject.gcTracePrivateProperties(gc);
#endif
    avmshell::AbstractRestrictedBaseObject::gcTrace(gc, 0);
    (void)(avmshell_AbstractRestrictedBaseObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SubclassOfAbstractRestrictedBaseObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmshell::AbstractRestrictedBaseObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::NativeBaseExtender1Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::NativeBaseExtender1Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::NativeBaseExtender1Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_NativeBaseExtender1Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::NativeBaseExtender1Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::NativeBaseExtender1Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseExtender1Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::NativeBaseExtender1Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseExtender1Class
    m_slots_NativeBaseExtender1Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseExtender1Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseExtender1Object::construct(int argc, avmplus::Atom* argv) { return avmshell::NativeBaseObject::construct(argc, argv); } )
bool avmplus::NativeBaseExtender1Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseExtender1Object
    m_slots_NativeBaseExtender1Object.gcTracePrivateProperties(gc);
#endif
    avmshell::NativeBaseObject::gcTrace(gc, 0);
    (void)(avmshell_NativeBaseObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseExtender1Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmshell::NativeBaseObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::NativeBaseExtender2Class::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::NativeBaseExtender2Class::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::NativeBaseExtender2Class(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_NativeBaseExtender2Class(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::NativeBaseExtender2Class::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::NativeBaseExtender2Object(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseExtender2Class::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::NativeBaseExtender2Class::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseExtender2Class
    m_slots_NativeBaseExtender2Class.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseExtender2Class::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NativeBaseExtender2Object::construct(int argc, avmplus::Atom* argv) { return avmshell::NativeBaseObject::construct(argc, argv); } )
bool avmplus::NativeBaseExtender2Object::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_NativeBaseExtender2Object
    m_slots_NativeBaseExtender2Object.gcTracePrivateProperties(gc);
#endif
    avmshell::NativeBaseObject::gcTrace(gc, 0);
    (void)(avmshell_NativeBaseObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::NativeBaseExtender2Object::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmshell::NativeBaseObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::DomainClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::DomainClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::DomainClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_DomainClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::DomainClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::DomainObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::DomainClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::DomainObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::StackFrameClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::StackFrameClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::StackFrameClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_StackFrameClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::StackFrameClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::StackFrameObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::StackFrameClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::StackFrameClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_StackFrameClass
    m_slots_StackFrameClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::StackFrameClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::StackFrameObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::StackFrameObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_StackFrameObject
    m_slots_StackFrameObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::StackFrameObject::gcTracePointerOffsets[] = {
    offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject.m_name),
    offsetof(avmplus::StackFrameObject, m_slots_StackFrameObject.m_file),
    0};
MMgc::GCTracerCheckResult avmplus::StackFrameObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,2);
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::SampleClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::SampleClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::SampleClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_SampleClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::SampleClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::SampleObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SampleClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::SampleClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SampleClass
    m_slots_SampleClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::SampleClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::SampleObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::SampleObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_SampleObject
    m_slots_SampleObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::SampleObject::gcTracePointerOffsets[] = {
    offsetof(avmplus::SampleObject, m_slots_SampleObject.m_stack),
    0};
MMgc::GCTracerCheckResult avmplus::SampleObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,1);
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::ClassFactoryClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::ClassFactoryClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::ClassFactoryClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_ClassFactoryClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::ClassFactoryClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::ClassFactoryObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ClassFactoryClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::ClassFactoryClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ClassFactoryClass
    m_slots_ClassFactoryClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::ClassFactoryClass::gcTracePointerOffsets[] = {
    offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass.m_StackFrameClass),
    offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass.m_SampleClass),
    offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass.m_DeleteObjectSampleClass),
    offsetof(avmplus::ClassFactoryClass, m_slots_ClassFactoryClass.m_NewObjectSampleClass),
    0};
MMgc::GCTracerCheckResult avmplus::ClassFactoryClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,4);
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::ClassFactoryObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::ClassFactoryObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_ClassFactoryObject
    m_slots_ClassFactoryObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::ClassFactoryObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::NewObjectSampleClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::NewObjectSampleClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmplus::NewObjectSampleClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_NewObjectSampleClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::NewObjectSampleClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), cls->getExtraSize()) avmplus::NewObjectSampleObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NewObjectSampleClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::NewObjectSampleObject::construct(int argc, avmplus::Atom* argv) { return avmplus::SampleObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::DeleteObjectSampleClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::DeleteObjectSampleClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::DeleteObjectSampleClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_DeleteObjectSampleClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::DeleteObjectSampleClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::DeleteObjectSampleObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::DeleteObjectSampleClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::DeleteObjectSampleClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_DeleteObjectSampleClass
    m_slots_DeleteObjectSampleClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::DeleteObjectSampleClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::DeleteObjectSampleObject::construct(int argc, avmplus::Atom* argv) { return avmplus::SampleObject::construct(argc, argv); } )
bool avmplus::DeleteObjectSampleObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_DeleteObjectSampleObject
    m_slots_DeleteObjectSampleObject.gcTracePrivateProperties(gc);
#endif
    avmplus::SampleObject::gcTrace(gc, 0);
    (void)(avmplus_SampleObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::DeleteObjectSampleObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::SampleObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::TraceClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmplus::TraceClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_TraceClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::TraceClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::TraceObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::TraceObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_TraceObject
    m_slots_TraceObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::TraceObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::EndianClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::EndianClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::EndianClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_EndianClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::EndianClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::EndianObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::EndianClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::EndianClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_EndianClass
    m_slots_EndianClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::EndianClass::gcTracePointerOffsets[] = {
    offsetof(avmplus::EndianClass, m_slots_EndianClass.m_BIG_ENDIAN),
    offsetof(avmplus::EndianClass, m_slots_EndianClass.m_LITTLE_ENDIAN),
    0};
MMgc::GCTracerCheckResult avmplus::EndianClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,2);
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::EndianObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::EndianObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_EndianObject
    m_slots_EndianObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::EndianObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::WorkerStateClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::WorkerStateClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::WorkerStateClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_WorkerStateClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::WorkerStateClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::WorkerStateObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::WorkerStateClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::WorkerStateClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_WorkerStateClass
    m_slots_WorkerStateClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::WorkerStateClass::gcTracePointerOffsets[] = {
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_NEW),
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_RUNNING),
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_TERMINATED),
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_FAILED),
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_ABORTED),
    offsetof(avmplus::WorkerStateClass, m_slots_WorkerStateClass.m_EXCEPTION),
    0};
MMgc::GCTracerCheckResult avmplus::WorkerStateClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,6);
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::WorkerStateObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::WorkerStateObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_WorkerStateObject
    m_slots_WorkerStateObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
MMgc::GCTracerCheckResult avmplus::WorkerStateObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::kOffsetNotFound;
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::ShellWorkerClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = ClassClosure::cantInstantiateCreateInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmshell::ShellWorkerClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_ShellWorkerClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::ShellWorkerClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), cls->getExtraSize()) avmshell::ShellWorkerObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::ShellWorkerClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::ShellWorkerObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
/*static*/ avmplus::ClassClosure* FASTCALL avmplus::WorkerEventClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmplus::WorkerEventClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), MMgc::kExact, cvtable->getExtraSize()) avmplus::WorkerEventClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmplus_WorkerEventClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmplus::WorkerEventClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), MMgc::kExact, cls->getExtraSize()) avmplus::WorkerEventObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::WorkerEventClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
bool avmplus::WorkerEventClass::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_WorkerEventClass
    m_slots_WorkerEventClass.gcTracePrivateProperties(gc);
#endif
    avmplus::ClassClosure::gcTrace(gc, 0);
    (void)(avmplus_ClassClosure_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::WorkerEventClass::gcTracePointerOffsets[] = {
    offsetof(avmplus::WorkerEventClass, m_slots_WorkerEventClass.m_WORKER_STATE),
    0};
MMgc::GCTracerCheckResult avmplus::WorkerEventClass::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ClassClosure::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,1);
}
#endif // GCDEBUG
AvmThunk_DEBUG_ONLY( avmplus::Atom avmplus::WorkerEventObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
bool avmplus::WorkerEventObject::gcTrace(MMgc::GC* gc, size_t _xact_cursor)
{
    (void)gc;
    (void)_xact_cursor;
#ifndef GC_TRIVIAL_TRACER_WorkerEventObject
    m_slots_WorkerEventObject.gcTracePrivateProperties(gc);
#endif
    avmplus::ScriptObject::gcTrace(gc, 0);
    (void)(avmplus_ScriptObject_isExactInterlock != 0);
    return false;
}
#ifdef GCDEBUG
const uint32_t avmplus::WorkerEventObject::gcTracePointerOffsets[] = {
    offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject.m_private_m_previousState),
    offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject.m_private_m_currentState),
    offsetof(avmplus::WorkerEventObject, m_slots_WorkerEventObject.m_flash_system_m_target),
    0};
MMgc::GCTracerCheckResult avmplus::WorkerEventObject::gcTraceOffsetIsTraced(uint32_t off) const
{
    MMgc::GCTracerCheckResult result;
    (void)off;
    (void)result;
    if ((result = avmplus::ScriptObject::gcTraceOffsetIsTraced(off)) != MMgc::kOffsetNotFound) return result;
    return MMgc::GC::CheckOffsetIsInList(off,gcTracePointerOffsets,3);
}
#endif // GCDEBUG
/*static*/ avmplus::ClassClosure* FASTCALL avmshell::ShellWorkerDomainClass::createClassClosure(avmplus::VTable* cvtable)
{
    cvtable->ivtable->createInstanceProc = avmshell::ShellWorkerDomainClass::createInstanceProc;
    ClassClosure* const cc = new (cvtable->gc(), cvtable->getExtraSize()) avmshell::ShellWorkerDomainClass(cvtable);
    AvmThunk_DEBUG_ONLY( avmplus::NativeID::SlotOffsetsAndAsserts::check_avmshell_ShellWorkerDomainClass(cc->traits(), cc->traits()->itraits); )
    return cc;
}
/*static*/ avmplus::ScriptObject* FASTCALL avmshell::ShellWorkerDomainClass::createInstanceProc(avmplus::ClassClosure* cls)
{
    return new (cls->gc(), cls->getExtraSize()) avmshell::ShellWorkerDomainObject(cls->ivtable(), cls->prototypePtr());
}
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::ShellWorkerDomainClass::construct(int argc, avmplus::Atom* argv) { return avmplus::ClassClosure::construct(argc, argv); } )
AvmThunk_DEBUG_ONLY( avmplus::Atom avmshell::ShellWorkerDomainObject::construct(int argc, avmplus::Atom* argv) { return avmplus::ScriptObject::construct(argc, argv); } )
