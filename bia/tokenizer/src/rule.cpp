#include <tokenizer/rule.hpp>

namespace bia {
namespace tokenizer {

rule::rule() noexcept
{
	id	= RULE_ID::ROOT;
	flags = 0;
}

rule::rule(RULE_ID id, flag_type flags, std::initializer_list<rule_function_type> steps)
	: id(id), flags(flags), steps(steps)
{}

void rule::run(stream::input_stream& input, rule::parameter& param) const
{
	for (auto& step : steps) {
		step(input, param);
	}
}

} // namespace tokenizer
} // namespace bia