#!/bin/bash

if [ -d "build" ]; 
then
	rm -rf build/*
else
        mkdir -p build
fi

files=$( find "$PWD/src" -path "$PWD/src/plot" -prune -false -o -name '*.cpp' -o -name '*.h' )

cd build
cmake -DGUI=OFF .. &>/dev/null

# include_args="$(cat ./compile_commands.json | grep command | sed "s/-I/\n-I/g" | grep -v command | awk '{print $1}' | sed "s/-I/-I /g")"

checks=$(cat ../external/cpp_codestyle/codestyle.cfg)

clang-tidy -config="$checks" $files -p=. 2>/dev/null