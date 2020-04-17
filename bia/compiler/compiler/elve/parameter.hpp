#ifndef BIA_COMPILER_ELVE_PARAMETER_HPP_
#define BIA_COMPILER_ELVE_PARAMETER_HPP_

#include "present.hpp"

#include <bytecode/writer/instruction.hpp>
#include <cstdint>
#include <exception/implementation_error.hpp>
#include <limits>
#include <tokenizer/token/token.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename T>
util::not_null<const tokenizer::token::token*>
    expression(present present, util::not_null<const tokenizer::token::token*> first,
               util::not_null<const tokenizer::token::token*> last, T&& destination);

inline std::pair<util::not_null<const tokenizer::token::token*>, std::uint8_t>
    parameter(present present, util::not_null<const tokenizer::token::token*> first,
              util::not_null<const tokenizer::token::token*> last)
{
	using tokenizer::token::token;

	const auto begin = first.get();
	const auto end   = begin + begin->value.get<token::control>().value;

	BIA_EXPECTS(static_cast<token::type>(first->value.index()) == token::type::control);

	std::uint8_t count = 0;
	auto a             = end;
	auto b             = end;

	while (true) {
		b = a;
		a = begin + a->value.get<token::control>().value;

		if (b - a <= 1) {
			break;
		} // limit is 254
		else if (++count == std::numeric_limits<std::uint8_t>::max()) {
			throw;
		}

		expression(present, a + 1, b, bytecode::member::tos{});
	}

	return { end + 1, count };
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif