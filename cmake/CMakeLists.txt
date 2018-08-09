cmake_minimum_required(VERSION 3.0)

project(hash)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

include_directories(
 ../
)

add_executable(geohash
 ../main.c
 ../geohash.c
)
