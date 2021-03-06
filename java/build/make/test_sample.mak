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


# Default goal
.DEFAULT_GOAL = check
.PHONY: javatest.default
javatest.default: $(.DEFAULT_GOAL) ;

# Parameters
CLI_XML_RES ?= $(CLI_DIR)/samples/clisample/clisample.xml

# Includes
CLI_DIR := ../../..
include _vars.mak
PRODUCT = TestSample
SRC_DIR = $(CLI_DIR)/java/src/cli/test
JAVA_FILES += $(CLI_TEST_SAMPLE_JAVA)
JAVA_FILES += $(CLI_JAVA)
JAVA_FILES += $(SRC_DIR)/TestTools.java
PROJECT_DEPS += libclijava.mak
PROJECT_DEPS += jni.mak
PROJECT_DEPS += native.mak
include _build.mak
JAVAC_OPTS += -nowarn
PROJ_CLEAN += $(CLI_JAVA) $(CLI_LOG)

# Variables
CLI_CLI2JAVA = $(CLI_DIR)/tools/cli2java.py
CLI_JAVA_CLASS_NAME = $(subst -,_,$(patsubst %.xml,%,$(notdir $(CLI_XML_RES))))
CLI_JAVA = $(CLI_DIR)/java/src/cli/test/samples/$(CLI_JAVA_CLASS_NAME).java
CLI_TEST_SAMPLE_JAVA = $(CLI_DIR)/java/src/cli/test/TestSample.java
CLI_TEST = $(patsubst %.xml,%.test,$(CLI_XML_RES))
CLI_LOG = $(OUT_DIR)/cli/test/samples/$(patsubst %.xml,%,$(notdir $(CLI_XML_RES))).log
CLI_CHECK = $(patsubst %.xml,%.check,$(CLI_XML_RES))

# Rules
.PHONY: check check.xml
check check.xml: $(CLI_LOG) $(CLI_CHECK)
	dos2unix $(CLI_CHECK) 2> /dev/null
	diff $(CLI_LOG) $(CLI_CHECK)

.PHONY: log
log: $(CLI_LOG) ;
$(CLI_LOG): $(CLI_JAVA) build $(CLI_TEST) $(CLI_DIR)/tools/clean_outlog.py
	dos2unix $(CLI_TEST) 2> /dev/null
	$(call RunJava,cli.test.TestSample cli.test.samples.$(CLI_JAVA_CLASS_NAME) $(CLI_TEST) $(CLI_LOG))
	python $(CLI_DIR)/tools/clean_outlog.py $(CLI_LOG)

$(CLI_JAVA): $(CLI_XML_RES) $(CLI_CLI2JAVA)
	$(call CheckDir,$(dir $@))
	python $(CLI_CLI2JAVA) --cli-class-name $(CLI_JAVA_CLASS_NAME) --cli-class-scope public $(CLI_XML_RES) --output $@
	sed -e "1s/^/package cli.test.samples;\n/" -i $@

.PHONY: deps
deps: ;

# Debug and help
include $(CLI_DIR)/build/make/_help.mak

.PHONY: $(CLI_DIR)/java/build/make/test.help
help: $(CLI_DIR)/java/build/make/test.help
$(CLI_DIR)/java/build/make/test.help:
	$(call PrintHelp, check.xml, Check test output for the given XML resource file (CLI_XML_RES))
	$(call PrintHelp, check,     Shortcut for check.xml rule)
	$(call PrintHelp, log,       Generate $(notdir $(CLI_LOG)))

.PHONY: $(CLI_DIR)/java/build/make/test.vars
vars: $(CLI_DIR)/java/build/make/test.vars
$(CLI_DIR)/java/build/make/test.vars:
	$(call ShowVariables,CLI_XML_RES CLI_CLI2JAVA CLI_JAVA CLI_JAVA_CLASS_NAME CLI_TEST_SAMPLE_JAVA CLI_TEST CLI_LOG CLI_CHECK)

# Dependencies
build: $(JAVA_FILES)
