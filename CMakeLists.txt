cmake_minimum_required(VERSION 3.1)

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

option(BIA_BUILD_BIA_TOOL "Builds the command line tool for Bia." ON)
option(BUILD_SHARED_LIBS "Builds the Bia library as a shared library." ON)
option(BIA_BUILD_TESTS "Builds the tests for the Bia library." ON)
option(BIA_GENERATE_DOCUMENTATION "Generate the documentatio with Doxygen." ON)

# Enable testing
if(BIA_BUILD_TESTS)
	include(CTest)
	option(CATCH_INSTALL_DOCS "" OFF)
	option(CATCH_INSTALL_HELPERS "" OFF)
	add_subdirectory("dependencies/Catch2")
	string(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dependencies/Catch2/contrib;")
	include(Catch)
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