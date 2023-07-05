#!/bin/bash
set echo off
echo "Building GameCode..."

clang++ -std=c++11 -stdlib=libstdc++ -rdynamic -D DEBUG -g -shared -undefined dynamic_lookup -fPIC -ldl -v game.cpp -o ../../../Binaries/Linux/spaceinvaders.os

echo "Done"
