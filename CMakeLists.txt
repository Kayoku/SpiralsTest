cmake_minimum_required(VERSION 3.0)

project(hash)

include_directories(
 ./geohash/src
 ./simhash/src
 ./actor-system
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

add_executable(simhash
 ./simhash/src/main_simhash.c
 ./simhash/src/simhash.c
)

add_executable(board
 ./actor-system/board.c
)

add_executable(actor-router
 ./actor-system/actor-router-main.c
 ./actor-system/actor-router.c
)

add_executable(actor-log
 ./actor-system/actor-log-main.c
 ./actor-system/actor-log.c
)

add_executable(actor-simhash
 ./actor-system/actor-simhash-main.c
 ./actor-system/actor-simhash.c
)

add_executable(actor-geohash
 ./actor-system/actor-geohash-main.c
 ./actor-system/actor-geohash.c
)

target_link_libraries(simhash_test cunit ssl crypto)
target_link_libraries(simhash ssl crypto)
target_link_libraries(geohash_test cunit)
target_link_libraries(actor-router czmq zmq)
target_link_libraries(actor-log czmq zmq)
target_link_libraries(actor-simhash czmq zmq)
target_link_libraries(actor-geohash czmq zmq)
target_link_libraries(board czmq zmq)
