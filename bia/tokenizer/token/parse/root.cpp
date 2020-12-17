#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline error_info small_stmt(parameter& param)
{
	if (const auto err = parse::any_of(param, parse::drop_stmt, parse::decl_stmt, parse::return_stmt,
	                                   parse::yield_stmt, parse::flow_control_stmt, parse::defer_stmt,
	                                   parse::import_stmt, parse::type_stmt, parse::single_expression)) {
		return err;
	}
	const auto old = param.backup();
	parse::spacer(param);
	if (param.encoder.read(param.input) != ';') {
		param.restore(old);
	}
	return {};
}

inline error_info compound_stmt(parameter& param)
{
	return parse::any_of(param, parse::if_stmt, parse::scope_stmt);
}

error_info parse::root(parameter& param)
{
	if (const auto err = parse::any_of(param, small_stmt, compound_stmt)) {
		return err;
	}
	param.bundle.emplace_back(token::control::cmd_end);
	return {};
}

error_info parse::batch(parameter& param)
{
	if (param.encoder.read(param.input) != '{') {
		return param.make_error(error::code::expected_opening_curly_bracket, -1);
	}
	token::batch info{};
	const auto index = param.bundle.size();
	param.bundle.emplace_back();

	error_info root_err{};
	while (true) {
		spacer(param);
		const auto old = param.backup();
		if ((root_err = root(param))) {
			param.restore(old);
			break;
		}
		++info.statement_count;
	}

	spacer(param);
	if (param.encoder.read(param.input) != '}') {
		const auto err = param.make_error(error::code::expected_closing_curly_bracket, -1);
		return err < root_err ? root_err : err;
	}
	param.bundle.at(index).value.emplace<token::batch>(info);
	return {};
}
