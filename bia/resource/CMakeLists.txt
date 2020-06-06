cmake_minimum_required(VERSION 3.1)

set(BIA_RESOURCE_PAGE_SIZE 256 CACHE STRING "The size of each page for the resource manager in bytes.")

create_library("${CMAKE_CURRENT_SOURCE_DIR}")
