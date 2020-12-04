#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline error_info decl_stmt_signature(parameter& param)
{
	auto old = param.backup();
	if (parse::any_of(param, "mut").second && !parse::spacer(param)) {
		param.bundle.emplace_back(token::keyword::mut);
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

error_info parse::decl_stmt(parameter& param)
{
	if (!any_of(param, "let").second || spacer(param)) {
		return param.make_error(error::code::expected_let);
	}
	param.bundle.emplace_back(token::keyword::let);

	if (const auto err = decl_stmt_signature(param)) {
		return err;
	}
	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (param.encoder.read(param.input) == ',') {
			param.bundle.emplace_back(token::control::comma);
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
	if (param.encoder.read(param.input) == '=') {
		param.bundle.emplace_back(operator_::assign);
		spacer(param);
		return multi_expression(param);
	}
	param.restore(old);
	return {};
}

error_info parse::drop_stmt(parameter& param)
{
	if (!any_of(param, "drop").second || spacer(param)) {
		return param.make_error(error::code::expected_drop);
	}

	if (const auto err = identifier(param)) {
		return err;
	}
	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (param.encoder.read(param.input) == ',') {
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
