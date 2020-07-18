#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

#include <bia/log/log.hpp>

bia::exception::syntax_details bia::tokenizer::token::parse::decl_stmt(parameter& parameter)
{
	// compare let
	if (const auto err = any_of(parameter, "invalid decl keyword", "let").second) {
		return err;
	}

	parameter.bundle.add(token{ token::keyword::let });

	BIA_LOG(TRACE, "matched 'let'");

	// whitespaces are required
	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched whitespace");

	if (const auto err = identifier(parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched identifier");

	// optional whitespaces
	eat_whitespaces(parameter);

	// compare '='
	const auto pos = parameter.input.tellg();

	if (parameter.encoder.read(parameter.input) != '=') {
		return { pos, "expected assignment operator" };
	}

	// optional whitespaces
	eat_whitespaces(parameter);

	// read expression
	return expression(parameter);
}

bia::exception::syntax_details bia::tokenizer::token::parse::import_stmt(parameter& parameter)
{
	// compare import
	if (const auto err = any_of(parameter, "invalid import statement", "import").second) {
		return err;
	}

	// whitespaces are required
	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	parameter.bundle.add({ token::keyword::import });

	return identifier(parameter);
}

bia::exception::syntax_details bia::tokenizer::token::parse::single_stmt(parameter& parameter)
{
	const auto old = parameter.backup();

	if (!decl_stmt(parameter)) {
		return {};
	}

	parameter.restore(old);

	if (!import_stmt(parameter)) {
		return {};
	}

	parameter.restore(old);

	if (!while_(parameter)) {
		return {};
	}

	parameter.restore(old);

	if (!if_(parameter)) {
		return {};
	}

	parameter.restore(old);

	if (!for_each(parameter)) {
		return {};
	}

	parameter.restore(old);

	return expression(parameter);
}

bia::exception::syntax_details bia::tokenizer::token::parse::cmd_end(parameter& parameter)
{
	const auto err = eat_whitespaces<true>(parameter);
	const auto pos = parameter.input.tellg();

	if (parameter.encoder.read(parameter.input) != ';') {
		parameter.input.seekg(pos);

		if (err) {
			return { pos, "expected ';' or a line feed" };
		}
	}

	// add cmd_end token; make sure its a token
	parameter.bundle.add({ token::token::cmd_end{} });

	return {};
}
