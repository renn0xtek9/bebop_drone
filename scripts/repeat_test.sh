#!/bin/bash 
set -e pipefail 
source /opt/ros/melodic/setup.bash 
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/../

for (( c=0; c<=1000; c+=1 ))
do
    catkin_make run_tests
done
