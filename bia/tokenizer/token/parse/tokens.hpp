#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../parameter.hpp"

#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

std::error_code value(parameter& parameter);
std::error_code term(parameter& parameter);
std::error_code expression(parameter& parameter);
std::error_code identifier(parameter& parameter);
std::error_code string(parameter& parameter);
std::error_code decl_stmt(parameter& parameter);
std::error_code import_stmt(parameter& parameter);
std::error_code single_stmt(parameter& parameter);
/**
 * Parses for a cmd end token.
 *
 * @param[in,out] parameter the required parameters
 * @returns an error if no cmd end is found
 */
std::error_code cmd_end(parameter& parameter);
std::error_code while_(parameter& parameter);
std::error_code for_each(parameter& parameter);
std::error_code member(parameter& parameter);
std::error_code operators(parameter& parameter);
std::error_code regex(parameter& parameter);
std::error_code parameter_list(parameter& parameter);
std::error_code number(parameter& parameter);
std::error_code if_(parameter& parameter);
std::error_code else_(parameter& parameter);
std::error_code loop_flow_control(parameter& parameter);
std::error_code function(parameter& parameter);
std::error_code type_definition(parameter& parameter);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
