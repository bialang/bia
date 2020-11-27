#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

using namespace bia::tokenizer::token;

inline error_info decl_stmt_signature(parameter& param)
{
	const auto old = param.backup();
	if (parse::any_of(param, "mut").second && !parse::eat_whitespaces(param)) {
		param.bundle.add({ token::keyword::mut });
	} else {
		param.restore(old);
	}
	return parse::identifier(param);
}

error_info parse::decl_stmt(parameter& param)
{
	if (!any_of(param, "let").second) {
	}
	if (const auto err = eat_whitespaces(param)) {
		return err;
	}
	if (const auto err = decl_stmt_signature(param)) {
		return err;
	}
	eat_whitespaces(param);
	if (param.encoder.read(param.input) != '=') {
	}
	eat_whitespaces(param);
	return multi_expression(param);
}
