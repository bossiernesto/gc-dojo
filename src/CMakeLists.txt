cmake_minimum_required(VERSION 2.8)

project(gc_dojo_core)

add_library( markAndSweep
    markandsweep.h markandsweep.cpp )

target_link_libraries(
    markAndSweep
)

