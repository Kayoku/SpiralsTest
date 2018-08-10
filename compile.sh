#!/bin/bash

set -e

mkdir build
cd build
cmake .. -G "Ninja"
ninja
