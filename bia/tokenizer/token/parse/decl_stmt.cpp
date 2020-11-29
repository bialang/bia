#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline error_info decl_stmt_signature(parameter& param)
{
	const auto old = param.backup();
	if (parse::any_of(param, "mut").second && !parse::spacer(param)) {
		param.bundle.emplace_back(token::keyword::mut);
	} else {
		param.restore(old);
	}
	return parse::identifier(param);
}

error_info parse::decl_stmt(parameter& param)
{
	if (!any_of(param, "let").second) {
		return param.
	}
	if (const auto err = spacer(param)) {
		return err;
	}
	if (const auto err = decl_stmt_signature(param)) {
		return err;
	}
	spacer(param);
	if (param.encoder.read(param.input) != '=') {
	}
	spacer(param);
	return multi_expression(param);
}
