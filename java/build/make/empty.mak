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
.DEFAULT_GOAL = build
.PHONY: empty.default
empty.default: $(.DEFAULT_GOAL) ;

# Includes
CLI_DIR := ../../..
include _vars.mak
PRODUCT = empty
SRC_DIR = $(JAVA_DIR)/src/cli/test
JAVA_FILES = $(CLI_GO_JAVA) $(CLI_JAVA)
PROJECT_DEPS = native.mak
include _build.mak
PROJ_CLEAN += $(CLI_JAVA)

# Variables
CLI_XML_RES = $(CLI_DIR)/samples/user-guide/empty.xml
CLI_XSL = $(JAVA_DIR)/xsl/javaclic.xsl
CLI_JAVA = $(patsubst %.xml,$(JAVA_DIR)/src/cli/test/%.java,$(notdir $(CLI_XML_RES)))
CLI_JAVA_CLASS_NAME = $(subst -,_,$(patsubst %.java,%,$(notdir $(CLI_JAVA))))
CLI_GO_JAVA = $(JAVA_DIR)/src/cli/test/GoEmpty.java

# Rules
run:
	cd $(OUT_DIR) && java cli.test.GoEmpty

$(CLI_JAVA): $(CLI_XML_RES) $(CLI_XSL)
	mkdir -p $(dir $(OUT_DIR))
	echo "package cli.test;" > $(CLI_JAVA)
	xsltproc --stringparam STR_CliClassName $(CLI_JAVA_CLASS_NAME) $(CLI_XSL) $(CLI_XML_RES) >> $(CLI_JAVA)

.PHONY: deps
deps: ;

# Debug and help
include $(CLI_DIR)/build/make/_help.mak

.PHONY: $(JAVA_DIR)/build/make/empty.help
help: $(JAVA_DIR)/build/make/empty.help
$(JAVA_DIR)/build/make/empty.help:
	$(call PrintHelp, run, 	 Run the Empty sample)

.PHONY: $(JAVA_DIR)/build/make/empty.vars
vars: $(JAVA_DIR)/build/make/empty.vars
$(JAVA_DIR)/build/make/empty.vars:
	$(call ShowVariables,CLI_XML_RES CLI_XSL CLI_JAVA CLI_JAVA_CLASS_NAME CLI_GO_JAVA)

# Dependencies
build: $(JAVA_FILES)
