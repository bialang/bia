project("string"
		LANGUAGES CXX)

list(APPEND LINK_LIBS
	PUBLIC "gc")

# String encoding conversion dependency
set(BIA_STRING_ENCODING_BACKEND "none"
	CACHE STRING "The library that should be used for encoding conversion of strings.")
set_property(CACHE BIA_STRING_ENCODING_BACKEND
	PROPERTY STRINGS "ICU" "none")

if(${BIA_STRING_ENCODING_BACKEND} STREQUAL "ICU")
	set(BIA_STRING_ENCODING_BACKEND_ICU ON)
	include(FindICU)
	find_package(ICU COMPONENTS io i18n)

	if(ICU_FOUND)
		list(APPEND LINK_LIBS
			PRIVATE ${ICU_LIBRARIES})
	else()
		message("ICU was not found")

		#require_submodule_lib("icu")

		# Compile
	endif()
else()
	set(BIA_STRING_ENCODING_BACKEND_NONE ON)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/string/config.hpp")
	
create_library(STATIC ${LINK_LIBS})