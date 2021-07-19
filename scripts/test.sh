#!/bin/bash 
set -euxo pipefail 
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/../
export ROS_DISTRO=melodic

source /opt/ros/melodic/setup.bash 
catkin_make tests 
catkin_make run_tests
