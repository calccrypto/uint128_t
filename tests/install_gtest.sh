#!/usr/bin/env bash

# not much better than git submodules, but there was never a need/want for the repo in this repo
cd ..
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=install
make -j $(nproc --all)
make -j install
