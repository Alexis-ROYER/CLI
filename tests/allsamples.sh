#!/bin/sh

# This file is part of the CLI library.  The CLI library aims to provide
# facilities in making text-based user interfaces.
# Copyright (C) 2006 Alexis Royer.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


for CLI_CHECK in $(find $(dirname "$0")"/../.." -iname "*.xml.check")
do
    CLI_XML_RES=$(echo "$CLI_CHECK" | sed -e "s/\.xml\.check/\.xml/")
    echo "------- "$(basename "$CLI_XML_RES")" -------"
    $(dirname "$0")/testsample.sh "$CLI_XML_RES" $1
done
