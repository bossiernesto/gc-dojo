message( STATUS ${CMAKE_SOURCE_DIR} )

include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${CMAKE_SOURCE_DIR}/lib_cspec )

add_executable( markAndSweepTest
    markAndSweepTest.cpp
)

target_link_libraries( markAndSweepTest
    cspec
    markAndSweep
)

