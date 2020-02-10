#ifndef BIA_TOKENIZER_TOKEN_KEYWORD_HPP_
#define BIA_TOKENIZER_TOKEN_KEYWORD_HPP_

#include "../resource_manager.hpp"

#include <exception/syntax_error.hpp>
#include <istream>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details keyword(const char* keyword, std::istream& input, string::encoding::encoder& encoder,
                                  resource_manager& resource_manager);

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif