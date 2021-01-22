/*
    Copyright 2006 Alexis Royer

    This file is part of the CLI library.

    The CLI library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _CLI_CONSOLE_H_
#define _CLI_CONSOLE_H_

#include "cli_io_device.h"


class CcliConsole : public CcliIODevice
{
public:
    CcliConsole(void);
    virtual ~CcliConsole(void);

public:
    virtual bool OpenDevice(void);
    virtual bool CloseDevice(void);
    virtual int GetChar(void) const;

private:
    virtual void PutString(const std::string& STR_Out) const;
};

#endif // _CLI_CONSOLE_H_

