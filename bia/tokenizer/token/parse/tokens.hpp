#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../error_info.hpp"
#include "../parameter.hpp"

#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

typedef Error_info (*token_type)(Parameter&);

Error_info spacer(Parameter& param);
bool is_spacing_character(string::encoding::Code_point cp) noexcept;

Error_info root(Parameter& param);
Error_info batch(Parameter& param);
Error_info scope_stmt(Parameter& param);

Error_info identifier(Parameter& param);
Error_info string(Parameter& param);
Error_info regex(Parameter& param);
Error_info number(Parameter& param);

Error_info return_stmt(Parameter& param);
Error_info yield_stmt(Parameter& param);
Error_info import_stmt(Parameter& param);
Error_info flow_control_stmt(Parameter& param);
Error_info defer_stmt(Parameter& param);

Error_info decl_stmt(Parameter& param);
Error_info assign_stmt(Parameter& param);
Error_info drop_stmt(Parameter& param);

Error_info if_stmt(Parameter& param);
Error_info else_if_stmt(Parameter& param);
Error_info else_stmt(Parameter& param);

Error_info while_stmt(Parameter& param);

Error_info multi_expression(Parameter& param);
Error_info single_expression(Parameter& param);
Error_info value(Parameter& param);

Error_info member_access(Parameter& param);
Error_info member_invocation(Parameter& param);
Error_info member_subscript(Parameter& param);

Error_info type_stmt(Parameter& param);
Error_info type_definition(Parameter& param);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
