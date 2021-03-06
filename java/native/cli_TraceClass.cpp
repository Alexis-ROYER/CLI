/*
    Copyright (c) 2006-2018, Alexis Royer, http://alexis.royer.free.fr/CLI

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
          and/or other materials provided with the distribution.
        * Neither the name of the CLI library project nor the names of its contributors may be used to endorse or promote products derived from this software
          without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "cli/pch.h"

#include "cli/traces.h"
#include "cli/help.h"

#include "cli_TraceClass.h"

#include "NativeObject.h"
#include "NativeExec.h"
#include "NativeTraces.h"


extern "C" JNIEXPORT jlong JNICALL Java_cli_TraceClass__1_1getJniTraceClass(
        JNIEnv* PJ_Env, jclass PJ_Class)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("TraceClass.__getJniTraceClass()") << cli::endl;

    const NativeObject::REF i64_TraceClassRef = NativeObject::GetNativeRef(NativeTraces::GetTraceClass());

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("TraceClass.__TraceClass()", i64_TraceClassRef) << cli::endl;
    return i64_TraceClassRef;
}

extern "C" JNIEXPORT jlong JNICALL Java_cli_TraceClass__1_1TraceClass(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jstring PJ_TraceClassName, jlong I64_NativeHelpRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("TraceClass.__TraceClass(PJ_TraceClassName, I64_NativeHelpRef)") << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamStr("PJ_TraceClassName", NativeExec::Java2Native(PJ_TraceClassName).c_str()) << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamInt64("I64_NativeHelpRef", I64_NativeHelpRef) << cli::endl;
    NativeObject::REF i64_TraceClassRef = 0;
    if (const cli::Help* const pcli_Help = NativeObject::GetNativeObject<const cli::Help*>(I64_NativeHelpRef))
    {
        if (cli::TraceClass* const pcli_TraceClass = new cli::TraceClass(NativeExec::Java2Native(PJ_TraceClassName).c_str(), *pcli_Help))
        {
            NativeObject::Use(*pcli_TraceClass);
            i64_TraceClassRef = NativeObject::GetNativeRef(*pcli_TraceClass);
        }
    }
    else
    {
        if (cli::TraceClass* const pcli_TraceClass = new cli::TraceClass(NativeExec::Java2Native(PJ_TraceClassName).c_str(), cli::Help()))
        {
            NativeObject::Use(*pcli_TraceClass);
            i64_TraceClassRef = NativeObject::GetNativeRef(*pcli_TraceClass);
        }
    }
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("TraceClass.__TraceClass()", i64_TraceClassRef) << cli::endl;
    return i64_TraceClassRef;
}

extern "C" JNIEXPORT jstring JNICALL Java_cli_TraceClass__1_1getClassName(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeTraceClassRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("TraceClass.__getClassName(I64_NativeTraceClassRef)") << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamInt64("I64_NativeTraceClassRef", I64_NativeTraceClassRef) << cli::endl;
    std::string str_ClassName;
    if (const cli::TraceClass* const pcli_TraceClass = NativeObject::GetNativeObject<const cli::TraceClass*>(I64_NativeTraceClassRef))
    {
        str_ClassName = (const char*) pcli_TraceClass->GetName();
    }
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndStr("TraceClass.__getClassName()", str_ClassName.c_str()) << cli::endl;
    return NativeExec::Native2Java(str_ClassName);
}

extern "C" JNIEXPORT jlong JNICALL Java_cli_TraceClass__1_1getHelp(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeTraceClassRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("TraceClass.__getHelp(I64_NativeTraceClassRef)") << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamInt64("I64_NativeTraceClassRef", I64_NativeTraceClassRef) << cli::endl;
    NativeObject::REF i64_HelpRef = 0;
    if (const cli::TraceClass* const pcli_TraceClass = NativeObject::GetNativeObject<const cli::TraceClass*>(I64_NativeTraceClassRef))
    {
        const cli::Help& cli_Help = pcli_TraceClass->GetHelp();
        NativeObject::CreateFromNative(cli_Help);
        NativeObject::Delegate(cli_Help, *pcli_TraceClass);
        i64_HelpRef = NativeObject::GetNativeRef(cli_Help);
    }
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("TraceClass.__getHelp()", i64_HelpRef) << cli::endl;
    return i64_HelpRef;
}
