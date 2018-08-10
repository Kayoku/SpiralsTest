#!/bin/bash

set -e

cd cmake
cmake -G "Ninja" .
ninja
