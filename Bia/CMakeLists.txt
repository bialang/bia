cmake_minimum_required(VERSION 3.1)

set(Bia_HEADER_FILES "bia.hpp" "config.hpp" "config_cmake.hpp")
set(Bia_SOURCE_FILES "")

# compiler namespace
set(Bia_HEADER_FILES_COMPILER "compile_compare_operation.hpp" "compile_normal_operation.hpp" "compiler.hpp" "compiler_value.hpp" "constant_operation.hpp" "scope_handler.hpp" "temp_counter.hpp")
set(Bia_SOURCE_FILES_COMPILER "compiler.cpp")

source_group("Header Files\\compiler" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\compiler" FILES ${Bia_SOURCE_FILES_COMPILER})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_COMPILER})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_COMPILER})

# encoding namespace
set(Bia_HEADER_FILES_ENCODING "ascii.hpp" "encoder.hpp" "utf8.hpp" "utf32.hpp")
set(Bia_SOURCE_FILES_ENCODING "utf8.cpp" "utf32.cpp")

source_group("Header Files\\encoding" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\encoding" FILES ${Bia_SOURCE_FILES_COMPILER})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_ENCODING})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_ENCODING})


# exception namespace
set(Bia_HEADER_FILES_EXCEPTION "exception.hpp")

source_group("Header Files\\exception" FILES ${Bia_HEADER_FILES_EXCEPTION})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_EXCEPTION})


# force namespace
set(Bia_HEADER_FILES_FORCE "disguised_caller.hpp" "disguised_caller_source.hpp" "initiator.hpp")

source_group("Header Files\\force" FILES ${Bia_HEADER_FILES_FORCE})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FORCE})


# framework namespace
set(Bia_HEADER_FILES_FRAMEWORK "create_member.hpp" "custom_member.hpp" "max_member_size.hpp" "member.hpp" "operator.hpp" "undefined_member.hpp")
set(Bia_SOURCE_FILES_FRAMEWORK "undefined_member.cpp")

source_group("Header Files\\framework" FILES ${Bia_HEADER_FILES_FRAMEWORK})
source_group("Source Files\\framework" FILES ${Bia_SOURCE_FILES_FRAMEWORK})

set(Bia_HEADER_FILES_EXECUTABLE "function.hpp" "lambda_function.hpp" "member_function.hpp" "static_function.hpp")

source_group("Header Files\\framework\\executable" FILES ${Bia_HEADER_FILES_EXECUTABLE})

set(Bia_HEADER_FILES_NATIVE "cstring_member.hpp" "native_member.hpp" "native_operator.hpp" "native_reference.hpp" "native_test_operator.hpp" "native_type.hpp" "native_variable.hpp")

source_group("Header Files\\framework\\native" FILES ${Bia_HEADER_FILES_NATIVE})

set(Bia_HEADER_FILES_OBJECT "class_template.hpp" "class_template_def.hpp" "constructor_chain.hpp" "instance_holder.hpp" "member_map.hpp" "member_map_def.hpp" "namespace_member.hpp" "object.hpp" "object_def.hpp" "object_variable.hpp" "raw_object.hpp" "raw_object_def.hpp" "template_wrapper.hpp")
set(Bia_SOURCE_FILES_OBJECT "member_map.cpp" "namespace_member.cpp")

source_group("Header Files\\framework\\object" FILES ${Bia_HEADER_FILES_OBJECT})
source_group("Source Files\\framework\\object" FILES ${Bia_SOURCE_FILES_OBJECT})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FRAMEWORK} ${Bia_HEADER_FILES_EXECUTABLE} ${Bia_HEADER_FILES_NATIVE} ${Bia_HEADER_FILES_OBJECT})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_FRAMEWORK} ${Bia_SOURCE_FILES_OBJECT})


# grammar namespace
set(Bia_HEADER_FILES_GRAMMAR "interpreter.hpp" "interpreter_id.hpp" "interpreter_rule.hpp" "interpreter_string.hpp" "interpreter_token.hpp" "report.hpp" "report_bundle.hpp" "syntax.hpp")
set(Bia_SOURCE_FILES_GRAMMAR "interpreter.cpp" "interpreter_rule.cpp" "interpreter_token.cpp" "syntax.cpp")

source_group("Header Files\\grammar" FILES ${Bia_HEADER_FILES_GRAMMAR})
source_group("Source Files\\grammar" FILES ${Bia_SOURCE_FILES_GRAMMAR})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_GRAMMAR})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_GRAMMAR})


