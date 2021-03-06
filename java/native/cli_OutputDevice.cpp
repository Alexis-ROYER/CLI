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

#include "cli/io_device.h"

#include "cli_OutputDevice.h"

#include "NativeDevice.h"
#include "NativeObject.h"
#include "NativeExec.h"
#include "NativeTraces.h"


// OutputDevice.Common implementation.

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Common_1_1putInteger(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef, jint I_Integer)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Common.__putInteger(I64_NativeOutputDeviceRef, I_Integer)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt("I_Integer", I_Integer) << cli::endl;

        pcli_OutputDevice->operator<<((int) I_Integer);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Common.__putInteger()") << cli::endl;
    }
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Common_1_1putFloat(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef, jfloat F_Float)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Common.__putFloat(I64_NativeOutputDeviceRef, F_Float)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamFloat("F_Float", F_Float) << cli::endl;

        pcli_OutputDevice->operator<<((float) F_Float);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Common.__putFloat()") << cli::endl;
    }
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Common_1_1putDouble(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef, jdouble D_Double)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Common.__putDouble(I64_NativeOutputDeviceRef, D_Double)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamFloat("D_Double", D_Double) << cli::endl;

        pcli_OutputDevice->operator<<((double) D_Double);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Common.__putDouble()") << cli::endl;
    }
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Common_1_1endl(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Common.__endl(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        pcli_OutputDevice->operator<<(cli::endl);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Common.__endl()") << cli::endl;
    }
}


// OutputDevice.Native implementation.

extern "C" JNIEXPORT jboolean JNICALL Java_cli_OutputDevice__1_1Native_1_1openDevice(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    bool b_Res = false;
    if (cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__openDevice(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        b_Res = pcli_OutputDevice->OpenUp(__CALL_INFO__);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndBool("OutputDevice.Native.__openDevice()", b_Res) << cli::endl;
    }
    return b_Res;
}

extern "C" JNIEXPORT jboolean JNICALL Java_cli_OutputDevice__1_1Native_1_1closeDevice(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    bool b_Res = false;
    if (cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__closeDevice(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        b_Res = pcli_OutputDevice->CloseDown(__CALL_INFO__);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndBool("OutputDevice.Native.__closeDevice()", b_Res) << cli::endl;
    }
    return b_Res;
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Native_1_1putString(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef, jstring PJ_Text)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__putString(I64_NativeOutputDeviceRef, PJ_Text)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamStr("PJ_Text", NativeExec::Java2Native(PJ_Text).c_str()) << cli::endl;

        pcli_OutputDevice->operator<<(NativeExec::Java2Native(PJ_Text).c_str());

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Native.__putString()") << cli::endl;
    }
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Native_1_1beep(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__beep(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        pcli_OutputDevice->Beep();

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Native.__beep()") << cli::endl;
    }
}

extern "C" JNIEXPORT void JNICALL Java_cli_OutputDevice__1_1Native_1_1cleanScreen(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__cleanScreen(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        pcli_OutputDevice->CleanScreen();

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndVoid("OutputDevice.Native.__cleanScreen()") << cli::endl;
    }
}

extern "C" JNIEXPORT jlong JNICALL Java_cli_OutputDevice__1_1Native_1_1getScreenInfo(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    NativeObject::REF i64_ScreenInfoRef = 0;
    if (const cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::Begin("OutputDevice.Native.__getScreenInfo(I64_NativeOutputDeviceRef)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;

        if (const cli::OutputDevice::ScreenInfo* const pcli_ScreenInfo = new cli::OutputDevice::ScreenInfo(pcli_OutputDevice->GetScreenInfo()))
        {
            NativeObject::CreateFromNative(*pcli_ScreenInfo);
            i64_ScreenInfoRef = NativeObject::GetNativeRef(*pcli_ScreenInfo);
        }

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_OutputDevice) << NativeTraces::EndInt64("OutputDevice.Native.__getScreenInfo()", i64_ScreenInfoRef) << cli::endl;
    }
    return i64_ScreenInfoRef;
}

extern "C" JNIEXPORT jboolean JNICALL Java_cli_OutputDevice__1_1Native_1_1wouldOutput(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeOutputDeviceRef, jlong I64_NativeOutputDevice2Ref)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    // Do not trace! for consistency reasons.
    bool b_Res = false;
    if (const cli::OutputDevice* const pcli_OutputDevice1 = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        if (const cli::OutputDevice* const pcli_OutputDevice2 = NativeObject::GetNativeObject<const cli::OutputDevice*>(I64_NativeOutputDevice2Ref))
        {
            b_Res = pcli_OutputDevice1->WouldOutput(*pcli_OutputDevice2);
        }
    }
    return b_Res;
}


// OutputDevice.Java implementation.

extern "C" JNIEXPORT jlong JNICALL Java_cli_OutputDevice__1_1Java_1_1Java(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jstring PJ_DbgName)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("OutputDevice.Java.__Java(PJ_DbgName)") << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamStr("PJ_DbgName", NativeExec::Java2Native(PJ_DbgName).c_str()) << cli::endl;

    NativeObject::REF i64_OutputDeviceRef = 0;
    if (cli::OutputDevice* const pcli_OutputDevice = new NativeDevice<cli::OutputDevice>(NativeExec::Java2Native(PJ_DbgName).c_str()))
    {
        NativeObject::Use(*pcli_OutputDevice);
        i64_OutputDeviceRef = NativeObject::GetNativeRef(*pcli_OutputDevice);
    }

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("OutputDevice.Java.__Java()", i64_OutputDeviceRef) << cli::endl;
    return i64_OutputDeviceRef;
}


