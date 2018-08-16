cmake_minimum_required(VERSION 3.0)

project(SpiralsTest)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic")

enable_testing()
find_package(GTest REQUIRED)

include_directories(
 ./geohash/src
 ./simhash/src
 ./actor-system
 ${GTEST_INCLUDE_DIR}
)

############################################################################
## Exec
############################################################################

add_executable(geohash
 ./geohash/src/main_geohash.c
 ./geohash/src/geohash.c
)

add_executable(simhash
 ./simhash/src/main_simhash.c
 ./simhash/src/simhash.c
)
target_link_libraries(simhash ssl crypto)

add_executable(board
 ./actor-system/board.c
)
target_link_libraries(board czmq zmq)

add_executable(actor-router
 ./actor-system/actor-router-main.c
 ./actor-system/actor-router.c
)
target_link_libraries(actor-router czmq zmq)

add_executable(actor-log
 ./actor-system/actor-log-main.c
 ./actor-system/actor-log.c
)
target_link_libraries(actor-log czmq zmq)

add_executable(actor-simhash
 ./actor-system/actor-simhash-main.c
 ./actor-system/actor-simhash.c
)
target_link_libraries(actor-simhash czmq zmq)

add_executable(actor-geohash
 ./actor-system/actor-geohash-main.c
 ./actor-system/actor-geohash.c
 ./geohash/src/geohash.c
)
target_link_libraries(actor-geohash czmq zmq)

############################################################################
## GTest
############################################################################

add_executable(geohash_test
 ./geohash/test/test_geohash.cpp
 ./geohash/src/geohash.c
)
target_link_libraries(geohash_test gtest gtest_main)

add_executable(simhash_test
 ./simhash/test/test_simhash.cpp
 ./simhash/src/simhash.c
)
target_link_libraries(simhash_test ssl crypto gtest gtest_main)

gtest_discover_tests(geohash_test)
gtest_discover_tests(simhash_test)
