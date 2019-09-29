cmake_minimum_required(VERSION 3.1)

project("bialang"
	LANGUAGES CXX)

function(download_submodule_library LIB_NAME)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/dependencies/${LIB_NAME}")
		if(NOT GIT_FOUND)
			find_package(Git REQUIRED)
		endif()

		message("Downloading ${LIB_NAME}...")

		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --depth 1 -- "dependencies/${LIB_NAME}"
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
	endif()
endfunction()

function(create_tests NAME)
	if(BIA_BUILD_TESTS)
		file(GLOB_RECURSE TMP_SOURCE_FILES
			"${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

		add_executable("${NAME}_test" ${TMP_SOURCE_FILES})
		target_link_libraries("${NAME}_test" ${NAME})
		target_include_directories("${NAME}_test"
			PRIVATE ${CATCH_INCLUDE_DIRS})

		add_test(${NAME} "${NAME}_test" "-s")
	endif()
endfunction()

set(CMAKE_CXX_STANDARD 11)

option(BIA_BUILD_BIA_TOOL "Builds the command line tool for Bia." OFF)
option(BUILD_SHARED_LIBS "Builds the Bia library as a shared library." ON)
option(BIA_BUILD_TESTS "Builds the tests for the Bia library." ON)
option(BIA_GENERATE_DOCUMENTATION "Generate the documentatio with Doxygen." OFF)

# Enable testing
if(BIA_BUILD_TESTS)
	include(CTest)
	set(CATCH_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Catch2")
	enable_testing()
endif()

# Add Bia library
add_subdirectory("bia")

if(BIA_BUILD_BIA_TOOL)
	add_subdirectory("tools/bia")
endif()

# Generate documentary
if(BIA_GENERATE_DOCUMENTATION)
	find_package(Doxygen REQUIRED)

	add_custom_target("doc"
		COMMAND ${DOXYGEN_EXECUTABLE} "Doxyfile"
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Building documentation")
endif()