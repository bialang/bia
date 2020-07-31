cmake_minimum_required(VERSION 3.1)

option(BIA_LOG_ENABLE_LOGGING "Whether the Bia library should make internal logs to the default logger." OFF)

if(BIA_LOG_ENABLE_LOGGING)
	set(BIA_DEPENDENCY_spdlog TRUE PARENT_SCOPE)
	set(BIA_LOG_NAME "bialang-logger"
		CACHE STRING "The name of the default logger.")
	set(BIA_LOG_PATTERN "[%T.%e | %n | %t | %^%l%$ ] %@@%!\\n\t%v"
		CACHE STRING "The defaul logging pattern. For more information look here: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags")
	set(BIA_LOG_LEVEL "INFO"
		CACHE STRING "The logging level (CIRITICAL, ERROR, WARN, INFO, DEBUG, TRACE)")
	set_property(CACHE BIA_LOG_LEVEL
		PROPERTY STRINGS "CRITICAL" "ERROR" "WARN" "INFO" "DEBUG" "TRACE")
endif()

create_library("${CMAKE_CURRENT_SOURCE_DIR}")
