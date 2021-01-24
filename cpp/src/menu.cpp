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

#include <stdlib.h>

#include "cli/menu.h"
#include "cli/keyword.h"
#include "cli/endl.h"
#include "cli/shell.h"
#include "cli/io_device.h"
#include "cli/command_line.h"
#include "cli/help.h"

CLI_NS_USE(cli)


Menu::Menu(const char* const STR_Name, const Help& CLI_Help)
  : SyntaxNode(STR_Name, CLI_Help),
    m_pcliHelp(NULL), m_pcliExit(NULL), m_pcliQuit(NULL), m_pcliPwm(NULL)
{
}

Menu::~Menu(void)
{
}

const tk::String Menu::GetName(void) const
{
    return GetKeyword();
}

const Keyword& Menu::GetHelpNode(void) const
{
    return *m_pcliHelp;
}

const Keyword& Menu::GetExitNode(void) const
{
    return *m_pcliExit;
}

const Keyword& Menu::GetQuitNode(void) const
{
    return *m_pcliQuit;
}

const Keyword& Menu::GetPwmNode(void) const
{
    return *m_pcliPwm;
}

void Menu::SetCli(Cli& CLI_Cli)
{
    SyntaxNode::SetCli(CLI_Cli);
    {   Help cli_Help(Help()
            .AddHelp(Help::LANG_EN, "Get help")
            .AddHelp(Help::LANG_FR, "Obtenir de l'aide"));
        m_pcliHelp = dynamic_cast<Keyword*>(& AddElement(new Keyword("help", cli_Help)));
        m_pcliHelp->AddElement(new Endl(cli_Help)); }
    {   Help cli_Help(Help()
            .AddHelp(Help::LANG_EN, Help::Concat("Exit menu '", GetKeyword(), "'"))
            .AddHelp(Help::LANG_FR, Help::Concat("Sortir du menu '", GetKeyword(), "'")));
        m_pcliExit = dynamic_cast<Keyword*>(& AddElement(new Keyword("exit", cli_Help)));
        m_pcliExit->AddElement(new Endl(cli_Help)); }
    {   Help cli_Help(Help()
            .AddHelp(Help::LANG_EN, "Quit")
            .AddHelp(Help::LANG_FR, "Quitter"));
        m_pcliQuit = dynamic_cast<Keyword*>(& AddElement(new Keyword("quit", cli_Help)));
        m_pcliQuit->AddElement(new Endl(cli_Help)); }
    {   Help cli_Help(Help()
            .AddHelp(Help::LANG_EN, "Print Working Menu")
            .AddHelp(Help::LANG_FR, "Affichage du menu courant"));
        m_pcliPwm = dynamic_cast<Keyword*>(& AddElement(new Keyword("pwm", cli_Help)));
        m_pcliPwm->AddElement(new Endl(cli_Help)); }
}

const bool Menu::ExecuteReserved(const CommandLine& CLI_CommandLine) const
{
    CommandLineIterator it(CLI_CommandLine);

    if (! it.StepIt()) { return false; }
    else if (it == GetHelpNode())
    {
        if (! it.StepIt()) { return false; }
        if (dynamic_cast<const Endl*>(*it))
        {
            GetShell().DisplayHelp();
            return true;
        }
    }
    else if (it == GetExitNode())
    {
        if (! it.StepIt()) { return false; }
        if (dynamic_cast<const Endl*>(*it))
        {
            GetShell().ExitMenu();
            return true;
        }
    }
    else if (it == GetQuitNode())
    {
        if (! it.StepIt()) { return false; }
        if (dynamic_cast<const Endl*>(*it))
        {
            GetShell().Quit();
            return true;
        }
    }
    else if (it == GetPwmNode())
    {
        if (! it.StepIt()) { return false; }
        if (dynamic_cast<const Endl*>(*it))
        {
            GetShell().PrintWorkingMenu();
            return true;
        }
    }

    return false;
}

const bool Menu::Execute(const CommandLine& CLI_CommandLine) const
{
    const ResourceString cli_Error = ResourceString()
        .SetString(ResourceString::LANG_EN, "No execution defined for the current command line")
        .SetString(ResourceString::LANG_FR, "Pas d'ex�cution d�finie pour la ligne de commande");
    GetErrorStream() << cli_Error.GetString(GetShell().GetLang()) << endl;
    return true;
}

void Menu::OnExit(void) const
{
}


MenuRef::MenuRef(const Menu& CLI_Menu)
  : Element("", Help()),
    m_pcliMenu(& CLI_Menu)
{
}

MenuRef::~MenuRef(void)
{
}

const Menu& MenuRef::GetMenu(void) const
{
    return *m_pcliMenu;
}

