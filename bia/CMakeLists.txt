cmake_minimum_required(VERSION 3.1)

project(bia
	VERSION 4.0
	LANGUAGES CXX)

set(BIA_BIALANG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

function(create_library)
	get_filename_component(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

	file(GLOB_RECURSE SOURCE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

	if(SOURCE_FILES)
		set(LIB_NAME ${LIB_NAME}-obj)

		# add dependencies
#		foreach(dep ${ARGV})
#			message(STATUS "adding ${dep}")
#			list(APPEND SOURCE_FILES $<TARGET_OBJECTS:${dep}-obj>)
#		endforeach()

		add_library(${LIB_NAME} OBJECT ${SOURCE_FILES})
		target_include_directories(${LIB_NAME}
			PUBLIC "$<BUILD_INTERFACE:${BIA_BIALANG_INCLUDE_DIR}>")
	endif()

	# config file
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in")
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp")
	endif()

#	install(TARGETS ${LIB_NAME}
#		EXPORT ${LIB_NAME}-targets
#		ARCHIVE DESTINATION "lib/bia"
#		LIBRARY DESTINATION "lib/bia"
#		INCLUDES DESTINATION "include")
#	install(EXPORT ${LIB_NAME}-targets
#			DESTINATION "lib/bia/cmake"
#			NAMESPACE bia::
#			FILE "bia-${LIB_NAME}-targets.cmake"
#			COMPONENT ${LIB_NAME})
endfunction()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
				"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp")

# add modules
set(BIA_MODULES "")

foreach(module "exception" "log" "util" "thread" "gc" "string" "member" "creator" "resource" "bytecode" "tokenizer" "connector" "bvm" "compiler" "bsl")
	add_subdirectory("${module}")
	list(APPEND BIA_MODULES "${module}")
	
	install(DIRECTORY "${module}"
			DESTINATION "include/bia"
			FILES_MATCHING PATTERN "*.hpp")
endforeach()


install(FILES "config.hpp"
		DESTINATION "include/bia")

find_package(Threads REQUIRED)
add_library(base STATIC $<TARGET_OBJECTS:log-obj> $<TARGET_OBJECTS:thread-obj> $<TARGET_OBJECTS:gc-obj> $<TARGET_OBJECTS:string-obj> $<TARGET_OBJECTS:resource-obj>)
target_link_libraries(base
	PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(base
	PUBLIC "$<BUILD_INTERFACE:${BIA_BIALANG_INCLUDE_DIR}>")

add_library(bsl STATIC $<TARGET_OBJECTS:bsl-obj> $<TARGET_OBJECTS:bvm-obj>)
target_link_libraries(bsl
	PUBLIC base)
add_library(compiler STATIC $<TARGET_OBJECTS:compiler-obj> $<TARGET_OBJECTS:tokenizer-obj>)
target_link_libraries(compiler
	PUBLIC base)

add_executable(maindev "main.cpp" ${BACKWARD_ENABLE})
target_link_libraries(maindev
	PUBLIC bsl compiler)

#add_backward(maindev)
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

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/bia-config-version.cmake"
		DESTINATION "lib/bia/cmake")




# CPack
set(CPACK_PACKAGE_NAME "Bia")
set(CPACK_PACKAGE_DESCRIPTION "Embedded scripting language")
set(CPACK_PACKAGE_VENDOR "Bialang")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Bia/${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

include(CPack)
