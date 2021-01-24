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


//! @file
//! @author Alexis Royer
//! @brief Cli class definition.

//! @mainpage
//! The CLI library allows you to easily define Command Line Interfaces.
//!
//! Within a single XML file, you define the tree of menus, keywords and parameters, and match them directly to some target language code.
//!
//! This documentation gives information about the implementation of this library for C++.
//! Here is a short introduction to quickly get the essential of it:
//!     - First of all, you might be interested in the Cli class, which defines a CLI structure.
//!     - Then have a look at the Shell and CommandLine classes. These classes implement CLI executions.
//!     - You might figure out at this point that the Shell class is based on the use of input/output devices.
//!       Different input/output devices are directly provided with this library:
//!         - console:                      Console
//!         - TCP:                          TelnetServer and TelnetConnection
//!         - files:                        InputFileDevice and OutputFileDevice
//!         - strings:                      SingleCommand and StringDevice
//!     - Eventually get back to the Menu class and find out how user code is executed through the handlers.
//!       It is also interesting at this point to have a look at the XSL transformation.
//!
//! Advanced users:
//!     - Interested in the traces management system? Have a look at Traces.
//!     - Want to define a specific input/output device? Inherit from IODevice.
//!     - Need to multiplex input and output devices? Maybe IOMux can help you.
//!     - Any question about thread-safe CLI termination? Please check the Shell::QuitThreadSafe method.
//!     - Mono-thread concerns? Try to implement MonoThreadDevice
//!     - Trying to integrate in an embedded context? The cli::CLI_NO_STL compiler directive is there for you.
//!       Also have a look at the various preprocessing constants described in preprocessing.h.

#ifndef _CLI_CLI_H_
#define _CLI_CLI_H_

#include "cli/namespace.h"
#include "cli/menu.h"
#include "cli/tk.h"


CLI_NS_BEGIN(cli)

    // Forward declarations
    class Cli;
    class Console;
    class Help;
    class ConfigMenu;
    class TracesMenu;


    //! @brief CLI definition class.
    //!
    //! An object of this class defines a CLI structure.
    //! Since a Cli object defines the main menu, it inherits from Menu.
    //! On the other hand, this class owns all sub-menus through the member m_vpcliMenus.
    //! Finally, since Menu inherits from SyntaxNode,
    //! it also owns a collection of possible Element objects
    //! that define the commands you can type in the first place.
    //!
    //! Since you should override the execution handler, this class should be inherited.
    //! That's the reason why the destructor is pure virtual.
    class Cli : public Menu
    {
    private:
        //! @brief No default constructor.
        Cli(void);
        //! @brief No copy constructor.
        Cli(const Cli&);

    public:
        //! @brief Constructor.
        Cli(
            const char* const STR_Name,     //!< Name of the CLI.
            const Help& CLI_Help            //!< Help object.
            );

        //! @brief Destructor.
        //!
        //! Pure virtual. Cli class is not final.
        virtual ~Cli(void) = 0;

    private:
        //! @brief No assignment operator.
        Cli& operator=(const Cli&);

    public:
        //! @brief CLI list type.
        typedef tk::Queue<const Cli*> List;

        //! @brief Retrieve CLI references from their names.
        //! @return The number of Cli instances found.
        static const int FindFromName(
            Cli::List& CLI_CliList,         //!< Output list.
            const char* const STR_RegExp    //!< Regular expression matching the searched CLI names.
            );

    public:
        //! @brief Menu addition.
        //! @return The menu just added.
        Menu& AddMenu(
            Menu* const PCLI_Menu       //!< New menu.
            );

    public:
        //! @brief Set the shell reference when executing.
        void SetShell(
            Shell& CLI_Shell    //!< Shell reference.
            ) const;
        //! @brief Returns the shell reference on execution.
        Shell& GetShell(void) const;

        //! @brief CLI reference setting.
        virtual void SetCli(Cli& CLI_Cli);
        //! @brief Reserved commands execution.
        virtual const bool ExecuteReserved(const CommandLine& CLI_CommandLine) const;
        //! @brief Handler on menu exit.
        virtual void OnExit(void) const;

    private:
        //! @brief Configuration menu access.
        ConfigMenu& GetConfigMenu(void);
        //! @brief Configuration menu access (read-only).
        const ConfigMenu& GetConfigMenu(void) const;
        //! @brief Configuration menu node access (read-only).
        const Keyword& GetConfigMenuNode(void) const;
    public:
        //! @brief Configuration menu enabling.
        //! @return false if the operation failed.
        const bool EnableConfigMenu(
            const bool B_Enable     //!< true for enabling, false otherwise.
            );

    private:
        #ifdef _DEBUG
        //! @brief Traces menu access.
        TracesMenu& GetTracesMenu(void);
        //! @brief Traces menu access (read-only).
        const TracesMenu& GetTracesMenu(void) const;
        //! @brief Configuration menu node access (read-only).
        const Keyword& GetTracesMenuNode(void) const;
        #endif

    private:
        //! Shell reference.
        mutable Shell* m_pcliShell;
        //! Owned menu collection.
        tk::Queue<const Menu*> m_qMenus;
        //! Configuration menu.
        ConfigMenu* m_pcliConfigMenu;
        //! Configuration menu node.
        Keyword* m_pcliConfigMenuNode;
        #ifdef _DEBUG
        //! Traces menu.
        TracesMenu* m_pcliTracesMenu;
        //! Traces menu node.
        Keyword* m_pcliTracesMenuNode;
        #endif
    };

CLI_NS_END(cli)

#endif // _CLI_CLI_H_

