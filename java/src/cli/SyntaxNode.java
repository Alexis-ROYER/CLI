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

package cli;


/** A syntax node is an element which may be considered as a node in the decision tree defining the command lines. */
public class SyntaxNode extends Element {

    /** Constructor.
        @param I64_NativeRef Native instance reference. */
    protected SyntaxNode(long I64_NativeRef) {
        super(I64_NativeRef);
    }

    /** Adds a next element in the command lines decision tree after this node.
        @param CLI_Element Next element after this node.
        @return The element added. null if an error occurred. */
    public final Element addElement(Element CLI_Element) {
        Element cli_Element = CLI_Element;
        long i64_NativeElementRef = __addElement(this.getNativeRef(), CLI_Element.getNativeRef());
        if (i64_NativeElementRef != 0) {
            cli_Element = (Element) NativeObject.getObject(i64_NativeElementRef);
        }
        return cli_Element;
    }
    private static final native long __addElement(long I64_NativeSyntaxNodeRef, long I64_NativeElementRef);

}
