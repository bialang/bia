cmake_minimum_required(VERSION 3.1)

# Project info
project(Bia)
set(Bia_VERSION_MAJOR 3)
set(Bia_VERSION_MINOR 60)

include_directories(Bia)

add_subdirectory(Bia)
add_subdirectory(tests)