#!/bin/bash

sudo apt-get install build-essential gcc-8 g++-8 cmake make lcov gcovr clang-tools clang-tidy clang-format ninja-build
sudo apt install libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib
