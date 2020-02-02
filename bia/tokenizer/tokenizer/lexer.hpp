#ifndef BIA_TOKENIZER_LEXER_HPP_
#define BIA_TOKENIZER_LEXER_HPP_

#include "token_receiver.hpp"

#include <istream>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {

class lexer
{
public:
	virtual ~lexer()                                 = default;
	virtual void lex(std::istream& input, string::encoding::encoder& encoder,
	                 token_receiver& receiver) const = 0;
};

} // namespace tokenizer
} // namespace bia

#endif