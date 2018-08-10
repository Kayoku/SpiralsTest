cmake_minimum_required(VERSION 3.0)

project(hash)

include_directories(
 ./geohash/src
 ./simhash/src
)

add_executable(geohash
 ./geohash/src/main_geohash.c
 ./geohash/src/geohash.c
)

add_executable(geohash_test
 ./geohash/test/test_geohash.c
 ./geohash/src/geohash.c
)

add_executable(simhash_test
 ./simhash/test/test_simhash.c
 ./simhash/src/simhash.c
)

target_link_libraries(geohash_test cunit)
target_link_libraries(simhash_test cunit ssl crypto)
