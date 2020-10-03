#!/bin/bash

BUILD_PATH=$1
COVERAGE_PATH=$2

echo "Tests build path =" $BUILD_PATH

[[ -z $BUILD_PATH ]] && echo -e "\e[44mEmpty arg BUILD_PATH\e[0m" && exit 1 
[[ -z $COVERAGE_PATH ]] && echo -e "\e[44mEmpty arg COVERAGE_PATH\e[0m" && exit 1 

cd $BUILD_PATH

lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info -o coverage.info \
	"/usr*" \
	"*src_test/*" \
	"*external/*" 
genhtml coverage.info --output-directory=$COVERAGE_PATH

