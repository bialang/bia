#ifndef BIA_TOKENZIER_TOKEN_PARSE_IDENTIFIER_HPP_
#define BIA_TOKENZIER_TOKEN_PARSE_IDENTIFIER_HPP_

#include "../parameter.hpp"

#include <bia/exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details identifier(parameter& tp);

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
