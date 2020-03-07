#ifndef BIA_TOKENIZER_LEXER_HPP_
#define BIA_TOKENIZER_LEXER_HPP_

#include "token_receiver.hpp"

#include <istream>
#include <string/encoding/encoder.hpp>
#include <util/types.hpp>

namespace bia {
namespace tokenizer {

class lexer
{
public:
	virtual ~lexer()                           = default;
	virtual void lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
	                 token_receiver& receiver) = 0;
};

} // namespace tokenizer
} // namespace bia

#endif