// OutputDevice static methods implementation.

extern "C" JNIEXPORT jlong JNICALL Java_cli_OutputDevice__1_1getNullDevice(
        JNIEnv* PJ_Env, jclass PJ_Class)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("OutputDevice.__getNullDevice()") << cli::endl;

    static NativeObject::REF i64_NullDeviceRef = 0;
    if (i64_NullDeviceRef == 0)
    {
        const cli::OutputDevice& cli_NullDevice = cli::OutputDevice::GetNullDevice();
        i64_NullDeviceRef = NativeObject::GetNativeRef(cli_NullDevice);

        // Note: Java should call this JNI interface once only for OutputDevice.m_cliNullDevice static member initialization.
        // Ensure one more token there so that System.runFinalizersOnExit(true) does not cause a crash on the Java OutputDevice object finalization.
        const_cast<cli::OutputDevice&>(cli_NullDevice).UseInstance(__CALL_INFO__);
    }

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("OutputDevice.__getNullDevice()", i64_NullDeviceRef) << cli::endl;
    return i64_NullDeviceRef;
}

extern "C" JNIEXPORT jlong JNICALL Java_cli_OutputDevice__1_1getStdOut(
        JNIEnv* PJ_Env, jclass PJ_Class)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("OutputDevice.__getStdOut()") << cli::endl;

    static NativeObject::REF i64_StdOutDeviceRef = 0;
    if (i64_StdOutDeviceRef == 0)
    {
        const cli::OutputDevice& cli_StdOutDevice = cli::OutputDevice::GetStdOut();
        i64_StdOutDeviceRef = NativeObject::GetNativeRef(cli_StdOutDevice);

        // Note: Java should call this JNI interface once only for OutputDevice.m_cliStdOut static member initialization.
        // Ensure one more token there so that System.runFinalizersOnExit(true) does not cause a crash on the Java OutputDevice object finalization.
        const_cast<cli::OutputDevice&>(cli_StdOutDevice).UseInstance(__CALL_INFO__);
    }

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("OutputDevice.__getStdOut()", i64_StdOutDeviceRef) << cli::endl;
    return i64_StdOutDeviceRef;
}

extern "C" JNIEXPORT jlong JNICALL Java_cli_OutputDevice__1_1getStdErr(
        JNIEnv* PJ_Env, jclass PJ_Class)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("OutputDevice.__getStdErr()") << cli::endl;

    static NativeObject::REF i64_StdErrDeviceRef = 0;
    if (i64_StdErrDeviceRef == 0)
    {
        const cli::OutputDevice& cli_StdErrDevice = cli::OutputDevice::GetStdErr();
        i64_StdErrDeviceRef = NativeObject::GetNativeRef(cli_StdErrDevice);

        // Note: Java should call this JNI interface once only for OutputDevice.m_cliStdErr static member initialization.
        // Ensure one more token there so that System.runFinalizersOnExit(true) does not cause a crash on the Java OutputDevice object finalization.
        const_cast<cli::OutputDevice&>(cli_StdErrDevice).UseInstance(__CALL_INFO__);
    }

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("OutputDevice.__getStdErr()", i64_StdErrDeviceRef) << cli::endl;
    return i64_StdErrDeviceRef;
}
