#ifndef BIA_TOKENIZER_BIA_LEXER_HPP_
#define BIA_TOKENIZER_BIA_LEXER_HPP_

#include "lexer.hpp"

#include <bia/resource/manager.hpp>

namespace bia {
namespace tokenizer {

class Bia_lexer : public Lexer
{
public:
	Bia_lexer(util::Not_null<std::shared_ptr<memory::Allocator>> allocator);
	error::Bia lex(Reader& reader, token::Receiver& receiver) override;

private:
	resource::Manager _manager;
};

} // namespace tokenizer
} // namespace bia

#endif
