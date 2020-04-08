project(bvm
	LANGUAGES CXX)

create_library(STATIC
	PUBLIC connector
	PUBLIC compiler)
