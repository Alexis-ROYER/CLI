# Copyright (c) 2006-2018, Alexis Royer, http://alexis.royer.free.fr/CLI
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
#       and/or other materials provided with the distribution.
#     * Neither the name of the CLI library project nor the names of its contributors may be used to endorse or promote products derived from this software
#       without specific prior written permission.
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

ifndef __TOOLS_PYTHON__
__TOOLS_PYTHON__ = 1

# Includes
CLI_DIR ?= ../../..
include $(CLI_DIR)/build/make/_vars.mak
include $(CLI_DIR)/tools/build/make/_vars.mak

# Variables
PYTHONPATH := $(CLI_DIR)/tools
PYTHON = export PYTHONPATH=$(PYTHONPATH) && python
PYLINT =
ifneq ($(shell which pylint 2> /dev/null),)
PYLINT = export PYTHONPATH=$(PYTHONPATH) && pylint
endif
OUT_DIR ?= "."

PYLINT_RESULT = $(OUT_DIR)/pylint.done

# Rules
$(PYLINT_RESULT): $(wildcard $(CLI_DIR)/tools/*.py)
ifeq ($(PYLINT),)
	$(warning Please install pylint in order to check python scripts before execution)
else
	$(call CheckDir,$(dir $@))
	$(PYLINT) --rcfile=$(CLI_DIR)/tools/pylint.conf $(wildcard $(CLI_DIR)/tools/*.py)
	touch $@
endif

# Debug and help
include $(CLI_DIR)/build/make/_help.mak

.PHONY: $(CLI_DIR)/tools/build/make/_python.vars
vars: $(CLI_DIR)/tools/build/make/_python.vars
$(CLI_DIR)/tools/build/make/_python.vars:
	$(call ShowVariables,PYTHONPATH PYTHON PYLINT OUT_DIR PYLINT_RESULT)

.PHONY: clean.pylint
clean.pylint:
	rm -f $(PYLINT_RESULT)

endif
# __TOOLS_PYTHON__
