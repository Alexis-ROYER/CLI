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


#include "cli/pch.h"

#include <stdio.h>

#include "cli/io_device.h"
#include "cli/cli.h"
#include "cli/traces.h"
#include "cli/assert.h"
#include "constraints.h"

CLI_NS_USE(cli)


#ifndef CLI_NO_NAMESPACE
const IOEndl cli::endl;
#else
const IOEndl endl;
#endif

static const TraceClass TRACE_IO_DEVICE_INSTANCES("CLI_IO_DEVICE_INSTANCES", Help()
    .AddHelp(Help::LANG_EN, "IO device instance management")
    .AddHelp(Help::LANG_FR, "Gestion des intances de p�riph�riques d'entr�e/sortie"));
static const TraceClass TRACE_IO_DEVICE_OPENING("CLI_IO_DEVICE_OPENING", Help()
    .AddHelp(Help::LANG_EN, "IO device opening management")
    .AddHelp(Help::LANG_FR, "Gestion de l'ouverture des p�riph�riques d'entr�e/sortie"));


OutputDevice::OutputDevice(
        const char* const STR_DbgName,
        const char* const STR_Endl,
        const bool B_AutoDelete)
  : m_strDbgName(MAX_DEVICE_NAME_LENGTH, STR_DbgName),
    m_strEndl(MAX_WORD_LENGTH, STR_Endl),
    m_iInstanceLock(B_AutoDelete ? 0 : 1), m_iOpenLock(0)
{
    // Please, no traces in constructor for consistency reasons.
}

OutputDevice::~OutputDevice(void)
{
}

const int OutputDevice::UseInstance(const CallInfo& CLI_CallInfo)
{
    GetTraces().Trace(TRACE_IO_DEVICE_INSTANCES)
        << "One more user for instance " << m_strDbgName << "/" << this << ", "
        << "user count: " << m_iInstanceLock << " -> " << m_iInstanceLock + 1 << ", "
        << "from " << CLI_CallInfo.GetFunction() << " "
        << "at " << CLI_CallInfo.GetFile() << ":" << CLI_CallInfo.GetLine() << endl;
    m_iInstanceLock ++;
    return m_iInstanceLock;
}

const int OutputDevice::FreeInstance(const CallInfo& CLI_CallInfo)
{
    GetTraces().Trace(TRACE_IO_DEVICE_INSTANCES)
        << "One less user for instance " << m_strDbgName << "/" << this << ", "
        << "user count: " << m_iInstanceLock << " -> " << m_iInstanceLock - 1 << ", "
        << "from " << CLI_CallInfo.GetFunction() << " "
        << "at " << CLI_CallInfo.GetFile() << ":" << CLI_CallInfo.GetLine() << endl;
    if (m_iInstanceLock == 1)
    {
        GetTraces().Trace(TRACE_IO_DEVICE_INSTANCES)
            << "Deleting the device " << m_strDbgName << "/" << this << endl;
        delete this;
        return 0;
    }
    else
    {
        m_iInstanceLock --;
        CLI_ASSERT(m_iInstanceLock > 0);
        return m_iInstanceLock;
    }
}

const int OutputDevice::GetInstanceUsers(void) const
{
    return m_iInstanceLock;
}

const bool OutputDevice::OpenUp(const CallInfo& CLI_CallInfo)
{
    GetTraces().Trace(TRACE_IO_DEVICE_OPENING)
        << "One more user for instance " << m_strDbgName << "/" << this << ", "
        << "user count: " << m_iOpenLock << " -> " << m_iOpenLock + 1 << ", "
        << "from " << CLI_CallInfo.GetFunction() << " "
        << "at " << CLI_CallInfo.GetFile() << ":" << CLI_CallInfo.GetLine() << endl;

    m_iOpenLock ++;

    if (m_iOpenLock == 1)
    {
        GetTraces().Trace(TRACE_IO_DEVICE_OPENING)
            << "Opening the device " << m_strDbgName << "/" << this << endl;
        if (! OpenDevice())
        {
            return false;
        }
    }

    return true;
}

const bool OutputDevice::CloseDown(const CallInfo& CLI_CallInfo)
{
    bool b_Res = true;

    if (m_iOpenLock > 0)
    {
        GetTraces().Trace(TRACE_IO_DEVICE_OPENING)
            << "One less user for instance " << m_strDbgName << "/" << this << ", "
            << "user count: " << m_iOpenLock << " -> " << m_iOpenLock - 1 << ", "
            << "from " << CLI_CallInfo.GetFunction() << " "
            << "at " << CLI_CallInfo.GetFile() << ":" << CLI_CallInfo.GetLine() << endl;

        if (m_iOpenLock == 1)
        {
            GetTraces().Trace(TRACE_IO_DEVICE_OPENING)
                << "Closing the device " << m_strDbgName << "/" << this << endl;
            b_Res = CloseDevice();
        }

        m_iOpenLock --;
    }
    else
    {
        GetTraces().Trace(TRACE_IO_DEVICE_OPENING)
            << "No more closing down for instance " << m_strDbgName << "/" << this << ", "
            << "user count = " << m_iOpenLock << ", "
            << "from " << CLI_CallInfo.GetFunction() << " "
            << "at " << CLI_CallInfo.GetFile() << ":" << CLI_CallInfo.GetLine() << endl;
    }

    return b_Res;
}

