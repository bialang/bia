#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../parameter.hpp"

#include <bia/exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details value(parameter& parameter);
exception::syntax_details term(parameter& parameter);
exception::syntax_details expression(parameter& parameter);
exception::syntax_details identifier(parameter& parameter);
exception::syntax_details string(parameter& parameter);
exception::syntax_details decl_stmt(parameter& parameter);
exception::syntax_details import_stmt(parameter& parameter);
exception::syntax_details single_stmt(parameter& parameter);
/**
 * Parses for a cmd end token.
 *
 * @param[in,out] parameter the required parameters
 * @returns an error if no cmd end is found
 */
exception::syntax_details cmd_end(parameter& parameter);
exception::syntax_details while_(parameter& parameter);
exception::syntax_details for_each(parameter& parameter);
exception::syntax_details member(parameter& parameter);
exception::syntax_details operators(parameter& parameter);
exception::syntax_details regex(parameter& parameter);
exception::syntax_details parameter_list(parameter& parameter);
exception::syntax_details number(parameter& parameter);
exception::syntax_details if_(parameter& parameter);
exception::syntax_details else_(parameter& parameter);
exception::syntax_details loop_flow_control(parameter& parameter);
exception::syntax_details function(parameter& parameter);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
