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

import java.util.Collection;


/** Command Line Interface class. */
public abstract class Cli extends Menu {

    static {
        // Loading 'cli' library.
        System.loadLibrary("cli");
    }

    /** Does nothing but loading the native library. */
    public static void load() {
        // Nothing to do: as far as this static method is called, the class will be loaded and the code above will be executed.
    }

    /** Constructor.
        @param J_Name   Name of the CLI.
        @param CLI_Help Help of the CLI. */
    public Cli(String J_Name, Help CLI_Help) {
        super(__Cli(J_Name, CLI_Help.getNativeRef()));
    }
    private static final native long __Cli(String J_Name, long I64_NativeHelpRef);

    /** Find from name.
        @param J_CliList    Output CLI list.
        @param J_RegExp     Regular expression describing the CLI name searched.
        @return Number of CLI instances found. */
    public static final int findFromName(Collection<Cli> J_CliList, String J_RegExp) {
        int i_Count = 0;
        long[] ari64_Refs = __findFromName(J_RegExp);
        for (int i=0; i<ari64_Refs.length; i++) {
            NativeObject cli_Cli = NativeObject.getObject(ari64_Refs[i]);
            if (cli_Cli != null) {
                J_CliList.add((Cli) cli_Cli);
                i_Count ++;
            }
        }
        return i_Count;
    }
    private static final native long[] __findFromName(String J_RegExp);

    /** Name accessor.
        @return CLI name. */
    public final String getName() {
        return __getName(this.getNativeRef());
    }
    private static final native String __getName(long I64_NativeRef);

    /** Menu addition.
        @param CLI_Menu Menu to add to the CLI.
        @return The menu itself. */
    public final Menu addMenu(Menu CLI_Menu) {
        if (__addMenu(this.getNativeRef(), CLI_Menu.getNativeRef())) {
            return CLI_Menu;
        }
        return null;
    }
    private static final native boolean __addMenu(long I64_NativeCliRef, long I64_NativeMenuRef);

    /** Menu retrieval.
        @param J_MenuName Menu name.
        @return The menu identified by the given name, null if not found. */
    public final Menu getMenu(String J_MenuName) {
        if (J_MenuName != null) {
            long i64_MenuRef = __getMenu(this.getNativeRef(), J_MenuName);
            NativeObject cli_Menu = NativeObject.getObject(i64_MenuRef);
            if ((cli_Menu != null) && (cli_Menu instanceof Menu)) {
                return (Menu) cli_Menu;
            }
        }

        return null;
    }
    private static final native long __getMenu(long I64_NativeCliRef, String J_MenuName);

    /** Comment line pattern addition.
        @param J_Start Comment line starter pattern.
        @return true if the comment line pattern has been successfully added, false otherwise. */
    public final boolean addCommentLinePattern(String J_Start) {
        return __addCommentLinePattern(this.getNativeRef(), J_Start);
    }
    private static final native boolean __addCommentLinePattern(long I64_NativeCliRef, String J_Start);

    /** Comment line pattern removal.
        @param J_Start Comment line starter pattern.
        @return true if the comment line pattern has been successfully removed, false otherwise. */
    final boolean removeCommentLinePattern(String J_Start) {
        return __removeCommentLinePattern(this.getNativeRef(), J_Start);
    }
    private static final native boolean __removeCommentLinePattern(long I64_NativeCliRef, String J_Start);

    /** Handler called when an error occurs.
        This method may be overridden by final menu classes.
        @param location Location of the error.
        @param message Message of the error.
        @return true if the error can be displayed by the shell, false if it should not be displayed. */
    public boolean onError(ResourceString location, ResourceString message) {
        return true;
    }
    private final boolean __onError(long I64_NativeLocationRef, long I64_NativeErrorMessageRef) {
        Traces.trace(NativeTraces.CLASS, NativeTraces.begin("Menu.__onError()"));
        boolean b_Res = true;
        ResourceString cli_Location = (ResourceString) NativeObject.getObject(I64_NativeLocationRef);
        ResourceString cli_ErrorMessage = (ResourceString) NativeObject.getObject(I64_NativeErrorMessageRef);
        if ((cli_Location != null) && (cli_ErrorMessage != null)) {
            b_Res = onError(cli_Location, cli_ErrorMessage);
        }
        Traces.trace(NativeTraces.CLASS, NativeTraces.end("Menu.__onError()", new Boolean(b_Res).toString()));
        return b_Res;
    }

    /** Determines whether the configuration menu is currently enabled.
        @return true when the configuration menu is curently enabled, false otherwise. */
    public boolean isConfigMenuEnabled() {
        return __isConfigMenuEnabled(this.getNativeRef());
    }
    private static final native boolean __isConfigMenuEnabled(long I64_NativeCliRef);

    /** Configuration menu enabling.
        @param B_Enable Enable or disable the configuration menu. */
    public final void enableConfigMenu(boolean B_Enable) {
        __enableConfigMenu(this.getNativeRef(), B_Enable);
    }
    private static final native boolean __enableConfigMenu(long I64_NativeCliRef, boolean B_Enable);
}
