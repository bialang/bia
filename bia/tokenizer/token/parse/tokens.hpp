#ifndef BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_TOKENS_HPP_

#include "../parameter.hpp"

#include <bia/error/bia_error.hpp>
#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

typedef error::Bia(*token_type)(Parameter&);

error::Bia spacer(Parameter& param);

error::Bia root(Parameter& param);
error::Bia batch(Parameter& param);
error::Bia scope_stmt(Parameter& param);

error::Bia identifier(Parameter& param);
error::Bia string(Parameter& param);
error::Bia regex(Parameter& param);
error::Bia number(Parameter& param);

error::Bia return_stmt(Parameter& param);
error::Bia yield_stmt(Parameter& param);
error::Bia import_stmt(Parameter& param);
error::Bia flow_control_stmt(Parameter& param);
error::Bia defer_stmt(Parameter& param);

error::Bia decl_stmt(Parameter& param);
error::Bia assign_stmt(Parameter& param);
error::Bia drop_stmt(Parameter& param);

error::Bia if_stmt(Parameter& param);
error::Bia else_if_stmt(Parameter& param);
error::Bia else_stmt(Parameter& param);

error::Bia while_stmt(Parameter& param);

error::Bia multi_expression(Parameter& param);
error::Bia single_expression(Parameter& param);
error::Bia value(Parameter& param);

error::Bia member_access(Parameter& param);
error::Bia member_invocation(Parameter& param);
error::Bia member_subscript(Parameter& param);

error::Bia type_stmt(Parameter& param);
error::Bia type_definition(Parameter& param);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
