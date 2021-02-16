#ifndef BIA_TOKENIZER_LEXER_HPP_
#define BIA_TOKENIZER_LEXER_HPP_

#include "reader.hpp"
#include "token/receiver.hpp"

namespace bia {
namespace tokenizer {

class Lexer
{
public:
	virtual ~Lexer()                                            = default;
	virtual void lex(Reader& reader, token::Receiver& receiver) = 0;
};

} // namespace tokenizer
} // namespace bia

#endif
