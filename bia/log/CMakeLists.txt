project(log
	LANGUAGES CXX)

option(BIA_LOG_ENABLE_LOGGING "Whether the Bia library should make internal logs to the default logger." OFF)

if(BIA_LOG_ENABLE_LOGGING)
	set(BIA_LOG_NAME "bialang-logger" CACHE STRING "The name of the default logger.")
	set(BIA_LOG_PATTERN "[%T.%e | %=5t | %-20s at %-3# (%-20!)] [%n: %^%8l%$]\\n\\t%v" CACHE STRING "The defaul logging pattern. For more information look here: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags")
endif()

create_library(STATIC)