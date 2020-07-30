#include "expression.hpp"
#include "helpers.hpp"

#include <bia/log/log.hpp>
#include <cstdint>
#include <limits>
#include <map>
#include <utility>

bia::compiler::elve::tokens_type bia::compiler::elve::parameter(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::control);

	std::map<resource::view, tokens_type> kwargs;
	std::size_t count = 0;

	while (true) {
		BIA_EXPECTS(!tokens.empty() &&
		            static_cast<token::type>(tokens.data()->value.index()) == token::type::control);

		const auto offset = tokens.data()->value.get<token::control>().value;

		if (offset <= 1) {
			tokens = tokens.subspan(offset + 1);

			break;
		}

		const auto expr = tokens.subspan(1, offset - 1);

		// kwarg
		if (static_cast<token::type>(expr.data()->value.index()) == token::type::control) {
			const auto& name = expr.data()[1].value.get<token::identifier>().memory;

			// redeclaration of same name
			if (kwargs.find(name) != kwargs.end()) {
				throw;
			}

			kwargs.insert({ name, expr.subspan(2) });
		} else {
			++count;

			expression(present, expr, bytecode::member::push{});
		}

		tokens = tokens.subspan(expr.end());
	}

	// push kwargs
	for (const auto& i : kwargs) {
		expression(present, i.second, bytecode::member::push{});
		present.writer.write<true, bytecode::oc_name>(
		    bytecode::member::resource{ present.resources.index_of(i.first) });
	}

	return tokens;
}
