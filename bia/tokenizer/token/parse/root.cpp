#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline Error_info small_stmt(Parameter& param)
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

inline Error_info compound_stmt(Parameter& param)
{
	return parse::any_of(param, parse::if_stmt, parse::scope_stmt);
}

Error_info parse::root(Parameter& param)
{
	if (const auto err = parse::any_of(param, small_stmt, compound_stmt)) {
		return err;
	}
	param.bundle.emplace_back(Token::Control::cmd_end);
	return {};
}

Error_info parse::batch(Parameter& param)
{
	if (param.encoder.read(param.input) != '{') {
		return param.make_error(error::Code::expected_opening_curly_bracket, -1);
	}
	Token::Batch info{};
	const auto index = param.bundle.size();
	param.bundle.emplace_back();

	Error_info root_err{};
	while (true) {
		spacer(param);
		const auto old = param.backup();
		if ((root_err = root(param))) {
			param.restore(old);
			break;
		}
		++info.statement_count;
	}

	if (param.encoder.read(param.input) != '}') {
		const auto err = param.make_error(error::Code::expected_closing_curly_bracket, -1);
		return err < root_err ? root_err : err;
	}
	param.bundle.at(index).value.emplace<Token::Batch>(info);
	return {};
}
