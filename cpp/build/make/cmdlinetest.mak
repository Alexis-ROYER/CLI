# Copyright (c) 2006-2010, Alexis Royer, http://alexis.royer.free.fr/CLI
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#     * Neither the name of the CLI library project nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# Default goal
.DEFAULT_GOAL = run
.PHONY: cmdlinetest.default
cmdlinetest.default: $(.DEFAULT_GOAL) ;

# Includes
CLI_DIR := ../../..
PROJECT = cmdlinetest
SRC_DIR = $(CPP_DIR)/tests/cmd_line
PROJ_INCLUDES += -I$(CPP_DIR)/include
PROJ_INCLUDES += -I$(CPP_DIR)/src
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
CPP_FILES += $(CPP_DIR)/src/consistency.cpp
CPP_FILES += $(CPP_DIR)/src/command_line.cpp
CPP_FILES += $(CPP_DIR)/src/command_line_edition.cpp
CPP_FILES += $(CPP_DIR)/src/command_line_history.cpp
CPP_FILES += $(CPP_DIR)/src/debug.cpp
CPP_FILES += $(CPP_DIR)/src/help.cpp
CPP_FILES += $(CPP_DIR)/src/io_device.cpp
CPP_FILES += $(CPP_DIR)/src/object.cpp
CPP_FILES += $(CPP_DIR)/src/resource_string.cpp
CPP_FILES += $(CPP_DIR)/src/string_device.cpp
CPP_FILES += $(CPP_DIR)/src/tk.cpp
CPP_FILES += $(CPP_DIR)/src/traces.cpp

# Addition for cli::CommandLine
CPP_FILES += $(CPP_DIR)/src/param.cpp
CPP_FILES += $(CPP_DIR)/src/param_string.cpp
CPP_FILES += $(CPP_DIR)/src/syntax_node.cpp
CPP_FILES += $(CPP_DIR)/src/syntax_tag.cpp
CPP_FILES += $(CPP_DIR)/src/element.cpp
CPP_FILES += $(CPP_DIR)/src/shell.cpp
CPP_FILES += $(CPP_DIR)/src/cli.cpp
CPP_FILES += $(CPP_DIR)/src/menu.cpp
CPP_FILES += $(CPP_DIR)/src/config_menu.cpp
CPP_FILES += $(CPP_DIR)/src/traces_menu.cpp
CPP_FILES += $(CPP_DIR)/src/keyword.cpp
CPP_FILES += $(CPP_DIR)/src/endl.cpp
CPP_FILES += $(CPP_DIR)/src/io_mux.cpp
CPP_FILES += $(CPP_DIR)/src/mt_device.cpp

PROJ_CPP_FLAGS += -DCLI_NO_STL
PROJ_CPP_FLAGS += -DCLI_MAX_CMD_LINE_LENGTH=256
PROJ_CPP_FLAGS += -DCLI_MAX_CMD_LINE_WORD_COUNT=32
PROJ_CPP_FLAGS += -DCLI_MAX_WORD_LENGTH=16
include _build.mak

# Rules
.PHONY: run
run: build
	$(PRODUCT)

# Dependencies
include $(AUTO_DEPS_FILE)
