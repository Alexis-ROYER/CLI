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


//! @file
//! @author Alexis Royer
//! @brief SyntaxNode class definition.

#ifndef _CLI_SYNTAX_NODE_H_
#define _CLI_SYNTAX_NODE_H_

#include <cli/element.h>


namespace cli {

    // Forward declarations.
    class Help;


    //! @brief Syntax node elements.
    //!
    //! Syntax node elements are element that accepts child elements.
    //! They store a list of possible childs,
    //! and offer operations based on this list.
    class SyntaxNode : public Element
    {
    public:
        //! @brief Constructor.
        SyntaxNode(
            const std::string& STR_Keyword, //!< Keyword of the element.
            const Help& CLI_Help            //!< Corresponding help.
            );

        //! @brief Destructor.
        virtual ~SyntaxNode(void);

    public:
        //! @brief Possible element addition.
        Element& AddElement(
            Element* const PCLI_Element     //!< New element.
            );

        //! @brief Returns the list of child elements coresponding to a keyword
        //!         or the beginning of a keyword.
        virtual const bool FindElements(
            ElementList& CLI_ExactList,     //!< Exact matching keywords output list.
            ElementList& CLI_NearList,      //!< All matching keywords output list.
            const char* const STR_Keyword   //!< Keyword or beginning of a keyword.
                                            //!< NULL means no keyword begun.
            ) const;

    private:
        //! List of possible child elements.
        ElementMap m_cliElements;
    };

};

#endif // _CLI_SYNTAX_NODE_H_
