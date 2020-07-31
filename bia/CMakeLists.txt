cmake_minimum_required(VERSION 3.1)

project(bia
	VERSION 4.0
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
		target_link_libraries(${TARGET} INTERFACE ${ITEM})
		list(APPEND BIA_DEPENDENCIES ${NAME})
		set(BIA_DEPENDENCIES ${BIA_DEPENDENCIES} PARENT_SCOPE)
	endif()
endfunction()



# build exportable libraries
list(APPEND BIA_COMPONENTS base bvm bsl compiler cbia)

# base
add_library(base INTERFACE)
target_sources(base
	INTERFACE
		$<TARGET_OBJECTS:log-obj>
		$<TARGET_OBJECTS:thread-obj>
		$<TARGET_OBJECTS:gc-obj>
		$<TARGET_OBJECTS:string-obj>
		$<TARGET_OBJECTS:member-obj>
		$<TARGET_OBJECTS:resource-obj>)
target_include_directories(base
	INTERFACE
		"$<BUILD_INTERFACE:${BIA_BIALANG_INCLUDE_DIR}>")

link_dependency(base spdlog spdlog::spdlog)
link_dependency(base Threads Threads::Threads)

# bvm
add_library(bvm INTERFACE)
target_sources(bvm
	INTERFACE
		$<TARGET_OBJECTS:bvm-obj>
		$<TARGET_OBJECTS:assembler-obj>)
target_link_libraries(bvm
	INTERFACE
		base)

# bsl
add_library(bsl INTERFACE)
target_sources(bsl
	INTERFACE
		$<TARGET_OBJECTS:bsl-obj>)
target_link_libraries(bsl
	INTERFACE
		bvm)

# compiler
add_library(compiler INTERFACE)
target_sources(compiler
	INTERFACE
		$<TARGET_OBJECTS:compiler-obj>
		$<TARGET_OBJECTS:tokenizer-obj>)
target_link_libraries(compiler
	INTERFACE
		base)

# cbia
add_library(cbia INTERFACE)
target_sources(cbia
	INTERFACE
		$<TARGET_OBJECTS:cbia-obj>)
target_link_libraries(cbia
	INTERFACE
		compiler
		bsl)


# test
if(BIA_BUILD_TESTS)
	add_subdirectory("tests")
endif()


# install
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR "include/")
set(LIBRARY_INSTALL_DIR "lib/bia")

configure_package_config_file("bia-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake"
	INSTALL_DESTINATION "lib/bia/cmake"
	PATH_VARS INCLUDE_INSTALL_DIR LIBRARY_INSTALL_DIR)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/bia-config-version.cmake" DESTINATION "lib/bia/cmake")
install(FILES "config.hpp" "bia.hpp" "cbia.h" DESTINATION "include/bia")

foreach(component ${BIA_COMPONENTS})
	install(TARGETS ${component}
			EXPORT ${component}-targets
			ARCHIVE DESTINATION "lib/bia"
			LIBRARY DESTINATION "lib/bia"
			INCLUDES DESTINATION "include/")
	install(EXPORT ${component}-targets
			DESTINATION "lib/bia/cmake"
			NAMESPACE bia::
			EXPORT_LINK_INTERFACE_LIBRARIES
			FILE "bia-${component}-targets.cmake"
			COMPONENT ${component})
endforeach()
