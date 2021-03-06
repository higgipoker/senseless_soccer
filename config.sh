#!/bin/sh

rm -rf Debug;
rm -rf Release;

mkdir Debug;
mkdir Release;
cd Debug;
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug;

cd ../Release;
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release

cd ..;
mkdir bin;
