
file(GLOB DIRS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" "*")

foreach(dir ${DIRS})
	if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
		create_test(${dir} "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
	endif()
endforeach()
