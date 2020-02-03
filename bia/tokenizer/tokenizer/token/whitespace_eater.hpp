#ifndef BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_

#include <exception/syntax_error.hpp>
#include <istream>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details eat_whitespaces(std::istream& input, string::encoding::encoder& encoder);

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif