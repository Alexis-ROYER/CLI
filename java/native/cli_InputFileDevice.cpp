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

#include "cli/file_device.h"

#include "cli_InputFileDevice.h"

#include "NativeObject.h"
#include "NativeExec.h"
#include "NativeTraces.h"


extern "C" JNIEXPORT jlong JNICALL Java_cli_InputFileDevice__1_1InputFileDevice(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jstring PJ_InputFileName, jlong I64_NativeOutputDeviceRef)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::Begin("InputFileDevice.__InputFileDevice(PJ_InputFileName, I64_NativeOutputDeviceRef)") << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamStr("PJ_InputFileName", NativeExec::Java2Native(PJ_InputFileName).c_str()) << cli::endl;
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::ParamInt64("I64_NativeOutputDeviceRef", I64_NativeOutputDeviceRef) << cli::endl;
    NativeObject::REF i64_FileDeviceRef = 0;
    if (cli::OutputDevice* const pcli_OutputDevice = NativeObject::GetNativeObject<cli::OutputDevice*>(I64_NativeOutputDeviceRef))
    {
        if (cli::InputFileDevice* const pcli_FileDevice = new cli::InputFileDevice(NativeExec::Java2Native(PJ_InputFileName).c_str(), *pcli_OutputDevice, true))
        {
            NativeObject::Use(*pcli_FileDevice);
            i64_FileDeviceRef = NativeObject::GetNativeRef(*pcli_FileDevice);
        }
    }
    cli::GetTraces().Trace(TRACE_JNI) << NativeTraces::EndInt64("InputFileDevice.__InputFileDevice()", i64_FileDeviceRef) << cli::endl;
    return i64_FileDeviceRef;
}

extern "C" JNIEXPORT void JNICALL Java_cli_InputFileDevice__1_1enableSpecialCharacters(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jlong I64_NativeFileDeviceRef, jboolean B_EnableSpecialCharacters)
{
    NativeExec::GetInstance().RegJNIEnv(PJ_Env);

    if (cli::InputFileDevice* const pcli_FileDevice = NativeObject::GetNativeObject<cli::InputFileDevice*>(I64_NativeFileDeviceRef))
    {
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_FileDevice) << NativeTraces::Begin("InputFileDevice.__enableSpecialCharacters(I64_NativeFileDeviceRef, B_EnableSpecialCharacters)") << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_FileDevice) << NativeTraces::ParamInt64("I64_NativeFileDeviceRef", I64_NativeFileDeviceRef) << cli::endl;
        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_FileDevice) << NativeTraces::ParamBool("B_EnableSpecialCharacters", B_EnableSpecialCharacters) << cli::endl;

        pcli_FileDevice->EnableSpecialCharacters(B_EnableSpecialCharacters);

        cli::GetTraces().SafeTrace(TRACE_JNI, *pcli_FileDevice) << NativeTraces::EndVoid("InputFileDevice.__enableSpecialCharacters()") << cli::endl;
    }
}
