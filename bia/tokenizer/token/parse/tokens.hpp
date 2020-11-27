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

error_info identifier(parameter& param);
error_info string(parameter& param);
error_info regex(parameter& param);
error_info number(parameter& param);

error_info decl_stmt(parameter& param);

error_info multi_expression(parameter& param);
error_info single_expression(parameter& param);
error_info value(parameter& param);
error_info member(parameter& param);

error_info type_stmt(parameter& param);
error_info type_definition(parameter& param);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
