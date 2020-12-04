#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../error_info.hpp"
#include "../parameter.hpp"

#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

typedef error_info(*token_type)(parameter&);

error_info spacer(parameter& param);

error_info root(parameter& param);
error_info batch(parameter& param);

error_info identifier(parameter& param);
error_info string(parameter& param);
error_info regex(parameter& param);
error_info number(parameter& param);

error_info return_stmt(parameter& param);
error_info yield_stmt(parameter& param);
error_info import_stmt(parameter& param);
error_info flow_control_stmt(parameter& param);
error_info defer_stmt(parameter& param);

error_info decl_stmt(parameter& param);
error_info drop_stmt(parameter& param);

error_info if_stmt(parameter& param);
error_info else_if_stmt(parameter& param);
error_info else_stmt(parameter& param);
error_info scope_stmt(parameter& param);

error_info multi_expression(parameter& param);
error_info single_expression(parameter& param);
error_info value(parameter& param);

error_info member_access(parameter& param);
error_info member_invocation(parameter& param);
error_info member_subscript(parameter& param);

error_info type_stmt(parameter& param);
error_info type_definition(parameter& param);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
