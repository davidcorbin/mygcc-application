#!/bin/bash

set -x

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y software-properties-common
sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y git build-essential cmake libssl-dev gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

# Install Qt from source
if [ ! -e Qt/5.10 ] ; then
  rm -rf Qt ;
  wget http://download.qt.io/official_releases/qt/5.10/5.10.0/qt-opensource-linux-x64-5.10.0.run ;
  chmod +x ./qt-opensource-linux-x64-5.10.0.run ;
  ./qt-opensource-linux-x64-5.10.0.run --platform minimal --script ../scripts/qt-installer-noninteractive.qs --no-force-installations ;
fi

git submodule update --init --recursive
mkdir build
cd build
cmake ..
make

