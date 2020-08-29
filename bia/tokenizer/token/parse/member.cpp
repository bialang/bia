#include "tokens.hpp"

std::error_code bia::tokenizer::token::parse::member(parameter& parameter)
{
	auto once = false;

	while (true) {
		if (const auto err = identifier(parameter)) {
			return once ? std::error_code{} : err;
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
