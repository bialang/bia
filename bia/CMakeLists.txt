project("bia"
	LANGUAGES CXX)

set(BIA_VERSION_MAJOR 4)
set(BIA_VERSION_MINOR 0)

function(create_library LIB_TYPE)
	get_filename_component(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

	if(${LIB_TYPE} STREQUAL "INTERFACE")
		set(VISIBILITY INTERFACE)
	else()
		file(GLOB_RECURSE SOURCE_FILES
			"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
		set(VISIBILITY PUBLIC)
	endif()

	# config file
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in")
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}/config.hpp")
	endif()

	add_library(${LIB_NAME} ${LIB_TYPE}
		${SOURCE_FILES})

	# add tests
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
		create_tests(${LIB_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/tests")
	endif()

	# add includes
	target_include_directories(${LIB_NAME}
		${VISIBILITY} ${CMAKE_CURRENT_SOURCE_DIR})

	# add libraries
	foreach(i RANGE 1 ${ARGC} 2)
		math(EXPR j "${i} + 1")
		target_link_libraries(${LIB_NAME}
			${ARGV${i}} ${ARGV${j}})
	endforeach()
endfunction()

# add modules
add_subdirectory("exception")
add_subdirectory("log")
add_subdirectory("util")
add_subdirectory("thread")
#add_subdirectory("bytecode")
add_subdirectory("gc")
add_subdirectory("string")
add_subdirectory("tokenizer")
#add_subdirectory("stack")
#add_subdirectory("stream")
#add_subdirectory("member_interface")
#add_subdirectory("connector_interface")
#add_subdirectory("member")
#add_subdirectory("compiler")
#add_subdirectory("creator")
#add_subdirectory("connector")
#add_subdirectory("bvm")