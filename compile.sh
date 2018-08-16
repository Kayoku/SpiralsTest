#!/bin/bash

set -e

# Install gtest if not

if [ ! -d './googletest-release-1.8.0' ]
then
	wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
	tar xf release-1.8.0.tar.gz
	rm release-1.8.0.tar.gz
	cd googletest-release-1.8.0
	cmake -DBUILD_SHARED_LIBS=ON -G "Ninja" .
	ninja
	cd ..
	sudo cp -a googletest-release-1.8.0/googletest/include/gtest /usr/include
	sudo cp -a googletest-release-1.8.0/googlemock/gtest/libgtest_main.so googletest-release-1.8.0/googlemock/gtest/libgtest.so /usr/lib/
	sudo ldconfig -v | grep gtest
fi

# Project compilation

if [ ! -d './build' ]
then
	mkdir build
fi
cd build
cmake .. -G "Ninja"
ninja
