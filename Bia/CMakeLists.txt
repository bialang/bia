cmake_minimum_required(VERSION 3.1)

set(Bia_HEADER_FILES "bia.hpp" "config.hpp" "internal_config.hpp")
set(Bia_SOURCE_FILES "")

# common namespace
set(Bia_HEADER_FILES_COMMON "member_names.hpp")
set(Bia_SOURCE_FILES_COMMON "member_names.cpp")

source_group("Header Files\\common" FILES ${Bia_HEADER_FILES_COMMON})
source_group("Source Files\\common" FILES ${Bia_SOURCE_FILES_COMMON})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_COMMON})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_COMMON})

# compiler namespace
set(Bia_HEADER_FILES_COMPILER "compile_compare_operation.hpp" "compile_normal_operation.hpp" "compiler.hpp" "compiler_loop_tracker.hpp" "compiler_value.hpp" "constant_operation.hpp" "scope_handler.hpp" "temp_counter.hpp")
set(Bia_SOURCE_FILES_COMPILER "compiler.cpp" "compiler_loop_tracker.cpp" "scope_handler.cpp")

source_group("Header Files\\compiler" FILES ${Bia_HEADER_FILES_COMPILER})
source_group("Source Files\\compiler" FILES ${Bia_SOURCE_FILES_COMPILER})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_COMPILER})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_COMPILER})

# dependency namespace
set(Bia_HEADER_FILES_DEPENDENCY "big_int.hpp" "regex.hpp")
set(Bia_SOURCE_FILES_DEPENDENCY "big_int.cpp" "regex.cpp")

source_group("Header Files\\dependency" FILES ${Bia_HEADER_FILES_DEPENDENCY})
source_group("Source Files\\dependency" FILES ${Bia_SOURCE_FILES_DEPENDENCY})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_DEPENDENCY})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_DEPENDENCY})

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
set(Bia_HEADER_FILES_FORCE "disguised_caller.hpp" "disguised_caller_def.hpp" "initiator.hpp")

source_group("Header Files\\force" FILES ${Bia_HEADER_FILES_FORCE})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FORCE})


# framework namespace
set(Bia_HEADER_FILES_FRAMEWORK "create_member.hpp" "custom_member.hpp" "max_member_size.hpp" "member.hpp" "member_cast_type.hpp" "operator.hpp" "undefined_member.hpp")
set(Bia_SOURCE_FILES_FRAMEWORK "undefined_member.cpp")

source_group("Header Files\\framework" FILES ${Bia_HEADER_FILES_FRAMEWORK})
source_group("Source Files\\framework" FILES ${Bia_SOURCE_FILES_FRAMEWORK})

set(Bia_HEADER_FILES_EXECUTABLE "function.hpp" "lambda_function.hpp" "lambda_function_def.hpp" "member_function.hpp" "member_function_def.hpp" "static_function.hpp")

source_group("Header Files\\framework\\executable" FILES ${Bia_HEADER_FILES_EXECUTABLE})

set(Bia_HEADER_FILES_NATIVE "big_int_member.hpp" "cstring_member.hpp" "double_member.hpp" "int_member.hpp" "native_operator.hpp" "native_test_operator.hpp" "native_variable.hpp" "regex_member.hpp")
set(Bia_SOURCE_FILES_NATIVE "big_int_member.cpp" "double_member.cpp" "int_member.cpp" "regex_member.cpp")

source_group("Header Files\\framework\\native" FILES ${Bia_HEADER_FILES_NATIVE})
source_group("Source Files\\framework\\native" FILES ${Bia_SOURCE_FILES_NATIVE})

set(Bia_HEADER_FILES_OBJECT "class_template.hpp" "class_template_def.hpp" "constructor_chain.hpp" "instance_holder.hpp" "instance_holder_def.hpp" "member_map.hpp" "member_map_def.hpp" "namespace_member.hpp" "object.hpp" "object_def.hpp" "object_variable.hpp" "raw_object.hpp" "raw_object_def.hpp" "template_wrapper.hpp")
set(Bia_SOURCE_FILES_OBJECT "member_map.cpp" "namespace_member.cpp")

source_group("Header Files\\framework\\object" FILES ${Bia_HEADER_FILES_OBJECT})
source_group("Source Files\\framework\\object" FILES ${Bia_SOURCE_FILES_OBJECT})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_FRAMEWORK} ${Bia_HEADER_FILES_EXECUTABLE} ${Bia_HEADER_FILES_NATIVE} ${Bia_HEADER_FILES_OBJECT})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_FRAMEWORK} ${Bia_SOURCE_FILES_NATIVE} ${Bia_SOURCE_FILES_OBJECT})


# grammar namespace
set(Bia_HEADER_FILES_GRAMMAR "grammar_id.hpp" "grammar_rule.hpp" "keyword.hpp" "lexer.hpp" "lexer_token.hpp" "report.hpp" "report_bundle.hpp" "syntax.hpp")
set(Bia_SOURCE_FILES_GRAMMAR "grammar_rule.cpp" "lexer.cpp" "lexer_token.cpp" "syntax.cpp")

source_group("Header Files\\grammar" FILES ${Bia_HEADER_FILES_GRAMMAR})
source_group("Source Files\\grammar" FILES ${Bia_SOURCE_FILES_GRAMMAR})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_GRAMMAR})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_GRAMMAR})


# machine namespace
set(Bia_HEADER_FILES_MACHINE "code.hpp" "disassembler.hpp" "machine_context.hpp" "member_array.hpp" "name_manager.hpp" "schein.hpp" "script_map.hpp" "string_resource.hpp" "stack.hpp" "string_manager.hpp" "variable_index.hpp")
set(Bia_SOURCE_FILES_MACHINE "disassembler.cpp" "machine_context.cpp" "member_array.cpp" "name_manager.cpp" "schein.cpp" "script_map.cpp" "string_manager.cpp" "variable_index.cpp")

