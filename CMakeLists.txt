cmake_minimum_required (VERSION 2.8)
project (camelup)

set(TARGET camelup)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INC_DIR} ${SRC_DIR})

file(GLOB_RECURSE INC_FILES "${INC_DIR}/*.h" "${SRC_DIR}/*.h")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -Wfatal-errors -Werror")

add_executable (${TARGET} ${SRC_FILES} ${INC_FILES})
