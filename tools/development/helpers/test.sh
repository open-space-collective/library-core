#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Core
# @file           tools/development/helpers/test.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# make test

if [[ -z ${1} ]]; then
    ${script_directory}/../bin/*.test
else
    ${script_directory}/../bin/*.test --gtest_filter=${1}
fi

################################################################################################################################################################
