cmake_minimum_required(VERSION 3.16)

project(RushHourCppExamples LANGUAGES CXX)

file(GLOB_RECURSE PROJECTS ${CMAKE_CURRENT_SOURCE_DIR}/projects "*/CMakeLists.txt")

foreach(PRJ ${PROJECTS})
    string(REGEX REPLACE "\/CMakeLists.txt" "" TEMP_PRJ ${PRJ})
    add_subdirectory(${TEMP_PRJ})
endforeach()
