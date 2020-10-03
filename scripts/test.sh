#!/bin/bash

if [ -d "tests/build_test" ];
then
        rm -rf tests/build_test/*
else
        mkdir -p tests/build_test
fi

cd tests/build_test

cmake ..

make -j $(($(nproc) - 1))

shopt -s extglob

./test_lvx_to_las

../../scripts/coverage.sh . ../../doc/coverage | tail -n 3

rm -rf !("test_lvx_to_las")
