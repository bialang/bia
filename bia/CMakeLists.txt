cmake_minimum_required(VERSION 3.1)

project(bia
	VERSION 4.0.0
	LANGUAGES CXX)

set(BIA_BIALANG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

function(create_library DIRECTORY)
	get_filename_component(LIB_NAME ${DIRECTORY} NAME)

	file(GLOB_RECURSE SOURCE_FILES "${DIRECTORY}/*.cpp")

	if(SOURCE_FILES)
		add_library(${LIB_NAME}-obj OBJECT ${SOURCE_FILES})
		target_include_directories(${LIB_NAME}-obj PUBLIC "$<BUILD_INTERFACE:${BIA_BIALANG_INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
		
		if(BUILD_SHARED_LIBS)
			set_property(TARGET ${LIB_NAME}-obj PROPERTY POSITION_INDEPENDENT_CODE ON)
		endif()
	endif()

	# config file
	if(EXISTS "${DIRECTORY}/config.hpp.in")
		configure_file("${DIRECTORY}/config.hpp.in" "${DIRECTORY}/config.hpp")
	endif()
endfunction()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
				"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp")

# add modules
set(BIA_MODULES "")

foreach(module "exception" "log" "util" "thread" "gc" "string" "member" "creator" "resource" "bytecode" "tokenizer" "connector" "bvm" "assembler" "compiler" "bsl" "detail" "cbia")
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${module}/CMakeLists.txt")
		add_subdirectory("${module}")
	else()
		create_library("${CMAKE_CURRENT_SOURCE_DIR}/${module}")
	endif()

	list(APPEND BIA_MODULES "${module}")

	install(DIRECTORY "${module}"
			DESTINATION "include/bia"
			FILES_MATCHING PATTERN "*.hpp")
endforeach()


# dependency function
function(link_dependency TARGET NAME ITEM)
	if(BIA_DEPENDENCY_${NAME})
		find_package(${NAME} REQUIRED)
		target_link_libraries(${TARGET} PUBLIC ${ITEM})
		list(APPEND BIA_DEPENDENCIES ${NAME})
		set(BIA_DEPENDENCIES ${BIA_DEPENDENCIES} PARENT_SCOPE)
	endif()
endfunction()



# build exportable libraries
list(APPEND BIA_COMPONENTS base bvm bsl compiler bia cbia)

# base
add_library(base
	$<TARGET_OBJECTS:log-obj>
	$<TARGET_OBJECTS:thread-obj>
	$<TARGET_OBJECTS:gc-obj>
	$<TARGET_OBJECTS:string-obj>
	$<TARGET_OBJECTS:member-obj>
	$<TARGET_OBJECTS:resource-obj>)
add_library(bia::base ALIAS base)
set_target_properties(base
	PROPERTIES
		OUTPUT_NAME "bia_base")
target_include_directories(base
	PUBLIC
		"$<BUILD_INTERFACE:${BIA_BIALANG_INCLUDE_DIR}>")

link_dependency(base spdlog spdlog::spdlog)
link_dependency(base Threads Threads::Threads)

# bvm
add_library(bvm
	$<TARGET_OBJECTS:bvm-obj>
	$<TARGET_OBJECTS:assembler-obj>)
add_library(bia::bvm ALIAS bvm)
set_target_properties(bvm
	PROPERTIES
		OUTPUT_NAME "bia_bvm")
target_link_libraries(bvm
	PUBLIC
		base)

# bsl
add_library(bsl
	$<TARGET_OBJECTS:bsl-obj>)
add_library(bia::bsl ALIAS bsl)
set_target_properties(bsl
	PROPERTIES
		OUTPUT_NAME "bia_bsl")
target_link_libraries(bsl
	PUBLIC
		bvm)

# compiler
add_library(compiler
	$<TARGET_OBJECTS:compiler-obj>
	$<TARGET_OBJECTS:tokenizer-obj>)
add_library(bia::compiler ALIAS compiler)
set_target_properties(compiler
	PROPERTIES
		OUTPUT_NAME "bia_compiler")
target_link_libraries(compiler
	PUBLIC
		base)

# bia
add_library(bia INTERFACE)
add_library(bia::bia ALIAS bia)
target_link_libraries(bia
	INTERFACE
		compiler
		bsl)


# cbia
add_library(cbia
	$<TARGET_OBJECTS:cbia-obj>)
add_library(bia::cbia ALIAS cbia)
set_target_properties(cbia
	PROPERTIES
		OUTPUT_NAME "bia_cbia")
target_link_libraries(cbia
	PUBLIC
		bia)


# test
if(BIA_BUILD_TESTS)
	add_subdirectory("tests")
endif()


# install
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR "include/")
set(LIBRARY_INSTALL_DIR "lib/")

configure_package_config_file("bia-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake"
	INSTALL_DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia"
	PATH_VARS INCLUDE_INSTALL_DIR LIBRARY_INSTALL_DIR)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/bia-config-version.cmake"
	DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia")
install(FILES "config.hpp" "bia.hpp" "cbia.h"
	DESTINATION "${INCLUDE_INSTALL_DIR}/bia")

foreach(component ${BIA_COMPONENTS})
	install(TARGETS ${component}
			EXPORT ${component}-targets
			ARCHIVE DESTINATION "${LIBRARY_INSTALL_DIR}"
			LIBRARY DESTINATION "${LIBRARY_INSTALL_DIR}"
			INCLUDES DESTINATION "${INCLUDE_INSTALL_DIR}")
	install(EXPORT ${component}-targets
			DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia"
			NAMESPACE bia::
			EXPORT_LINK_INTERFACE_LIBRARIES
			FILE "bia-${component}-targets.cmake"
			COMPONENT ${component})
endforeach()