const int OutputDevice::GetOpenUsers(void) const
{
    return m_iOpenLock;
}

const OutputDevice& OutputDevice::operator <<(const tk::String& STR_Out) const
{
    PutString(STR_Out);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const char* const STR_Out) const
{
    if (STR_Out != NULL)
    {
        PutString(STR_Out);
    }
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const unsigned char UC_Out) const
{
    return this->operator<<((unsigned int) UC_Out);
}

const OutputDevice& OutputDevice::operator <<(const char C_Out) const
{
    char arc_String[] = { C_Out, '\0' };
    PutString(arc_String);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const short S_Out) const
{
    return this->operator<<((int) S_Out);
}

const OutputDevice& OutputDevice::operator <<(const unsigned short US_Out) const
{
    return this->operator<<((unsigned int) US_Out);
}

const OutputDevice& OutputDevice::operator <<(const long L_Out) const
{
    return this->operator <<((int) L_Out);
}

const OutputDevice& OutputDevice::operator <<(const unsigned long UL_Out) const
{
    return this->operator <<((unsigned int) UL_Out);
}

const OutputDevice& OutputDevice::operator <<(const int I_Out) const
{
    char str_Out[128];
    snprintf(str_Out, sizeof(str_Out), "%d", I_Out);
    PutString(str_Out);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const unsigned int UI_Out) const
{
    char str_Out[128];
    snprintf(str_Out, sizeof(str_Out), "%u", UI_Out);
    PutString(str_Out);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const float F_Out) const
{
    return this->operator <<((double) F_Out);
}

