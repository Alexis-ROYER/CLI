/*
    Copyright (c) 2006-2009, Alexis Royer

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

#include "cli/console.h"
#include "cli/traces.h"

//! @warning Include ncurses after cli.
#include <curses.h>

CLI_NS_USE(cli)


//! @brief Original ncurses escape delay.
static const int i_OriginalDelay = ESCDELAY;
//! @brief Ncurses device count.
static int i_NcursesDeviceCount = 0;


//! @brief ncurses console trace class singleton redirection.
#define CLI_NCURSES_CONSOLE GetNcursesConsoleTraceClass()
//! @brief ncurses console trace class singleton.
static const TraceClass& GetNcursesConsoleTraceClass(void)
{
    static const TraceClass cli_NcursesConsoleTraceClass("CLI_NCURSES_CONSOLE", Help()
        .AddHelp(Help::LANG_EN, "CLI ncurses console traces")
        .AddHelp(Help::LANG_FR, "Traces de la console ncurses du CLI"));
    return cli_NcursesConsoleTraceClass;
}

Console::Console(const bool B_AutoDelete)
  : IODevice("ncurses-console", B_AutoDelete),
    m_pData(NULL)
{
    // Does nothing but registers the appropriate trace classes.
    GetTraces().Trace(CLI_NCURSES_CONSOLE);
}

Console::~Console(void)
{
    Console::CloseDevice();
}

const bool Console::OpenDevice(void)
{
    if (m_pData == NULL)
    {
        // Configure ncurses

        // Regular ncurses configuration.
        WINDOW* const p_Window = initscr();
        raw(); // Use raw() instead of cbreak(), since we also want to trap the control character sequences.
        noecho();
        // Additional configuration.
        scrollok(p_Window, TRUE); // Enable scrolling.
        keypad(p_Window, TRUE); // Enable arrow keys.
        ESCDELAY = 0; // Change the escape delay to none instead of 1000 ms by default.

        m_pData = p_Window;

        i_NcursesDeviceCount ++;
    }

    if (m_pData == NULL)
    {
        m_cliLastError
            .SetString(ResourceString::LANG_EN, "ncurses configuration failed")
            .SetString(ResourceString::LANG_FR, "La configuration de ncurses a �chou�");
        return false;
    }
    else
    {
        return true;
    }
}

const bool Console::CloseDevice(void)
{
    if (m_pData != NULL)
    {
        m_pData = NULL;

        i_NcursesDeviceCount --;
        if (i_NcursesDeviceCount <= 0)
        {
            // Restore original escape delay.
            ESCDELAY = i_OriginalDelay;
        }

        endwin();
    }

    return true;
}

const KEY Console::GetKey(void) const
{
    // ncurses constants.
    static const int NC_KEY_UP = KEY_UP;
        #undef KEY_UP
    static const int NC_KEY_DOWN = KEY_DOWN;
        #undef KEY_DOWN
    static const int NC_KEY_LEFT = KEY_LEFT;
        #undef KEY_LEFT
    static const int NC_KEY_RIGHT = KEY_RIGHT;
        #undef KEY_RIGHT
    static const int NC_KEY_END = KEY_END;
        #undef KEY_END

    while (1)
    {
        const int i_Char = getch();
        GetTraces().Trace(CLI_NCURSES_CONSOLE) << "i_Char = " << i_Char << endl;
        switch (i_Char)
        {
        // Breakers.
        case 27:
            do {
                nodelay((WINDOW*) m_pData, TRUE);
                const int i_Char2 = getch();
                nodelay((WINDOW*) m_pData, FALSE);
                GetTraces().Trace(CLI_NCURSES_CONSOLE) << "i_Char2 = " << i_Char2 << endl;
                switch (i_Char2)
                {
                // Escape character.
                case ERR:   return cli::ESCAPE;
                // ALT sequences
                case 'c':   return cli::COPY;
                case 'x':   return cli::CUT;
                case 'v':   return cli::PASTE;
                case 'z':   return cli::UNDO;
                case 'y':   return cli::REDO;
                case NC_KEY_LEFT:   return PAGE_LEFT;
                case NC_KEY_RIGHT:  return PAGE_RIGHT;
                default:
                    // Unknown ALT sequence.
                    break;
                }
            } while(0);
            break;

        // Deletions.
        case KEY_BACKSPACE: return cli::BACKSPACE;
        case KEY_DC:        return cli::DELETE;
        case KEY_IC:        return cli::INSERT;

        // Movements
        case NC_KEY_UP:     return cli::KEY_UP;
        case KEY_PPAGE:     return cli::PAGE_UP;
        case NC_KEY_DOWN:   return cli::KEY_DOWN;
        case KEY_NPAGE:     return cli::PAGE_DOWN;
        case NC_KEY_LEFT:   return cli::KEY_LEFT;
        case NC_KEY_RIGHT:  return cli::KEY_RIGHT;
        case KEY_HOME:      return cli::KEY_BEGIN;
        case NC_KEY_END:    return cli::KEY_END;

        // Accentuated characters
        case 225:           return cli::KEY_aacute;
        case 224:           return cli::KEY_agrave;
        case 228:           return cli::KEY_auml;
        case 226:           return cli::KEY_acirc;
        case 231:           return cli::KEY_ccedil;
        case 233:           return cli::KEY_eacute;
        case 232:           return cli::KEY_egrave;
        case 235:           return cli::KEY_euml;
        case 234:           return cli::KEY_ecirc;
        case 237:           return cli::KEY_iacute;
        case 236:           return cli::KEY_igrave;
        case 239:           return cli::KEY_iuml;
        case 238:           return cli::KEY_icirc;
        case 243:           return cli::KEY_oacute;
        case 242:           return cli::KEY_ograve;
        case 246:           return cli::KEY_ouml;
        case 244:           return cli::KEY_ocirc;
        case 250:           return cli::KEY_uacute;
        case 249:           return cli::KEY_ugrave;
        case 252:           return cli::KEY_uuml;
        case 251:           return cli::KEY_ucirc;

        // Special characters.
        case 96:            return BACK_QUOTE;
        case 163:           return POUND;
        case 167:           return PARAGRAPH;
        case 176:           return DEGREE;
        case 178:           return SQUARE;
        case 181:           return MICRO;

        // Control sequences.
        case 1:             return cli::KEY_BEGIN;  // CTRL+A
        case 3:             return cli::BREAK;      // CTRL+C
        case 4:             return cli::LOGOUT;     // CTRL+D
        case 5:             return cli::KEY_END;    // CTRL+E
        case 12:            return cli::CLS;        // CTRL+L
        case 14:            return NEXT;            // CTRL+N
        case 16:            return PREVIOUS;        // CTRL+P
        case 25:            return cli::REDO;       // CTRL+Y
        case 407:           return cli::UNDO;       // CTRL+Z

        // Function keys.
        case 265:           return F1;
        case 266:           return F2;
        case 267:           return F3;
        case 268:           return F4;
        case 269:           return F5;
        case 270:           return F6;
        case 271:           return F7;
        case 272:           return F8;
        case 273:           return F9;
        case 274:           return F10;
        case 275:           return F11;
        case 276:           return F12;

        default:
            {
                // Call the base implementation.
                const KEY e_Char = IODevice::GetKey(i_Char);
                if (e_Char != NULL_KEY)
                {
                    return e_Char;
                }
            }
        }
    }
}

void Console::PutString(const char* const STR_Out) const
{
    char str_Char[2] = { '\0', '\0' };

    if (STR_Out != NULL)
    {
        const unsigned int ui_Len = strlen(STR_Out);
        for (unsigned int ui=0; ui<ui_Len; ui++)
        {
            str_Char[0] = STR_Out[ui];
            // Possible translation of certain character here...
            addstr(str_Char);
        }
        refresh();
    }
}

void Console::Beep(void) const
{
    beep();
}

void Console::CleanScreen(void) const
{
    erase();
}
