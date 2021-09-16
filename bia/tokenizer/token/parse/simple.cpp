#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia;
using namespace bia::tokenizer::token;

error::Bia parse::return_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "return").second || spacer(param)) {
		return param.make_error(error::Code::expected_return, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::return_, ranger.range());
	return multi_expression(param);
}

error::Bia parse::yield_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "yield").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::yield, ranger.range());
	return multi_expression(param);
}

error::Bia parse::import_stmt(Parameter& param)
{
	auto as_stmt = [&] {
		const auto ranger = param.begin_range();
		if (!any_of(param, "as").second || spacer(param)) {
			return param.make_error(error::Code::expected_as, ranger.range());
		}
		param.bundle.emplace_back(Token::Keyword::as, ranger.range());
		return identifier(param);
	};

	const auto ranger = param.begin_range();
	if (!any_of(param, "import").second || spacer(param)) {
		return param.make_error(error::Code::expected_import_statement, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::import, ranger.range());

	auto old = param.backup();
	if (!string(param)) {
		spacer(param);
		return as_stmt();
	}
	param.restore(old);

	if (const auto err = identifier(param)) {
		return err;
	}
	old = param.backup();
	if (spacer(param) || as_stmt()) {
		param.restore(old);
	}
	return {};
}

error::Bia parse::flow_control_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	const auto x      = any_of(param, "break", "continue");
	if (!x.second || spacer(param)) {
		return param.make_error(error::Code::expected_flow_control, ranger.range());
	}
	param.bundle.emplace_back(x.first == 0 ? Token::Keyword::break_ : Token::Keyword::continue_,
	                          ranger.range());

	const auto old = param.backup();
	if (identifier(param)) {
		param.restore(old);
	}
	return {};
}

error::Bia parse::defer_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "defer").second || spacer(param)) {
		return param.make_error(error::Code::expected_defer, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::defer, ranger.range());
	return any_of(param, single_expression, batch);
}
