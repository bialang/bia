#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../error_info.hpp"
#include "../parameter.hpp"

#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

typedef Error_info(*token_type)(parameter&);

Error_info spacer(parameter& param);

Error_info root(parameter& param);
Error_info batch(parameter& param);

Error_info identifier(parameter& param);
Error_info string(parameter& param);
Error_info regex(parameter& param);
Error_info number(parameter& param);

Error_info return_stmt(parameter& param);
Error_info yield_stmt(parameter& param);
Error_info import_stmt(parameter& param);
Error_info flow_control_stmt(parameter& param);
Error_info defer_stmt(parameter& param);

Error_info decl_stmt(parameter& param);
Error_info drop_stmt(parameter& param);

Error_info if_stmt(parameter& param);
Error_info else_if_stmt(parameter& param);
Error_info else_stmt(parameter& param);
Error_info scope_stmt(parameter& param);

Error_info multi_expression(parameter& param);
Error_info single_expression(parameter& param);
Error_info value(parameter& param);

Error_info member_access(parameter& param);
Error_info member_invocation(parameter& param);
Error_info member_subscript(parameter& param);

Error_info type_stmt(parameter& param);
Error_info type_definition(parameter& param);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
