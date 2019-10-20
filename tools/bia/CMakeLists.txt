file(GLOB BIA_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

download_submodule_library("CLI11")

# Get zlib
find_package(ZLIB)

if(NOT ZLIB_FOUND)
	# Download https://www.zlib.net/zlib-1.2.11.tar.gz c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1
endif()

add_executable("biatool" ${BIA_SOURCE_FILES})
target_link_libraries("biatool" "bia")
target_include_directories("biatool" "${CMAKE_SOURCE_DIR}/dependencies/CLI11/include/")
set_target_properties("biatool"
	PROPERTIES OUTPUT_NAME "bia")