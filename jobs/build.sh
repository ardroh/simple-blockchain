#!/bin/bash

workspace=$1
mode=$2

if [[ "$2" == "clean" ]]; then
    rm -rf "$workspace/build"
fi

mkdir -p "$workspace/build"
pushd "$workspace/build"

if [[ "$2" == "clean" ]]; then
    cmake .. -DCMAKE_BUILD_TYPE=Debug
fi


make
