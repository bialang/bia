project("util"
		LANGUAGES CXX)

set(BIA_UTIL_CONTRACT_BEHAVIOR "abort" CACHE STRING "How a contract violation should end (throw, abort, nothing).")
set_property(CACHE BIA_UTIL_CONTRACT_BEHAVIOR PROPERTY STRINGS "throw" "abort" "nothing")

if(${STREQUAL} STREQUAL "throw")
	set(BIA_UTIL_CONTRACT_BEHAVIOR_THROW ON)
elseif(${if(${STREQUAL} STREQUAL "abort")
	set(BIA_UTIL_CONTRACT_BEHAVIOR_ABORT ON)
else()
	set(BIA_UTIL_CONTRACT_BEHAVIOR_NOTHING ON)
endif()

create_library(INTERFACE
	INTERFACE "exception")