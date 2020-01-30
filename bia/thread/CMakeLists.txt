project("thread"
		LANGUAGES CXX)

list(APPEND LINK_LIBS
	PUBLIC "exception"
	PUBLIC "log")

# Thread backend
set(BIA_THREAD_BACKEND "std::thread"
	CACHE STRING "The thread backend that should be used for creating threads in Bia and in its implementation.")
set_property(CACHE BIA_THREAD_BACKEND
	PROPERTY STRINGS "std::thread" "boost::thread" "none")

if(${BIA_THREAD_BACKEND} STREQUAL "std::thread")
	set(BIA_THREAD_BACKEND_STD ON)

	find_package(Threads REQUIRED)
	list(APPEND LINK_LIBS
		PRIVATE ${CMAKE_THREAD_LIBS_INIT})
elseif(${BIA_THREAD_BACKEND} STREQUAL "boost::thread")
	set(BIA_THREAD_BACKEND_BOOST ON)
else()
	set(BIA_THREAD_BACKEND_NONE ON)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/thread/config.hpp")
	
create_library(STATIC ${LINK_LIBS})