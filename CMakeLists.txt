cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(GTU_AUTONOMOUS_VEHICLE)

include_directories(${PROJECT_SOURCE_DIR}/src/modules/*)

file(GLOB_RECURSE MODULES ${PROJECT_SOURCE_DIR} *.cpp)

add_executable(modules ${MODULES})