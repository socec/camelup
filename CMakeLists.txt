cmake_minimum_required (VERSION 2.8)
project (camelup)

set(TARGET camelup)

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE INC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_executable (${TARGET} ${SRC_FILES} ${INC_FILES})

target_compile_options(${TARGET} PUBLIC -std=c++11 -Wall -Wfatal-errors)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
