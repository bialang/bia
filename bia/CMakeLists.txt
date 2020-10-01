cmake_minimum_required(VERSION 3.1)

project(bia
	VERSION 0.0.0
	LANGUAGES CXX)

option(BIA_LOG_ENABLE "Whether the Bia library should make internal logs to the default logger." OFF)
set(BIA_UTIL_CONTRACT_BEHAVIOR "abort"
	CACHE STRING "How a contract violation should end {throw, abort, none}.")
set_property(CACHE BIA_UTIL_CONTRACT_BEHAVIOR
	PROPERTY STRINGS "throw" "abort" "none")
set(BIA_THREAD_BACKEND "std::thread"
	CACHE STRING "The thread backend that should be used for creating threads in Bia and in its implementation {std::thread, none}.")
set_property(CACHE BIA_THREAD_BACKEND
	PROPERTY STRINGS "std::thread" "none")
set(BIA_RESOURCE_PAGE_SIZE 256
	CACHE STRING "The size of each page for the resource manager in bytes.")

add_library(bia)

# logging
if(BIA_LOG_ENABLE)
	find_package(spdlog REQUIRED)
	list(APPEND BIA_DEPENDENCIES spdlog)
	target_link_libraries(bia
		PUBLIC spdlog::spdlog)

	set(BIA_LOG_NAME "bialang-logger"
		CACHE STRING "The name of the default logger.")
	set(BIA_LOG_PATTERN "[%T.%e | %n | %t | %^%l%$ ] %@@%!\\n\t%v"
		CACHE STRING "The defaul logging pattern. For more information look here: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags")
	set(BIA_LOG_LEVEL "INFO"
		CACHE STRING "The logging level (CIRITICAL, ERROR, WARN, INFO, DEBUG, TRACE)")
	set_property(CACHE BIA_LOG_LEVEL
		PROPERTY STRINGS "CRITICAL" "ERROR" "WARN" "INFO" "DEBUG" "TRACE")
endif()

# test endianess
include(TestBigEndian)
test_big_endian(BIA_BIG_ENDIAN)

if("${BIA_UTIL_CONTRACT_BEHAVIOR}" STREQUAL "throw")
	set(BIA_UTIL_CONTRACT_BEHAVIOR_THROW TRUE)
elseif("${BIA_UTIL_CONTRACT_BEHAVIOR}" STREQUAL "abort")
	set(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT TRUE)
endif()

# thread
if("${BIA_THREAD_BACKEND}" STREQUAL "std::thread")
	find_package(Threads REQUIRED)
	list(APPEND BIA_DEPENDENCIES Threads)
	target_link_libraries(bia
		PUBLIC Threads::Threads)
	set(BIA_THREAD_BACKEND_STD ON)
else()
	# disable threading
	set(BIA_THREAD_BACKEND_NONE ON)
	set(BIA_THREAD_SLEEP_FUNCTION ""
		CACHE STRING "The sleep function implementation. Takes a single std::chrono::duration<Rep, Period> argument.")
	set(BIA_THREAD_SLEEP_INCLUDE ""
		CACHE STRING "One additional include for the sleep function. For example <thread>")

	if(NOT BIA_THREAD_SLEEP_FUNCTION)
		message(FATAL_ERROR "BIA_THREAD_SLEEP_FUNCTION must be defined.")
	endif()
endif()

# string
set(BIA_STRING_ENCODING_BACKEND_NONE ON)


# configure all config.hpp.in
file(GLOB_RECURSE config_templates "${CMAKE_CURRENT_SOURCE_DIR}/*config.hpp.in")

foreach(config ${config_templates})
	string(LENGTH "${config}" config_length)
	math(EXPR config_length "${config_length} - 3")
	string(SUBSTRING "${config}" 0 ${config_length} config_output)
	configure_file("${config}" "${config_output}")
endforeach()


# bia
file(GLOB_RECURSE BIA_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE BIA_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
list(APPEND BIA_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/cbia.h")

target_sources(bia
	PRIVATE "${BIA_SOURCE_FILES}" "${CMAKE_CURRENT_HEADER_FILES}")
target_include_directories(bia
	PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>")
add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-missing-field-initializers -Wno-unused-parameter)
add_library(bia::bia ALIAS bia)


# install
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR "include")
set(LIBRARY_INSTALL_DIR "lib")

configure_package_config_file("bia-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake"
	INSTALL_DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia"
	PATH_VARS INCLUDE_INSTALL_DIR LIBRARY_INSTALL_DIR)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES
		"${CMAKE_CURRENT_BINARY_DIR}/bia-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/bia-config-version.cmake"
	DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "${INCLUDE_INSTALL_DIR}"
	FILES_MATCHING REGEX ".*\\.(hpp|h)$")
install(TARGETS bia
	EXPORT bia-targets
	ARCHIVE DESTINATION "${LIBRARY_INSTALL_DIR}"
	LIBRARY DESTINATION "${LIBRARY_INSTALL_DIR}"
	INCLUDES DESTINATION "${INCLUDE_INSTALL_DIR}")
install(EXPORT bia-targets
	DESTINATION "${LIBRARY_INSTALL_DIR}/cmake/bia"
	NAMESPACE bia::
	EXPORT_LINK_INTERFACE_LIBRARIES
	FILE "bia-targets.cmake"
	COMPONENT bia)
