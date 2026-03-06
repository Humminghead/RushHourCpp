cmake_minimum_required(VERSION 3.16)

project(RushHourCppExamples LANGUAGES CXX)

file(GLOB_RECURSE PROJECTS ${CMAKE_CURRENT_SOURCE_DIR}/ "*/CMakeLists.txt")

foreach(PRJ ${PROJECTS})
  string (FIND ${PRJ} "/build/" POS)
  if( ${POS} EQUAL -1)
    string(REGEX REPLACE "\/CMakeLists.txt" "" TEMP_PRJ ${PRJ})
    add_subdirectory(${TEMP_PRJ})
  endif()
endforeach()
