#include "any_of.hpp"
#include "batch.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

std::error_code bia::tokenizer::token::parse::for_each(parameter& parameter)
{
	if (!any_of(parameter, "for").second) {
		return error::code::bad_for_statement;
	}

	parameter.bundle.add({ token::keyword::for_ });

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = identifier(parameter)) {
		return err;
	}

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (!any_of(parameter, "in").second) {
		return error::code::expected_in;
	}

	if (const auto err = eat_whitespaces(parameter)) {
		return err;
	}

	if (const auto err = expression(parameter)) {
		return err;
	}

	// add __iter__ call
	{
		parameter.bundle.add(token{ operator_::member_access });

		auto streambuf = parameter.manager.start_memory(true);
		std::ostream output{ &streambuf };

		output << "__iter__";
		output.put(0);

		parameter.bundle.add(token{ token::identifier{ streambuf.finish(resource::type::string), false } });
	}

	eat_whitespaces(parameter);

	if (const auto err = batch(parameter, no_batch_call)) {
		return err;
	}

	return {};
}
