#ifndef BIA_TOKENIZER_LEXER_HPP_
#define BIA_TOKENIZER_LEXER_HPP_

#include "token/receiver.hpp"

#include <bia/string/encoding/encoder.hpp>
#include <istream>

namespace bia {
namespace tokenizer {

class Lexer
{
public:
	virtual ~Lexer()                            = default;
	virtual void lex(std::istream& input, string::encoding::Encoder& encoder,
	                 token::Receiver& receiver) = 0;
};

} // namespace tokenizer
} // namespace bia

#endif
