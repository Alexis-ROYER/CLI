/*
    This file is part of the CLI library.  The CLI library aims to provide
    facilities in making text-based user interfaces.
    Copyright (C) 2006-2007 Alexis Royer.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <cli/io_mux.h>
#include <cli/shell.h>
#include "consistency.h"

using namespace cli;


IOMux::IOMux(const bool B_AutoDelete)
  : IODevice("mux", "\n", B_AutoDelete),
    m_bIOLocked(false)
{
    EnsureCommonDevices();
    EnsureTraces();

    memset(m_arpcliOutputs, '\0', sizeof(m_arpcliOutputs));
}

IOMux::~IOMux(void)
{
    for (int i = 0; i < STREAM_TYPES_COUNT; i++)
    {
        SetOutput((STREAM_TYPE) i, NULL);
    }
    ResetInputList();
}

const bool IOMux::OpenDevice(void)
{
    bool b_Res = true;
    IODevice* pcli_Input = NULL;

    // Input.
    if ((! CheckInput()) || (m_qInputs.empty()))
    {
        b_Res = false;
    }
    else
    {
        if ((pcli_Input = m_qInputs.front()))
        {
            if (! pcli_Input->OpenUp(__CALL_INFO__))
            {
                b_Res = false;
            }
        }
        else
        {
            b_Res = false;
        }
    }

    // Outputs.
    for (int i = 0; i < STREAM_TYPES_COUNT; i++)
    {
        // Select default output if none is set.
        if (m_arpcliOutputs[i] == NULL)
        {
            if (pcli_Input != NULL)
            {
                m_arpcliOutputs[i] = pcli_Input;
            }
            else
            {
                m_arpcliOutputs[i] = & OutputDevice::GetNullDevice();
            }
            m_arpcliOutputs[i]->UseInstance(__CALL_INFO__);
        }

        // Open up the output device.
        if (m_arpcliOutputs[i] != NULL)
        {
            if (! m_arpcliOutputs[i]->OpenUp(__CALL_INFO__))
            {
                b_Res = false;
            }
        }
    }

    if (! b_Res)
    {
        CloseDevice();
    }
    return b_Res;
}

const bool IOMux::CloseDevice(void)
{
    bool b_Res = true;

    // Outputs.
    for (int i = 0; i < STREAM_TYPES_COUNT; i++)
    {
        if (m_arpcliOutputs[i] != NULL)
        {
            if (! m_arpcliOutputs[i]->CloseDown(__CALL_INFO__))
            {
                b_Res = false;
            }
        }
    }

    // Inputs.
    while (! m_qInputs.empty())
    {
        if (! ReleaseFirstInputDevice())
        {
            b_Res = false;
        }
    }

    return b_Res;
}

void IOMux::PutString(const std::string& STR_Out) const
{
    //! @warning This method should not be called. However, we redirect the call to output stream.
    if ((m_arpcliOutputs[OUTPUT_STREAM] != NULL)
        // Protection against infinite loop.
        && (! m_bIOLocked))
    {
        m_bIOLocked = true;
        m_arpcliOutputs[OUTPUT_STREAM]->PutString(STR_Out);
        m_bIOLocked = false;
    }
}

void IOMux::Beep(void) const
{
    //! @warning This method should not be called. However, we redirect the call to m_tOutput.
    if ((m_arpcliOutputs[OUTPUT_STREAM] != NULL)
        // Protection against infinite loop.
        && (! m_bIOLocked))
    {
        m_bIOLocked = true;
        m_arpcliOutputs[OUTPUT_STREAM]->Beep();
        m_bIOLocked = false;
    }
}

const KEY IOMux::GetKey(void) const
{
    if (CheckInput() && (! m_qInputs.empty()))
    {
        if (IODevice* const pcli_Input = m_qInputs.front())
        {
            // Protection against infinite loop.
            if (! m_bIOLocked)
            {
                m_bIOLocked = true;
                KEY e_Key = pcli_Input->GetKey();
                m_bIOLocked = false;

                if (e_Key != NULL_KEY)
                {
                    return e_Key;
                }
                else if (const_cast<IOMux*>(this)->NextInput())
                {
                    return GetKey();
                }
            }
        }
    }

    return cli::NULL_KEY;
}

const OutputDevice& IOMux::GetOutput(const STREAM_TYPE E_StreamType) const
{
    if ((E_StreamType >= 0) && (E_StreamType < STREAM_TYPES_COUNT)
        && (m_arpcliOutputs[E_StreamType] != NULL))
    {
        return *m_arpcliOutputs[E_StreamType];
    }
    else
    {
        return OutputDevice::GetNullDevice();
    }
}

const bool IOMux::SetOutput(const STREAM_TYPE E_StreamType, OutputDevice* const PCLI_Stream)
{
    // Free previous device.
    if (! ReleaseOutputDevice(E_StreamType, true))
    {
        return false;
    }

    // Store next device reference.
    m_arpcliOutputs[E_StreamType] = PCLI_Stream;
    // Lock the device instance.
    if (PCLI_Stream != NULL)
    {
        PCLI_Stream->UseInstance(__CALL_INFO__);
    }

    // Possibly open the device.
    if ((GetOpenUsers() > 0)
        && (m_arpcliOutputs[E_StreamType] != NULL)
        // Protection against misfunctionning.
        && (m_arpcliOutputs[E_StreamType] != this))
    {
        if (! m_arpcliOutputs[E_StreamType]->OpenUp(__CALL_INFO__))
        {
            return false;
        }
    }

    return true;
}

const IODevice* const IOMux::GetInput(void) const
{
    if (! m_qInputs.empty())
    {
        return m_qInputs.front();
    }

    return NULL;
}

const bool IOMux::AddInput(IODevice* const PCLI_Input)
{
    if (PCLI_Input != NULL)
    {
        m_qInputs.push_back(PCLI_Input);
        PCLI_Input->UseInstance(__CALL_INFO__);
    }

    return true;
}

const bool IOMux::NextInput(void)
{
    // Terminate head device.
    if (! m_qInputs.empty())
    {
        if (! ReleaseFirstInputDevice())
        {
            return false;
        }
    }

    // Prepare next device.
    if (CheckInput() && (! m_qInputs.empty()))
    {
        if (IODevice* const pcli_Input = m_qInputs.front())
        {
            if (GetOpenUsers() > 0)
            {
                if (! pcli_Input->OpenUp(__CALL_INFO__))
                {
                    // Open failure.
                    return false;
                }
            }

            // Successful return.
            return true;
        }
    }

    // Default return indicates a failure.
    return false;
}

const bool IOMux::ResetInputList(void)
{
    bool b_Res = true;

    while (! m_qInputs.empty())
    {
        if (! ReleaseFirstInputDevice())
        {
            b_Res = false;
        }
    }

    return b_Res;
}

IODevice* const IOMux::CreateInputDevice(void)
{
    return NULL;
}

const bool IOMux::CheckInput(void) const
{
    if (m_qInputs.empty())
    {
        // Input needed.
        if (IODevice* const pcli_Input = const_cast<IOMux*>(this)->CreateInputDevice())
        {
            const_cast<IOMux*>(this)->AddInput(pcli_Input);
            if (GetOpenUsers() > 0)
            {
                // Input should be opened.
                if (! pcli_Input->OpenUp(__CALL_INFO__))
                {
                    // Open failure.
                    return false;
                }
            }
        }
        else if (m_qInputs.empty())
        {
            // No more input.
            return false;
        }
    }

    // Successful return.
    return true;
}

const bool IOMux::ReleaseFirstInputDevice(void)
{
    if (! m_qInputs.empty())
    {
        bool b_Res = true;

        if (IODevice* const pcli_Input = m_qInputs.front())
        {
            if (GetOpenUsers() > 0)
            {
                // Close the device if needed.
                if (! pcli_Input->CloseDown(__CALL_INFO__))
                {
                    b_Res = false;
                }
            }
            // Free the device instance.
            pcli_Input->FreeInstance(__CALL_INFO__);
        }

        // Remove device reference.
        m_qInputs.pop_front();

        return b_Res;
    }
    else
    {
        return false;
    }
}

const bool IOMux::ReleaseOutputDevice(const STREAM_TYPE E_StreamType, const bool B_Delete)
{
    bool b_Res = true;

    if (m_arpcliOutputs[E_StreamType] != NULL)
    {
        if (GetOpenUsers() > 0)
        {
            // Close the device if needed.
            if (! m_arpcliOutputs[E_StreamType]->CloseDown(__CALL_INFO__))
            {
                b_Res = false;
            }
        }
        // Release the device instance.
        m_arpcliOutputs[E_StreamType]->FreeInstance(__CALL_INFO__);

        // Remove reference.
        m_arpcliOutputs[E_StreamType] = NULL;
    }

    return b_Res;
}