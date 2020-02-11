#ifndef BIA_TOKENIZER_BIA_LEXER_HPP_
#define BIA_TOKENIZER_BIA_LEXER_HPP_

#include "lexer.hpp"

namespace bia {
namespace tokenizer {

class bia_lexer : public lexer
{
public:
	void lex(std::istream& input, string::encoding::encoder& encoder,
	                 token_receiver& receiver) const override;
private:
};

} // namespace tokenizer
} // namespace bia

#endif