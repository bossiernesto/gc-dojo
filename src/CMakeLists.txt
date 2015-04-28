cmake_minimum_required(VERSION 2.8)

project(gc_dojo_core)

add_library( markAndSweep
    markandsweep.h markandsweep.cpp)

add_library( markAndCompact
    markandreallocate.h markandreallocate.cpp)

target_link_libraries(
    markAndSweep
    markAndCompact
)

