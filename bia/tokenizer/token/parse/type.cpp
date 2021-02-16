#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info chained_type(Parameter& param);

inline Error_info tuple_type(Parameter& param)
{
	auto ranger = param.begin_range();
	if (param.reader.read() != '(') {
		return param.make_error(bia::error::Code::bad_tuple, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::bracket_open, ranger.range());
	parse::spacer(param);
	if (const auto err = chained_type(param)) {
		return err;
	}
	parse::spacer(param);

	for (auto first = true; true; first = false) {
		auto old = param.backup();
		ranger = param.begin_range();
		if (param.reader.read() != ',') {
			param.restore(old);
			break;
		}
		param.bundle.emplace_back(Token::Control::comma, ranger.range());

		parse::spacer(param);
		old = param.backup();
		if (const auto err = chained_type(param)) {
			if (first) {
				param.restore(old);
				break;
			}
			return err;
		}
		parse::spacer(param);
	}

	ranger = param.begin_range();
	if (param.reader.read() != ')') {
		return param.make_error(bia::error::Code::bad_tuple, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::bracket_close, ranger.range());
	return {};
}

inline Error_info single_type(Parameter& param)
{
	Token::Array_dimension array{};
	const auto ranger = param.begin_range();
	while (true) {
		const auto old = param.backup();
		if (!parse::any_of(param, "[]").second) {
			param.restore(old);
			break;
		}
		++array.dimension;
	}
	param.bundle.emplace_back(array, ranger.range());
	return parse::any_of(param, parse::identifier, tuple_type);
}

inline Error_info type(Parameter& param)
{
	return parse::any_of(param, tuple_type, single_type);
}

inline Error_info chained_type(Parameter& param)
{
	if (const auto err = type(param)) {
		return err;
	}

	while (true) {
		const auto old = param.backup();
		parse::spacer(param);
		if (param.reader.read() != '|') {
			param.restore(old);
			break;
		}
		parse::spacer(param);
		if (const auto err = type(param)) {
			return err;
		}
	}
	return {};
}

Error_info parse::type_stmt(Parameter& param)
{
	auto ranger = param.begin_range();
	if (!any_of(param, "type").second) {
		return param.make_error(error::Code::expected_type_declaration, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::type, ranger.range());
	if (const auto err = spacer(param)) {
		return err;
	}

	if (const auto err = identifier(param)) {
		return err;
	}
	spacer(param);

	ranger = param.begin_range();
	if (param.reader.read() != '=') {
		return param.make_error(error::Code::expected_assignment, ranger.range());
	}
	spacer(param);
	return chained_type(param);
}

Error_info parse::type_definition(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, ":").second) {
		return param.make_error(error::Code::expected_type_definition, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::type_definition, ranger.range());
	spacer(param);
	if (const auto err = chained_type(param)) {
		return err;
	}
	return {};
}
