#!/bin/bash  
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/../

source /home/user/out/arsdk-native/staging/native-wrapper.sh 
source devel/setup.bash 
roslaunch ./src/start_bebop.launch



    
