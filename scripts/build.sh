#!/bin/bash

set -x

git submodule update --init --recursive
cd ext/cpr
cmake .
cd ../json
cmake .
cd ../..
