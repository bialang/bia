#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::return_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "return").second || spacer(param)) {
		return param.make_error(error::Code::expected_return, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::return_, ranger.range());
	return multi_expression(param);
}

Error_info parse::yield_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "yield").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::yield, ranger.range());
	return multi_expression(param);
}

Error_info parse::import_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "import").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::import, ranger.range());
	return any_of(param, string, identifier);
}

Error_info parse::flow_control_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	const auto x = any_of(param, "break", "continue");
	if (!x.second || spacer(param)) {
		return param.make_error(error::Code::expected_yield, ranger.range());
	}
	param.bundle.emplace_back(x.first == 1 ? Token::Keyword::break_ : Token::Keyword::continue_, ranger.range());

	const auto old = param.backup();
	if (identifier(param)) {
		param.restore(old);
	}
	return {};
}

Error_info parse::defer_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "defer").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::defer, ranger.range());
	return any_of(param, single_expression, batch);
}
