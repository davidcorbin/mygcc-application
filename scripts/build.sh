#!/bin/bash

set -x

git submodule update --init --recursive
cd ext/cpr
cmake .
make
cd ../json
cmake .
make
cd ../..
