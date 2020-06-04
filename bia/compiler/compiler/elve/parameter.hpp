#ifndef BIA_COMPILER_ELVE_PARAMETER_HPP_
#define BIA_COMPILER_ELVE_PARAMETER_HPP_

#include "present.hpp"

#include <cstdint>
#include <limits>
#include <log/log.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename Destination>
tokens_type expression(present present, tokens_type tokens, Destination&& destination);

inline std::pair<tokens_type, std::uint8_t> parameter(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	const auto first = tokens.data();
	const auto last  = first + first->value.get<token::control>().value;

	BIA_EXPECTS(static_cast<token::type>(first->value.index()) == token::type::control);

	BIA_LOG(INFO, "processing parameters {} - {}", static_cast<const void*>(first),
	        static_cast<const void*>(last));

	std::uint8_t count = 0;
	auto a             = last;
	auto b             = last;

	while (true) {
		b = a;
		a = first + a->value.get<token::control>().value;

		BIA_EXPECTS(static_cast<token::type>(a->value.index()) == token::type::control);

		if (b - a <= 1) {
			break;
		} // limit is 254
		else if (++count == std::numeric_limits<std::uint8_t>::max()) {
			throw;
		}

		expression(present, { a + 1, b }, bytecode::member::tos{});
	}

	return { tokens.subspan(last + 1), count };
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
