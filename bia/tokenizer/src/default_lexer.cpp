#include <tokenizer/default_lexer.hpp>

namespace bia {
namespace tokenizer {

default_lexer::default_lexer()
{}

void default_lexer::lex(stream::input_stream& input, token_receiver& receiver)
{
/*	rule_parameter parameter;

	rules[static_cast<int>(RULE_ID::ROOT)].run(input, parameter);*/
}

} // namespace tokenizer
} // namespace bia