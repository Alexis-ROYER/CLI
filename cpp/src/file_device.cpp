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
#include <string.h>

#include "cli/file_device.h"
#include "cli/assert.h"
#include "consistency.h"
#include "constraints.h"

CLI_NS_USE(cli)


InputFileDevice::InputFileDevice(
        const char* const STR_FileName,
        OutputDevice& CLI_Output,
        const bool B_AutoDelete)
  : IODevice(tk::String::Concat(MAX_DEVICE_NAME_LENGTH, "input-file[", STR_FileName, "]"), "\n", B_AutoDelete),
    m_strFileName(MAX_FILE_PATH_LENGTH, STR_FileName), m_pfFile(NULL),
    m_cliOutput(CLI_Output),
    m_iCurrentLine(0), m_iCurrentColumn(0), m_iNextLine(1), m_iNextColumn(1)
{
    EnsureCommonDevices();

    m_cliOutput.UseInstance(__CALL_INFO__);
}

InputFileDevice::~InputFileDevice(void)
{
    m_cliOutput.FreeInstance(__CALL_INFO__);
}

const bool InputFileDevice::OpenDevice(void)
{
    CLI_ASSERT(& m_cliOutput != this);
    if (! m_cliOutput.OpenUp(__CALL_INFO__))
    {
        return false;
    }

    if (m_pfFile == NULL)
    {
        m_pfFile = fopen(m_strFileName, "r");
    }

    return (m_pfFile != NULL);
}

const bool InputFileDevice::CloseDevice(void)
{
    bool b_Res = true;

    if (m_pfFile != NULL)
    {
        if (fclose(m_pfFile) != 0)
        {
            b_Res = false;
        }
        m_pfFile = NULL;
    }

    if (! m_cliOutput.CloseDown(__CALL_INFO__))
    {
        b_Res = false;
    }

    return b_Res;
}

const KEY InputFileDevice::GetKey(void) const
{
    if (m_pfFile != NULL)
    {
        m_iCurrentLine = m_iNextLine;
        m_iCurrentColumn = m_iNextColumn;
        char c_Char = NULL_KEY;
        if (fread(& c_Char, sizeof(char), 1, m_pfFile) == 1)
        {
            if (c_Char == '\n')
            {
                m_iNextLine ++;
                m_iNextColumn = 1;
            }
            else
            {
                m_iNextColumn ++;
            }
            return IODevice::GetKey(c_Char);
        }
    }

    return NULL_KEY;
}

void InputFileDevice::PutString(const char* const STR_Out) const
{
    m_cliOutput.PutString(STR_Out);
}

void InputFileDevice::Beep(void) const
{
    m_cliOutput.Beep();
}

const tk::String InputFileDevice::GetFileName(void) const
{
    return m_strFileName;
}

const int InputFileDevice::GetCurrentLine(void) const
{
    return m_iCurrentLine;
}

const int InputFileDevice::GetCurrentColumn(void) const
{
    return m_iCurrentColumn;
}


OutputFileDevice::OutputFileDevice(const char* const STR_FileName, const bool B_AutoDelete)
  : OutputDevice(tk::String::Concat(MAX_DEVICE_NAME_LENGTH, "output-file[", STR_FileName, "]"), "\n", B_AutoDelete),
    m_strFileName(MAX_FILE_PATH_LENGTH, STR_FileName), m_pfFile(NULL)
{
}

OutputFileDevice::~OutputFileDevice(void)
{
}

const bool OutputFileDevice::OpenDevice(void)
{
    if (m_pfFile == NULL)
    {
        m_pfFile = fopen(m_strFileName, "w");
    }

    return (m_pfFile != NULL);
}

const bool OutputFileDevice::CloseDevice(void)
{
    bool b_Res = true;

    if (m_pfFile != NULL)
    {
        if (fclose(m_pfFile) != 0)
        {
            b_Res = false;
        }
        m_pfFile = NULL;
    }

    return b_Res;
}

void OutputFileDevice::PutString(const char* const STR_Out) const
{
    if (m_pfFile != NULL)
    {
        fwrite(STR_Out, sizeof(char), strlen(STR_Out), m_pfFile);
    }
}

void OutputFileDevice::Beep(void) const
{
}

const tk::String OutputFileDevice::GetFileName(void) const
{
    return m_strFileName;
}

