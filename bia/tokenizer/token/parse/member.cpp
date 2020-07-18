#include "tokens.hpp"

bia::exception::syntax_details bia::tokenizer::token::parse::member(parameter& parameter)
{
	auto once = false;

	while (true) {
		if (const auto err = identifier(parameter)) {
			return once ? exception::syntax_details{} : err;
		}

		once = true;

		while (true) {
			const auto old = parameter.backup();

			if (parameter_list(parameter)) {
				parameter.restore(old);

				break;
			}
		}
	}
}
