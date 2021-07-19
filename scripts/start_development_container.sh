#!/bin/bash
set -euxo pipefail
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/../

IMAGE=drone/devel-container:v4
docker run --rm -it -v $(pwd):/home/user/src --network=host $IMAGE
