#!/bin/bash
set -euxo pipefail 
sudo apt-get install -y autoconf language-pack-en git build-essential libtool libavahi-client-dev libavcodec-dev libavformat-dev libswscale-dev libncurses5-dev mplayer
cd $HOME
curl https://storage.googleapis.com/git-repo-downloads/repo-1 > $HOME/repo
python3 $HOME/repo init -u https://github.com/Parrot-Developers/arsdk_manifests.git
python3 $HOME/repo sync
./build.sh -p arsdk-native -t build-sdk -j
