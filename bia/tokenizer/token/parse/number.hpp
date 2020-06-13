#ifndef BIA_TOKENIZER_TOKEN_PARSE_NUMBER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_NUMBER_HPP_

#include "../parameter.hpp"

#include <bia/exception/syntax_error.hpp>
#include <bia/util/variant.hpp>
#include <limits>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {
namespace detail {

inline bool integer_add(token::int_type& value, string::encoding::code_point_type cp, int base)
{
	BIA_EXPECTS(cp >= '0' && cp <= '9');

	const auto val = cp - '0';

	// limit
	if (std::numeric_limits<token::int_type>::max() / 10 < value ||
	    std::numeric_limits<token::int_type>::max() - value * 10 < val) {
		return false;
	}

	value = value * 10 + val;

	return true;
}

inline bool floating_point_add(double& value, string::encoding::code_point_type cp, int base)
{
	value += (cp - '0') / 10.0;

	return true;
}

} // namespace detail

inline exception::syntax_details number(parameter& parameter)
{
	enum class state
	{
		start,
		decimal,
		zero,
		octal,
		hex_begin,
		hex,
		binary_begin,
		binary,
		floating_point,
	};

	auto s = state::start;
	util::variant<token::int_type, double> value{ 0 };

	while (true) {
		const auto pos = parameter.input.tellg();
		const auto cp  = parameter.encoder.read(parameter.input);

		// consume ' as whitespace
		if (s != state::start && cp == '\'') {
			continue;
		}

		switch (s) {
		case state::start: {
			if (cp == '0') {
				s = state::zero;
			} else if (cp >= '1' && cp <= '9') {
				s              = state::decimal;
				value.get<0>() = cp - '0';
			} else {
				return { pos, "unexpected start of number" };
			}

			break;
		}
		case state::decimal: {
			if (cp >= '0' && cp <= '9') {
				if (!detail::integer_add(value.get<0>(), cp, 10)) {
					return { pos, "integer overflow" };
				}
			} else if (cp == '.') {
				s = state::floating_point;

				value.emplace<1>(value.get<0>());
			} else {
				goto gt_end;
			}

			break;
		}
		case state::zero: {
			if (cp == 'x' || cp == 'X') {
				s = state::hex_begin;
			} else if (cp == 'b' || cp == 'B') {
				s = state::binary_begin;
			} else if (cp >= '0' && cp <= '7') {
				s              = state::octal;
				value.get<0>() = cp - '0';
			} else if (cp == '.') {
				s = state::floating_point;

				value.emplace<1>(value.get<0>());
			} else {
				goto gt_end;
			}

			break;
		}
		case state::octal: {
			if (cp >= '0' && cp <= '7') {
				if (!detail::integer_add(value.get<0>(), cp, 7)) {
					return { pos, "integer overflow" };
				}
			} else {
				goto gt_end;
			}

			break;
		}
		case state::floating_point: {
			if (cp >= '0' && cp <= '9') {
				if (!detail::floating_point_add(value.get<1>(), cp, 10)) {
					return { pos, "floating point overflow" };
				}
			}

			break;
		}
		default: BIA_IMPLEMENTATION_ERROR("not implemented");
		}

	gt_end:;
		parameter.input.seekg(pos);

		// double value
		if (value.index()) {
			parameter.bundle.add({ value.get<1>() });
		} else {
			parameter.bundle.add({ value.get<0>() });
		}

		return {};
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
