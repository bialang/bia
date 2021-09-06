#include "tokens.hpp"

using namespace bia;
using namespace bia::tokenizer::token;

error::Bia parse::regex(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (param.reader.read() != 'r') {
		return param.make_error(error::Code::expected_regex, ranger.range());
	}
	auto err = string(param);
	if (err) {
		return err;
	}
	auto memory               = param.bundle.back().value.get<Token::String>().memory;
	memory.type               = resource::Type::regex;
	param.bundle.back().value = Token::Regex{ memory };
	return {};
}
