#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/ci/test.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

project_directory="${script_directory}/../.."
docker_directory="${script_directory}/../docker"

source "${docker_directory}/.env"

docker run \
--rm \
--volume="${project_directory}:/app:rw" \
--volume="/app/build" \
--volume="${docker_directory}/environment/helpers/build.sh:/app/build/build.sh:ro" \
--volume="${docker_directory}/environment/helpers/test.sh:/app/build/test.sh:ro" \
--workdir="/app/build" \
${image_name} \
/bin/bash -c "/app/build/build.sh && /app/build/test.sh"

################################################################################################################################################################