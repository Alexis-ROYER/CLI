-------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------


PURPOSE
  The CLI library makes it easy to generate command line interfaces.

VERSION
  Please refer to the VERSION.txt file.

INSTALL
  This library needs the 'ncurses' library for the console mode.
  It also needs a JDK 1.5 at least, with a regular JAVA_HOME environment variable being set.
  Assuming this, you should compile the library from the sources using the following commands:
    $ cd build/make
    $ make
  or (debug version):
    $ make _DEBUG=1
 Eventually copy 'cli.dll/so' and extract 'cli.jar' in the correct paths
 or modify your paths to have java work with this library

USE
  Write CLI definitions in XML files.
  Generate native code thanks to the cli2cpp.py and cli2java.py transformation tool.
  Compile and link with the library.
  Enjoy...

CONTACT / MORE INFO
  ./web/index.html
  ./web/user-guide/cli-user-guide.html
  http://alexis.royer.free.fr/CLI/

