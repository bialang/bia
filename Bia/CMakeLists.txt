#cmake_minimum_required(VERSION 3.1)

set(Bia_HEADER_FILES "config.hpp" "utf8.h")
set(Bia_SOURCE_FILES "")

# compiler namespace
set(Bia_HEADER_FILES_COMPILER "compiler.hpp" "constant_operation.hpp" "temp_counter.hpp")
set(Bia_SOURCE_FILES_COMPILER "compiler.cpp")

source_group("Header Files\\compiler" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\compiler" FILES ${Bia_SOURCE_FILES_COMPILER})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_COMPILER})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_COMPILER})


# exception namespace
set(Bia_HEADER_FILES_EXCEPTION "exception.hpp")

source_group("Header Files\\exception" FILES ${Bia_HEADER_FILES_EXCEPTION})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_EXCEPTION})


# force namespace
set(Bia_HEADER_FILES_FORCE "biaInitiator.hpp" "disguised_caller.hpp")

source_group("Header Files\\force" FILES ${Bia_HEADER_FILES_FORCE})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FORCE})


# framework namespace
set(Bia_HEADER_FILES_FRAMEWORK "create_member.hpp" "member.hpp" "biaNamespace.hpp" "operator.hpp" "undefined_member.hpp")
set(Bia_SOURCE_FILES_FRAMEWORK "biaNamespace.cpp" "undefined_member.cpp")

source_group("Header Files\\framework" FILES ${Bia_HEADER_FILES_FRAMEWORK})
source_group("Source Files\\framework" FILES ${Bia_SOURCE_FILES_FRAMEWORK})

set(Bia_HEADER_FILES_EXECUTABLE "biaFunction.hpp" "biaStaticFunction.hpp" "biaMemberFunction.hpp" "biaLambdaFunction.hpp")

source_group("Header Files\\framework\\executable" FILES ${Bia_HEADER_FILES_EXECUTABLE})

set(Bia_HEADER_FILES_NATIVE "biaCString.hpp" "native_member.hpp" "biaNativeOperator.hpp" "biaNativeReference.hpp" "biaNativeTestOperator.hpp" "native_type.hpp" "native_variable.hpp")
set(Bia_SOURCE_FILES_NATIVE "biaCString.cpp")

source_group("Header Files\\framework\\native" FILES ${Bia_HEADER_FILES_NATIVE})
source_group("Source Files\\framework\\native" FILES ${Bia_SOURCE_FILES_NATIVE})

set(Bia_HEADER_FILES_OBJECT "biaClass.hpp" "biaClassMemberHolder.hpp" "biaClassRaw.hpp" "biaClassTemplate.hpp")

source_group("Header Files\\framework\\object" FILES ${Bia_HEADER_FILES_OBJECT})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FRAMEWORK} ${Bia_HEADER_FILES_EXECUTABLE} ${Bia_HEADER_FILES_NATIVE} ${Bia_HEADER_FILES_OBJECT})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_FRAMEWORK} ${Bia_SOURCE_FILES_NATIVE})


# grammar namespace
set(Bia_HEADER_FILES_GRAMMAR "interpreter.hpp" "interpreter_ids.hpp" "interpreter_rule.hpp" "interpreter_strings.hpp" "interpreter_tokens.hpp" "report_bundle.hpp" "syntax.hpp")
set(Bia_SOURCE_FILES_GRAMMAR "interpreter.cpp" "interpreter_rule.cpp" "syntax.cpp")

source_group("Header Files\\grammar" FILES ${Bia_HEADER_FILES_GRAMMAR})
source_group("Source Files\\grammar" FILES ${Bia_SOURCE_FILES_GRAMMAR})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_GRAMMAR})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_GRAMMAR})


# machine namespace
set(Bia_HEADER_FILES_MACHINE "allocator.hpp" "machine_code.hpp" "machine_context.hpp" "machine_schein.hpp" "name_manager.hpp" "biaTemporaryStorage.hpp" "biaVariableHandler.hpp")
set(Bia_SOURCE_FILES_MACHINE "allocator.cpp" "machine_code.cpp" "machine_context.cpp" "machine_schein.cpp" "name_manager.cpp")

source_group("Header Files\\machine" FILES ${Bia_HEADER_FILES_MACHINE})
source_group("Source Files\\machine" FILES ${Bia_SOURCE_FILES_MACHINE})

set(Bia_HEADER_FILES_DISASSEMBLER "biaMachineDecoder.hpp")
set(Bia_SOURCE_FILES_DISASSEMBLER "biaMachineDecoder.cpp")

source_group("Header Files\\machine\\disassembler" FILES ${Bia_HEADER_FILES_DISASSEMBLER})
source_group("Source Files\\machine\\disassembler" FILES ${Bia_SOURCE_FILES_DISASSEMBLER})

set(Bia_HEADER_FILES_LINK "biaInstantiate.hpp" "biaLink.hpp" "biaOperator.hpp" "print.hpp")
set(Bia_SOURCE_FILES_LINK "biaInstantiate.cpp" "biaOperator.cpp")

source_group("Header Files\\machine\\link" FILES ${Bia_HEADER_FILES_LINK})
source_group("Source Files\\machine\\link" FILES ${Bia_SOURCE_FILES_LINK})

set(Bia_HEADER_FILES_MODULAR "biaModule.hpp" "biaModuleHandler.hpp")
set(Bia_SOURCE_FILES_MODULAR "biaModule.cpp")

source_group("Header Files\\machine\\modular" FILES ${Bia_HEADER_FILES_MODULAR})
source_group("Source Files\\machine\\modular" FILES ${Bia_SOURCE_FILES_MODULAR})

set(Bia_HEADER_FILES_PLATFORM "architecture.hpp" "toolset.hpp")

source_group("Header Files\\machine\\platform" FILES ${Bia_HEADER_FILES_PLATFORM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_MACHINE} ${Bia_HEADER_FILES_DISASSEMBLER} ${Bia_HEADER_FILES_LINK} ${Bia_HEADER_FILES_MODULAR} ${Bia_HEADER_FILES_PLATFORM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_MACHINE} ${Bia_SOURCE_FILES_DISASSEMBLER} ${Bia_SOURCE_FILES_LINK} ${Bia_SOURCE_FILES_MODULAR})

# stream namespace
set(Bia_HEADER_FILES_STREAM "output_stream.hpp" "output_stream_buffer.hpp")
set(Bia_SOURCE_FILES_STREAM "output_stream_buffer.cpp")

source_group("Header Files\\stream" FILES ${Bia_HEADER_FILES_STREAM})
source_group("Source Files\\stream" FILES ${Bia_SOURCE_FILES_STREAM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_STREAM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_STREAM})


# utility namespace
set(Bia_HEADER_FILES_UTILITY "hasher.hpp" "type_traits.hpp")

source_group("Header Files\\utility" FILES ${Bia_HEADER_FILES_UTILITY})
 
 set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_UTILITY})
 
 # Add library
 add_library(Bia ${Bia_HEADER_FILES} ${Bia_SOURCE_FILES})