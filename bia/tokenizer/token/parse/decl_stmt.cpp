#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline Error_info decl_stmt_signature(Parameter& param)
{
	auto old          = param.backup();
	const auto ranger = param.begin_range();
	if (parse::any_of(param, "mut").second && !parse::spacer(param)) {
		param.bundle.emplace_back(Token::Keyword::mut, ranger.range());
	} else {
		param.restore(old);
	}
	if (const auto err = parse::identifier(param)) {
		return err;
	}
	parse::spacer(param);
	old = param.backup();
	if (const auto err = parse::type_definition(param)) {
		param.set_optional_error(err);
		param.restore(old);
	}
	return {};
}

Error_info parse::decl_stmt(Parameter& param)
{
	auto ranger = param.begin_range();
	if (!any_of(param, "let").second || spacer(param)) {
		return param.make_error(error::Code::expected_let, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::let, ranger.range());

	if (const auto err = decl_stmt_signature(param)) {
		return err;
	}
	while (true) {
		const auto old = param.backup();
		spacer(param);
		ranger = param.begin_range();
		if (param.reader.read() == ',') {
			param.bundle.emplace_back(Token::Control::comma, ranger.range());
			spacer(param);
			if (const auto err = decl_stmt_signature(param)) {
				return err;
			}
		} else {
			param.restore(old);
			break;
		}
	}

	const auto old = param.backup();
	spacer(param);
	ranger = param.begin_range();
	if (param.reader.read() == '=') {
		param.bundle.emplace_back(Operator::assign, ranger.range());
		spacer(param);
		return multi_expression(param);
	}
	param.restore(old);
	return {};
}

Error_info parse::drop_stmt(Parameter& param)
{
	auto ranger = param.begin_range();
	if (!any_of(param, "drop").second || spacer(param)) {
		return param.make_error(error::Code::expected_drop, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::drop, ranger.range());
	if (const auto err = identifier(param)) {
		return err;
	}
	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (param.reader.read() == ',') {
			spacer(param);
			if (const auto err = identifier(param)) {
				return err;
			}
		} else {
			param.restore(old);
			break;
		}
	}
	return {};
}
