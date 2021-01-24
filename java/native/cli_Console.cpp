/*
    Copyright (c) 2006-2007, Alexis Royer

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
        * Neither the name of the CLI library project nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

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

#include <cli/console.h>

#include "cli_Console.h"

#include "NativeObject.h"
#include "NativeTraces.h"


extern "C" JNIEXPORT jint JNICALL Java_cli_Console__1_1Console(
        JNIEnv* PJ_Env, jclass PJ_Class)
{
    NativeTraces::TraceMethod("Console.__Console()");
    cli::Console* pcli_Console = NULL;
    if ((pcli_Console = new cli::Console(true)))
    {
        NativeObject::Use(pcli_Console);
    }
    NativeTraces::TraceReturn("Console.__Console()", "%d", (int) pcli_Console);
    return (jint) pcli_Console;
}

extern "C" JNIEXPORT void JNICALL Java_cli_Console__1_1finalize(
        JNIEnv* PJ_Env, jclass PJ_Class,
        jint I_NativeConsoleRef)
{
    NativeTraces::TraceMethod("Console.__finalize(I_NativeConsoleRef)");
    NativeTraces::TraceParam("I_NativeConsoleRef", "%d", I_NativeConsoleRef);
    if (const cli::Console* const pcli_Console = (const cli::Console*) I_NativeConsoleRef)
    {
        NativeObject::Free(pcli_Console);
    }
    NativeTraces::TraceReturn("Console.__finalize()");
}
