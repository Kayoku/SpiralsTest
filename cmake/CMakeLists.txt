cmake_minimum_required(VERSION 3.0)

project(hash)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

include_directories(
 ../geohash/src
)

add_executable(geohash
 ../geohash/src/main_geohash.c
 ../geohash/src/geohash.c
)