const OutputDevice& OutputDevice::operator <<(const double D_Out) const
{
    char str_Out[128];
    snprintf(str_Out, sizeof(str_Out), "%f", D_Out);
    PutString(str_Out);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(void* const PV_Out) const
{
    char str_Out[128];
    snprintf(str_Out, sizeof(str_Out), "0x%08x", (unsigned int) PV_Out);
    PutString(str_Out);
    return *this;
}

const OutputDevice& OutputDevice::operator <<(const IOEndl& CLI_IOEndl) const
{
    PutString(m_strEndl);
    return *this;
}

OutputDevice& OutputDevice::GetNullDevice(void)
{
    class NullDevice : public OutputDevice
    {
    public:
        NullDevice(void) : OutputDevice("null", "", false) {}
        virtual ~NullDevice(void) {}

    protected:
        virtual const bool OpenDevice(void) { return true; }
        virtual const bool CloseDevice(void) { return true; }
    public:
        virtual void PutString(const char* const STR_Out) const {}
        virtual void Beep(void) const {}
    };

    static NullDevice cli_Null;
    return cli_Null;
}

OutputDevice& OutputDevice::GetStdOut(void)
{
    class StdOutDevice : public OutputDevice
    {
    public:
        StdOutDevice(void) : OutputDevice("stdout", "\n", false) {}
        virtual ~StdOutDevice(void) {}

    protected:
        virtual const bool OpenDevice(void) { return true; }
        virtual const bool CloseDevice(void) { return true; }
    public:
        virtual void PutString(const char* const STR_Out) const { fprintf(stdout, "%s", STR_Out); }
        virtual void Beep(void) const {}
    };

    static StdOutDevice cli_StdOut;
    return cli_StdOut;
}

OutputDevice& OutputDevice::GetStdErr(void)
{
    class StdErrDevice : public OutputDevice
    {
    public:
        StdErrDevice(void) : OutputDevice("stderr", "\n", false) {}
        virtual ~StdErrDevice(void) {}

    protected:
        virtual const bool OpenDevice(void) { return true; }
        virtual const bool CloseDevice(void) { return true; }
    public:
        virtual void PutString(const char* const STR_Out) const { fprintf(stderr, "%s", STR_Out); }
        virtual void Beep(void) const {}
    };

    static StdErrDevice cli_StdErr;
    return cli_StdErr;
}


IODevice::IODevice(
        const char* const STR_DbgName,
        const char* const STR_Endl,
        const bool B_AutoDelete)
  : OutputDevice(STR_DbgName, STR_Endl, B_AutoDelete)
{
}

IODevice::~IODevice(void)
{
}

IODevice& IODevice::GetNullDevice(void)
{
    class NullDevice : public IODevice
    {
    public:
        NullDevice(void) : IODevice("null", "", false) {}
        virtual ~NullDevice(void) {}

    protected:
        virtual const bool OpenDevice(void) { return true; }
        virtual const bool CloseDevice(void) { return true; }
    public:
        virtual void PutString(const char* const STR_Out) const {}
        virtual void Beep(void) const {}
        virtual const KEY GetKey(void) const { return NULL_KEY; }
    };

    static NullDevice cli_Null;
    return cli_Null;
}

IODevice& IODevice::GetStdIn(void)
{
    class StdInDevice : public IODevice
    {
    public:
        StdInDevice(void) : IODevice("stdin", "", false) {
        }
        virtual ~StdInDevice(void) {
        }

    protected:
        virtual const bool OpenDevice(void) {
            OutputDevice::GetStdOut().UseInstance(__CALL_INFO__);
            return OutputDevice::GetStdOut().OpenUp(__CALL_INFO__);
        }
        virtual const bool CloseDevice(void) {
            bool b_Res = OutputDevice::GetStdOut().CloseDown(__CALL_INFO__);
            OutputDevice::GetStdOut().FreeInstance(__CALL_INFO__);
            return b_Res;
        }
    public:
        virtual void PutString(const char* const STR_Out) const {
            OutputDevice::GetStdOut().PutString(STR_Out);
        }
        virtual void Beep(void) const {
            OutputDevice::GetStdOut().Beep();
        }
        virtual const KEY GetKey(void) const {
            const char c_Char = (char) getchar();
                return IODevice::GetKey(c_Char);
            }
    };

    static StdInDevice cli_StdIn;
    return cli_StdIn;
}

const KEY IODevice::GetKey(const int I_Char) const
{
    switch (I_Char)
    {
    case 3:             return BREAK;
    case 4:             return LOGOUT;
    case 10: case 13:   return ENTER;
    case 27:            return ESCAPE;
    case 127:           return BACKSPACE;
    case 1001:          return KEY_UP;
    case 1002:          return KEY_DOWN;
    case 1005:          return PAGE_UP;
    case 1006:          return PAGE_DOWN;

    case ' ':           return SPACE;
    case '\t':          return TAB;

    case '0':   return KEY_0;
    case '1':   return KEY_1;
    case '2':   return KEY_2;
    case '3':   return KEY_3;
    case '4':   return KEY_4;
    case '5':   return KEY_5;
    case '6':   return KEY_6;
    case '7':   return KEY_7;
    case '8':   return KEY_8;
    case '9':   return KEY_9;

    case 'a':   return KEY_a;
    case 'b':   return KEY_b;
    case 'c':   return KEY_c;
    case 'd':   return KEY_d;
    case 'e':   return KEY_e;
    case 'f':   return KEY_f;
    case 'g':   return KEY_g;
    case 'h':   return KEY_h;
    case 'i':   return KEY_i;
    case 'j':   return KEY_j;
    case 'k':   return KEY_k;
    case 'l':   return KEY_l;
    case 'm':   return KEY_m;
    case 'n':   return KEY_n;
    case 'o':   return KEY_o;
    case 'p':   return KEY_p;
    case 'q':   return KEY_q;
    case 'r':   return KEY_r;
    case 's':   return KEY_s;
    case 't':   return KEY_t;
    case 'u':   return KEY_u;
    case 'v':   return KEY_v;
    case 'w':   return KEY_w;
    case 'x':   return KEY_x;
    case 'y':   return KEY_y;
    case 'z':   return KEY_z;

    case 'A':   return KEY_A;
    case 'B':   return KEY_B;
    case 'C':   return KEY_C;
    case 'D':   return KEY_D;
    case 'E':   return KEY_E;
    case 'F':   return KEY_F;
    case 'G':   return KEY_G;
    case 'H':   return KEY_H;
    case 'I':   return KEY_I;
    case 'J':   return KEY_J;
    case 'K':   return KEY_K;
    case 'L':   return KEY_L;
    case 'M':   return KEY_M;
    case 'N':   return KEY_N;
    case 'O':   return KEY_O;
    case 'P':   return KEY_P;
    case 'Q':   return KEY_Q;
    case 'R':   return KEY_R;
    case 'S':   return KEY_S;
    case 'T':   return KEY_T;
    case 'U':   return KEY_U;
    case 'V':   return KEY_V;
    case 'W':   return KEY_W;
    case 'X':   return KEY_X;
    case 'Y':   return KEY_Y;
    case 'Z':   return KEY_Z;

    case '+':   return PLUS;
    case '-':   return MINUS;
    case '*':   return STAR;
    case '/':   return SLASH;
    case '<':   return LOWER_THAN;
    case '>':   return GREATER_THAN;
    case '=':   return EQUAL;
    case '%':   return PERCENT;

    case '_':   return UNDERSCORE;
    case '@':   return AROBASE;
    case '#':   return SHARP;
    case '&':   return AMPERCENT;
    case '$':   return DOLLAR;
    case '\\':  return BACKSLASH;
    case '|':   return PIPE;

    case '?':   return QUESTION;
    case '!':   return EXCLAMATION;
    case ':':   return COLUMN;
    case '.':   return DOT;
    case ',':   return COMA;
    case ';':   return SEMI_COLUMN;
    case '\'':  return QUOTE;
    case '"':   return DOUBLE_QUOTE;

    case '(':   return OPENING_BRACE;
    case ')':   return CLOSING_BRACE;
    case '{':   return OPENING_CURLY_BRACE;
    case '}':   return CLOSING_CURLY_BRACE;
    case '[':   return OPENING_BRACKET;
    case ']':   return CLOSING_BRACKET;

    default:
        // Unrecognized character.
        return NULL_KEY;
    }
}
