cmake_minimum_required(VERSION 3.1)

list(APPEND LINK_LIBS
	PUBLIC exception
	PUBLIC $<TARGET_OBJECTS:log>
	PUBLIC util)

# thread backend
set(BIA_THREAD_BACKEND "std::thread"
	CACHE STRING "The thread backend that should be used for creating threads in Bia and in its implementation.")
set_property(CACHE BIA_THREAD_BACKEND
	PROPERTY STRINGS "std::thread" "none")

if(${BIA_THREAD_BACKEND} STREQUAL "std::thread")
	set(BIA_THREAD_BACKEND_STD ON)

	find_package(Threads REQUIRED)
	list(APPEND LINK_LIBS
		PRIVATE ${CMAKE_THREAD_LIBS_INIT})
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
	
create_library("${CMAKE_CURRENT_SOURCE_DIR}")
