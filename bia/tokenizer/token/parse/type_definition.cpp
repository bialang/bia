#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

using namespace bia::tokenizer::token;

error_info chained_type(parameter& param);

inline error_info tuple_type(parameter& param)
{
	if (param.encoder.read(param.input) != '(') {
		return param.make_error(bia::error::code::bad_tuple, -1);
	}
	param.bundle.add({ token::control::bracket_open });
	parse::eat_whitespaces(param);
	if (const auto err = chained_type(param)) {
		return err;
	}
	parse::eat_whitespaces(param);

	for (auto first = true; true; first = false) {
		auto old = param.backup();
		if (param.encoder.read(param.input) != ',') {
			param.restore(old);
			break;
		}
		param.bundle.add({ token::control::comma });

		parse::eat_whitespaces(param);
		old = param.backup();
		if (const auto err = chained_type(param)) {
			if (first) {
				param.restore(old);
				break;
			}
			return err;
		}
		parse::eat_whitespaces(param);
	}

	if (param.encoder.read(param.input) != ')') {
		return param.make_error(bia::error::code::bad_tuple, -1);
	}
	param.bundle.add({ token::control::bracket_close });
	return {};
}

inline error_info single_type(parameter& param)
{
	token::array_dimension array{};
	while (true) {
		const auto old = param.backup();
		if (!parse::any_of(param, "[]").second) {
			param.restore(old);
			break;
		}
		++array.dimension;
	}
	param.bundle.add({ array });
	return parse::any_of(param, parse::identifier, tuple_type);
}

inline error_info type(parameter& param)
{
	return parse::any_of(param, tuple_type, single_type);
}

inline error_info chained_type(parameter& param)
{
	if (const auto err = type(param)) {
		return err;
	}

	while (true) {
		const auto old = param.backup();
		parse::eat_whitespaces(param);
		if (param.encoder.read(param.input) != '|') {
			param.restore(old);
			break;
		}
		parse::eat_whitespaces(param);
		if (const auto err = type(param)) {
			return err;
		}
	}
	return {};
}

error_info parse::type_stmt(parameter& param)
{
	if (!any_of(param, "type").second) {
		return param.make_error(error::code::expected_declaration_statement, -1);
	}
	param.bundle.add(token{ token::keyword::type });
	if (const auto err = eat_whitespaces(param)) {
		return err;
	}

	if (const auto err = identifier(param)) {
		return err;
	}
	eat_whitespaces(param);

	if (param.encoder.read(param.input) != '=') {
		return param.make_error(error::code::expected_assignment, -1);
	}
	eat_whitespaces(param);
	return chained_type(param);
}

error_info parse::type_definition(parameter& param)
{
	if (!any_of(param, ":").second) {
		return param.make_error(error::code::expected_declaration_statement, -1);
	}
	param.bundle.add(token{ token::control::type_definition });
	eat_whitespaces(param);
	if (const auto err = chained_type(param)) {
		return err;
	}
	return {};
}
