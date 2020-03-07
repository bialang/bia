#ifndef BIA_TOKENIZER_BIA_LEXER_HPP_
#define BIA_TOKENIZER_BIA_LEXER_HPP_

#include "lexer.hpp"
#include "resource_manager.hpp"

namespace bia {
namespace tokenizer {

class bia_lexer : public lexer
{
public:
	bia_lexer(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator);
	void lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
	         token_receiver& receiver) override;

private:
	resource_manager _resource_manager;
};

} // namespace tokenizer
} // namespace bia

#endif