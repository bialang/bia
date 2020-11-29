#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

error_info parse::if_stmt(parameter& param)
{
	if (!any_of(param, "if").second) {
	}
	eat_whitespaces(param);
	if (const auto err = single_expression(param)) {
		return err;
	}
	if (const auto err = batch(param)) {
		return err;
	}
	
	while (true) {
		const auto old = param.backup();
		if (else_if_stmt(param)) {
			param.restore(old);
			break;
		}
	}

	const auto old = param.backup();
	if (else_stmt(param)) {
		param.restore(old);
	}
	return {};
}
