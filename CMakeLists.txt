cmake_minimum_required(VERSION 3.20)
project(aoc2024
        DESCRIPTION "Advent of Code 2024 solutions"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

string(APPEND CMAKE_CXX_FLAGS " -Wall")
string(APPEND CMAKE_CXX_FLAGS " -Wbuiltin-macro-redefined")
string(APPEND CMAKE_CXX_FLAGS " -pedantic")
string(APPEND CMAKE_CXX_FLAGS " -Werror")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME}
  PRIVATE
  "${SOURCE_DIR}/main.cpp"
  "${SOURCE_DIR}/utility.cpp"
  "${SOURCE_DIR}/day1.cpp"
  "${SOURCE_DIR}/day2.cpp"
  "${SOURCE_DIR}/day3.cpp"
  "${SOURCE_DIR}/day4.cpp"
  "${SOURCE_DIR}/day5.cpp"
  "${SOURCE_DIR}/day6.cpp"
  "${SOURCE_DIR}/day7.cpp"
  "${SOURCE_DIR}/day8.cpp"
  "${SOURCE_DIR}/day9.cpp"
  "${SOURCE_DIR}/day10.cpp"
  "${SOURCE_DIR}/day11.cpp"
  "${SOURCE_DIR}/day12.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
