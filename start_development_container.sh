#!/bin/bash
set -euxo pipefail
IMAGE=drone/devel-container:v2
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR
docker run --rm -it -v $(pwd):/home/user/src --network=host drone/devel-container:v1 

