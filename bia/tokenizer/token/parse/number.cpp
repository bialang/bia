#include "tokens.hpp"

#include <limits>
#include <string>

inline bool integer_add(bia::tokenizer::token::token::int_type& value,
                        bia::string::encoding::code_point_type cp, int base)
{
	using bia::tokenizer::token::token;

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

inline bool floating_point_add(double& value, bia::string::encoding::code_point_type cp, int base)
{
	value += (cp - '0') / 10.0;

	return true;
}

std::error_code bia::tokenizer::token::parse::number(parameter& parameter)
{
	enum class state
	{
		start,
		decimal,
		zero,
		octal,
		hex,
		binary,
		floating_point,
	};

	auto s = state::start;
	std::string number;

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
				s = state::decimal;
			} else {
				return error::code::bad_number;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::decimal: {
			if (cp == '.') {
				s = state::floating_point;
			} else if (cp < '0' || cp > '9') {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::zero: {
			if (cp == 'x' || cp == 'X') {
				s = state::hex;
			} else if (cp == 'b' || cp == 'B') {
				s = state::binary;
			} else if (cp >= '0' && cp <= '7') {
				s = state::octal;
			} else if (cp == '.') {
				s = state::floating_point;
			} else {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::octal: {
			if (cp < '0' || cp > '7') {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::hex: {
			if ((cp < '0' || cp > '9') && (cp < 'a' || cp > 'f') && (cp < 'A' && cp > 'F')) {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::binary: {
			if (cp != '0' && cp != '1') {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		case state::floating_point: {
			if (cp < '0' || cp > '9') {
				goto gt_end;
			}

			number.push_back(static_cast<char>(cp));

			break;
		}
		default: BIA_THROW(error::code::bad_switch_value);
		}

		continue;

	gt_end:;
		parameter.input.seekg(pos);

		std::size_t tmp = 0;

		// double value
		if (s == state::floating_point) {
			try {
				parameter.bundle.add({ std::stod(number) });
			} catch (const std::exception& e) {
				return error::code::bad_number;
			}
		} else {
			try {
				parameter.bundle.add({ static_cast<token::int_type>(std::stoll(number, nullptr, 0)) });
			} catch (const std::exception& e) {
				return error::code::bad_number;
			}
		}

		return {};
	}
}
