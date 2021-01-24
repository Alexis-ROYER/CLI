# Copyright (c) 2006-2007, Alexis Royer
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

ifndef __ROOT_VARS__
__ROOT_VARS__ = 1

# Parameters
ROOT_DIR ?= ../..

#Includes
include $(ROOT_DIR)/build/make/utils.mak

# Variables
CPP_DIR = $(ROOT_DIR)/cpp
JAVA_DIR = $(ROOT_DIR)/java
SAMPLES_DIR = $(ROOT_DIR)/samples
WEB_DIR = $(ROOT_DIR)/web

ifndef _DEBUG
	RDX = Release
else
	RDX = Debug
endif

# Debug and help
.PHONY: $(ROOT_DIR)/build/make/vars.help
$(ROOT_DIR)/build/make/vars.help: ;

.PHONY: $(ROOT_DIR)/build/make/vars.vars
$(ROOT_DIR)/build/make/vars.vars:
	$(call ShowVariables,ROOT_DIR CPP_DIR JAVA_DIR SAMPLES_DIR WEB_DIR)


endif
# __ROOT_VARS__
