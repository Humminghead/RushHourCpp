cmake_minimum_required(VERSION 3.16)

include(ExternalProject)

ExternalProject_Add(ChronoTimer
  GIT_REPOSITORY https://github.com/Humminghead/ChronoTimer.git
  GIT_TAG        main
  INSTALL_DIR ${CMAKE_BINARY_DIR}/3rdparty/inst
  BINARY_DIR  ${CMAKE_BINARY_DIR}/3rdparty/bin
  SOURCE_DIR  ${CMAKE_BINARY_DIR}/3rdparty/src
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/3rdparty/inst
)

project(operators_pp_lh_rh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/3rdparty/inst/include)