source_group("Header Files\\machine" FILES ${Bia_HEADER_FILES_MACHINE})
source_group("Source Files\\machine" FILES ${Bia_SOURCE_FILES_MACHINE})

set(Bia_HEADER_FILES_LINK "instantiate.hpp" "link.hpp" "operation.hpp" "print.hpp")
set(Bia_SOURCE_FILES_LINK "instantiate.cpp" "operation.cpp")

source_group("Header Files\\machine\\link" FILES ${Bia_HEADER_FILES_LINK})
source_group("Source Files\\machine\\link" FILES ${Bia_SOURCE_FILES_LINK})

set(Bia_HEADER_FILES_MEMORY "allocator.hpp" "big_int_allocator.hpp" "executable_allocator.hpp" "member_allocator.hpp" "simple_allocator.hpp" "stl_allocator_wrapper.hpp")
set(Bia_SOURCE_FILES_MEMORY "big_int_allocator.cpp" "simple_allocator.cpp")

source_group("Header Files\\machine\\memory" FILES ${Bia_HEADER_FILES_MEMORY})
source_group("Source Files\\machine\\memory" FILES ${Bia_SOURCE_FILES_MEMORY})

set(Bia_HEADER_FILES_MODULAR "module_library.hpp" "module_loader.hpp")
set(Bia_SOURCE_FILES_MODULAR "module_loader.cpp")

source_group("Header Files\\machine\\modular" FILES ${Bia_HEADER_FILES_MODULAR})
source_group("Source Files\\machine\\modular" FILES ${Bia_SOURCE_FILES_MODULAR})

set(Bia_HEADER_FILES_PLATFORM "architecture.hpp" "architecture_utils.hpp" "machine_code.hpp" "machine_schein.hpp" "member_passer.hpp" "passer.hpp" "static_passer.hpp" "varg_member_passer.hpp" "x86_translator.hpp")
set(Bia_SOURCE_FILES_PLATFORM "machine_code.cpp")

source_group("Header Files\\machine\\platform" FILES ${Bia_HEADER_FILES_PLATFORM})
source_group("Source Files\\machine\\platform" FILES ${Bia_SOURCE_FILES_PLATFORM})

set(Bia_HEADER_FILES_VIRTUAL_MACHINE "op_code.hpp" "virtual_disassembler.hpp" "virtual_machine_code.hpp" "virtual_machine_schein.hpp" "virtual_translator.hpp")
set(Bia_SOURCE_FILES_VIRTUAL_MACHINE "virtual_disassembler.cpp" "virtual_machine_code.cpp" "virtual_machine_schein.cpp" "virtual_translator.cpp")

source_group("Header Files\\machine\\virtual_machine" FILES ${Bia_HEADER_FILES_VIRTUAL_MACHINE})
source_group("Source Files\\machine\\virtual_machine" FILES ${Bia_SOURCE_FILES_VIRTUAL_MACHINE})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_MACHINE} ${Bia_HEADER_FILES_LINK} ${Bia_HEADER_FILES_MEMORY} ${Bia_HEADER_FILES_MODULAR} ${Bia_HEADER_FILES_PLATFORM} ${Bia_HEADER_FILES_VIRTUAL_MACHINE})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_MACHINE} ${Bia_SOURCE_FILES_LINK} ${Bia_SOURCE_FILES_MEMORY} ${Bia_SOURCE_FILES_MODULAR} ${Bia_SOURCE_FILES_PLATFORM} ${Bia_SOURCE_FILES_VIRTUAL_MACHINE})

# stream namespace
set(Bia_HEADER_FILES_STREAM "buffer_input_stream.hpp" "buffer_output_stream.hpp" "input_stream.hpp" "output_stream.hpp" "string_stream.hpp")
set(Bia_SOURCE_FILES_STREAM "buffer_input_stream.cpp" "buffer_output_stream.cpp")

source_group("Header Files\\stream" FILES ${Bia_HEADER_FILES_STREAM})
source_group("Source Files\\stream" FILES ${Bia_SOURCE_FILES_STREAM})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_STREAM})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_STREAM})


# utility namespace
set(Bia_HEADER_FILES_UTILITY "buffer_builder.hpp" "guard.hpp" "hasher.hpp" "index_map.hpp" "local_object.hpp" "max.hpp" "scope_exit.hpp" "share.hpp" "share_def.hpp" "string_key.hpp" "type_traits.hpp" "variant.hpp")
set(Bia_SOURCE_FILES_UTILITY "scope_exit.cpp")

source_group("Header Files\\utility" FILES ${Bia_HEADER_FILES_UTILITY})
source_group("Source Files\\utility" FILES ${Bia_SOURCE_FILES_UTILITY})

set(Bia_HEADER_FILES ${Bia_HEADER_FILES} ${Bia_HEADER_FILES_UTILITY})
set(Bia_SOURCE_FILES ${Bia_SOURCE_FILES} ${Bia_SOURCE_FILES_UTILITY})


# Adding the library
add_library(Bia ${Bia_SOURCE_FILES})

add_executable(Bia_main "main.cpp")
target_link_libraries(Bia_main Bia)

target_link_libraries(Bia ${BIA_LIBRARIES})
target_include_directories(Bia PUBLIC ${BIA_INCLUDES})

# For dlopen and dlsym
if(CMAKE_DL_LIBS)
    target_link_libraries(Bia ${CMAKE_DL_LIBS})
endif()


# Install
install(TARGETS Bia DESTINATION lib)
install(FILES ${Bia_HEADER_FILES} DESTINATION "include/Bia")
