# Copyright (c) 2006-2009, Alexis Royer
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


# Includes
CLI_DIR := ../../..
PROJECT = libclicpp
STATIC_LIB_PREFIX =
PRODUCT_TYPE = STATIC_LIB
SRC_DIR = $(CPP_DIR)/src
CPP_FILES = $(filter-out $(SRC_DIR)/win_console.cpp,$(wildcard $(SRC_DIR)/*.cpp))
PROJ_INCLUDES = -I$(CPP_DIR)/include
# Include win_console.cpp also for dependency computation
deps: CPP_FILES += $(SRC_DIR)/win_console.cpp
include build.mak

# Debug and help
include $(CLI_DIR)/build/make/help.mak

.PHONY: $(CPP_DIR)/build/make/libclicpp.help
$(CPP_DIR)/build/make/libclicpp.help: ;

.PHONY: $(CPP_DIR)/build/make/libclicpp.vars
$(CPP_DIR)/build/make/libclicpp.vars:
	$(call ShowVariables,)

# Dependencies
include $(AUTO_DEPS_FILE)
