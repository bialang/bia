project("external"
		LANGUAGES CXX)

# Regex dependecy
set(BIA_REGEX_BACKEND "PCRE2" 
	CACHE STRING "The regex backend that should be used for default patterns in the Bia language.")
set_property(CACHE BIA_REGEX_BACKEND
	PROPERTY STRINGS "PCRE2" "std::regex" "none")

if(${BIA_REGEX_BACKEND} STREQUAL "none")
	# Download PCRE2
	download_submodule_library("PCRE2")

	# Build
	option(PCRE2_BUILD_PCRE2_8 "" OFF)
	option(PCRE2_BUILD_PCRE2_16 "" ON)
	option(PCRE2_SUPPORT_JIT "" ON)
	option(PCRE2_BUILD_PCRE2GREP "" OFF)
	set(TMP_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
	set(BUILD_SHARED_LIBS OFF
		CACHE BOOL "" FORCE)
	
	add_subdirectory("${CMAKE_SOURCE_DIR}/dependencies/PCRE2")

	set(BUILD_SHARED_LIBS ${TMP_BUILD_SHARED_LIBS}
		CACHE BOOL "" FORCE)

	target_link_libraries("external" "pcre2-16")
elseif(${BIA_REGEX_BACKEND} STREQUAL "std::regex")

else()
endif()

# Big integer dependency
set(BIA_BIG_INT_BACKEND "MPIR"
	CACHE STRING "The big integer backend that should be used for the default integers in Bia.")
set_property(CACHE BIA_BIG_INT_BACKEND
	PROPERTY STRINGS "MPIR" "none")

if(${BIA_BIG_INT_BACKEND} STREQUAL "MPIR")

else()

endif()

# String encoding conversion dependency
set(BIA_STRING_ENCODING_BACKEND "ICU"
	CACHE STRING "The library that should be used for encoding conversion of strings.")
set_property(CACHE BIA_STRING_ENCODING_BACKEND
	PROPERTY STRINGS "ICU" "none")

if(${BIA_STRING_ENCODING_BACKEND} STREQUAL "ICU")
	include(FindICU)
	find_package(ICU COMPONENTS io i18n)

	if(ICU_FOUND)
		target_link_libraries("external" ${ICU_LIBRARIES})
	else()
		message("ICU was not found")

		#require_submodule_lib("icu")

		# Compile
	endif()
else()
endif()

# String formating dependency
set(BIA_STRING_FORMATTING_BACKEND "{fmt}"
	CACHE STRING "The library that should be used for string formatting.")
set_property(CACHE BIA_STRING_FORMATTING_BACKEND
	PROPERTY STRINGS "{fmt}" "none")

if(${BIA_STRING_ENCODING_BACKEND} STREQUAL "{fmt}")
else()
endif()

file(GLOB EXTERNAL_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library("external" ${EXTERNAL_SOURCE_FILES})

if(BUILD_TESTS)
	add_subdirectory("tests")
endif()