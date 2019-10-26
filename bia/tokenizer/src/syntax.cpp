#include <tokenizer/lexer_token/calling_token.hpp>
#include <tokenizer/rule.hpp>
#include <tokenizer/syntax.hpp>

namespace bia {
namespace tokenizer {

class syntax_lexer : public lexer
{
public:
	virtual void lex(stream::input_stream& input, token_receiver& receiver) const override
	{
		rule::parameter param(
			*string::encoding::encoder::get_instance(string::encoding::encoder::STANDARD_ENCODING::ASCII));

		rules[static_cast<std::size_t>(RULE_ID::ROOT)].run(input, param);
	}

	rule rules[rule_id_count];
};

std::unique_ptr<lexer> syntax::default_lexer;

void syntax::initialize()
{
	using namespace lexer_token;

	auto lx  = new syntax_lexer();
	auto set = [&](RULE_ID id, rule::flag_type flags, std::initializer_list<rule::rule_function_type> steps) {
		lx->rules[static_cast<std::size_t>(id)] = rule(id, flags, steps);
	};

	// set rules
	set(RULE_ID::ROOT, rule::F_OR, { calling_token });

	default_lexer.reset(lx);
}

void syntax::finalize()
{
	default_lexer = nullptr;
}

const lexer& syntax::default_syntax() noexcept
{
	return *default_lexer.get();
}

} // namespace tokenizer
} // namespace bia