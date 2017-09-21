#!/bin/bash

mkdir -p build
pushd build
    cmake ..
    make -j8
popd

build/opencv-cpp-test ../resources/test.png
