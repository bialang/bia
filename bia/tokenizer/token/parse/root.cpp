#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia;
using namespace bia::tokenizer::token;

inline error::Bia small_stmt(Parameter& param)
{
	if (const auto err =
	      parse::any_of(param, parse::drop_stmt, parse::decl_stmt, parse::assign_stmt, parse::return_stmt,
	                    parse::yield_stmt, parse::flow_control_stmt, parse::defer_stmt, parse::import_stmt,
	                    parse::type_stmt, parse::single_expression)) {
		return err;
	}
	const auto old = param.backup();
	parse::spacer(param);
	if (param.reader.read() != ';') {
		param.restore(old);
	}
	return {};
}

inline error::Bia compound_stmt(Parameter& param)
{
	return parse::any_of(param, parse::if_stmt, parse::while_stmt, parse::scope_stmt);
}

error::Bia parse::root(Parameter& param)
{
	if (const auto err = parse::any_of(param, small_stmt, compound_stmt)) {
		return err;
	}
	param.bundle.emplace_back(Token::Control::cmd_end, param.begin_range().range());
	return {};
}

error::Bia parse::batch(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (param.reader.read() != '{') {
		return param.make_error(error::Code::expected_opening_curly_bracket, ranger.range());
	}
	Token::Batch info{};
	const auto index = param.bundle.size();
	param.bundle.emplace_back();

	error::Bia root_err{};
	while (true) {
		spacer(param);
		const auto old = param.backup();
		if ((root_err = root(param))) {
			param.restore(old);
			break;
		}
		++info.statement_count;
	}

	const auto end_ranger = param.begin_range();
	if (param.reader.read() != '}') {
		const auto err = param.make_error(error::Code::expected_closing_curly_bracket, end_ranger.range());
		return err < root_err ? root_err : err;
	}
	param.bundle.at(index) = { info, ranger.range() };
	return {};
}
