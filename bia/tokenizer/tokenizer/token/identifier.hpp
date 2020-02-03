#ifndef BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_
#define BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_

#include <exception/syntax_error.hpp>
#include <istream>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details identifier(std::istream& input, string::encoding::encoder& encoder);

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif