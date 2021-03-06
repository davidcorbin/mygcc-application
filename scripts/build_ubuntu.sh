#!/bin/bash

set -x

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y software-properties-common
sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y git build-essential cmake qt5-default libqt5svg5* libssl-dev gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

mkdir build
cd build
cmake ..
make