# machine namespace
set(Bia_HEADER_FILES_MACHINE "disassembler.hpp" "machine_code.hpp" "machine_context.hpp" "machine_schein.hpp" "machine_stack.hpp" "string_manager.hpp" "variable_index.hpp")
set(Bia_SOURCE_FILES_MACHINE "disassembler.cpp" "machine_code.cpp" "machine_context.cpp" "machine_schein.cpp" "machine_stack.cpp" "string_manager.cpp" "variable_index.cpp")

source_group("Header Files\\machine" FILES ${Bia_HEADER_FILES_MACHINE})
source_group("Source Files\\machine" FILES ${Bia_SOURCE_FILES_MACHINE})

set(Bia_HEADER_FILES_LINK "instantiate.hpp" "link.hpp" "operation.hpp" "print.hpp")
set(Bia_SOURCE_FILES_LINK "instantiate.cpp" "operation.cpp")

source_group("Header Files\\machine\\link" FILES ${Bia_HEADER_FILES_LINK})
source_group("Source Files\\machine\\link" FILES ${Bia_SOURCE_FILES_LINK})

set(Bia_HEADER_FILES_MEMORY "allocator.hpp" "executable_allocator.hpp" "simple_allocator.hpp" "simple_executable_allocator.hpp" "stl_allocator_wrapper.hpp")
set(Bia_SOURCE_FILES_MEMORY "simple_allocator.cpp" "simple_executable_allocator.cpp")

source_group("Header Files\\machine\\memory" FILES ${Bia_HEADER_FILES_MEMORY})
source_group("Source Files\\machine\\memory" FILES ${Bia_SOURCE_FILES_MEMORY})

set(Bia_HEADER_FILES_MODULAR "module_library.hpp" "module_loader.hpp")
set(Bia_SOURCE_FILES_MODULAR "module_loader.cpp")

source_group("Header Files\\machine\\modular" FILES ${Bia_HEADER_FILES_MODULAR})
source_group("Source Files\\machine\\modular" FILES ${Bia_SOURCE_FILES_MODULAR})

set(Bia_HEADER_FILES_PLATFORM "architecture.hpp" "architecture_utils.hpp" "member_passer.hpp" "passer.hpp" "static_passer.hpp" "toolset.hpp" "varg_member_passer.hpp")

source_group("Header Files\\machine\\platform" FILES ${Bia_HEADER_FILES_PLATFORM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_MACHINE} ${Bia_HEADER_FILES_LINK} ${Bia_HEADER_FILES_MEMORY} ${Bia_HEADER_FILES_MODULAR} ${Bia_HEADER_FILES_PLATFORM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_MACHINE} ${Bia_SOURCE_FILES_LINK} ${Bia_SOURCE_FILES_MEMORY} ${Bia_SOURCE_FILES_MODULAR})

# stream namespace
set(Bia_HEADER_FILES_STREAM "buffer_input_stream.hpp" "buffer_output_stream.hpp" "file_input_stream.hpp" "file_output_stream.hpp" "input_stream.hpp" "output_stream.hpp" "string_stream.hpp")
set(Bia_SOURCE_FILES_STREAM "buffer_input_stream.cpp" "buffer_output_stream.cpp")

source_group("Header Files\\stream" FILES ${Bia_HEADER_FILES_STREAM})
source_group("Source Files\\stream" FILES ${Bia_SOURCE_FILES_STREAM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_STREAM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_STREAM})


# utility namespace
set(Bia_HEADER_FILES_UTILITY "guard.hpp" "hasher.hpp" "share.hpp" "share_def.hpp" "string_key.hpp" "type_traits.hpp")

source_group("Header Files\\utility" FILES ${Bia_HEADER_FILES_UTILITY})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_UTILITY})

# Adding the library
if(BIA_BUILD_SHARED)
  add_library(Bia SHARED ${Bia_HEADER_FILES} ${Bia_SOURCE_FILES})
else(BIA_BUILD_SHARED)
  add_library(Bia STATIC ${Bia_HEADER_FILES} ${Bia_SOURCE_FILES})
endif(BIA_BUILD_SHARED)

# Install
install(TARGETS Bia DESTINATION lib)
install(FILES ${Bia_HEADER_FILES} DESTINATION "include/Bia")
