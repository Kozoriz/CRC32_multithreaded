cmake_minimum_required(VERSION 2.8)

project (CRC32_multithreaded)
set (PROJECT CRC32_multithreaded)

### FLAGS/PACKAGES
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -w")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR       ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib)

include_directories(src)

file( GLOB HEADERS
   src/*.h
)

file( GLOB SOURCES
   src/*.cc
)


add_executable( ${PROJECT} ${HEADERS} ${SOURCES})

