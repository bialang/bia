cmake_minimum_required(VERSION 3.1)

file(GLOB dirs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" "*")

# set(CMAKE_CXX_STANDARD 17)

foreach(dir ${dirs})
	if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
		file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp")

		add_executable(${dir}_test ${sources} ${BACKWARD_ENABLE})
		target_link_libraries(${dir}_test PUBLIC bia::bia)
		target_include_directories(${dir}_test PUBLIC ${CATCH_INCLUDE_DIRS})
		
		if(BACKWARD_ENABLE)
			add_backward(${dir}_test)
		endif()

		if(BIA_BUILD_BENCHMARKS)
			add_test(NAME ${dir}_test COMMAND ${dir}_test)
		else()
			add_test(NAME ${dir}_test
				COMMAND ${dir}_test "~[benchmark]")
		endif()
	endif()
endforeach()

set_property(TARGET bia_test PROPERTY CXX_STANDARD 17)
