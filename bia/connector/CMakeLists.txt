project("connector"
	LANGUAGES CXX)
	
create_library(INTERFACE
	INTERFACE "stack"
	INTERFACE "member_interface")