#ifndef BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_

#include "../error_info.hpp"
#include "../parameter.hpp"

#include <bia/util/gsl.hpp>
#include <initializer_list>
#include <utility>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline std::pair<std::size_t, bool> any_of(parameter& tp, util::czstring token)
{
	while (*token) {
		const auto pos = tp.input.tellg();
		if (tp.encoder.read(tp.input) != *token++) {
			return { 0, false };
		}
	}
	return { 0, true };
}

template<typename... Types>
inline std::pair<std::size_t, bool> any_of(parameter& tp, util::czstring token, Types&&... tokens)
{
	const auto old = tp.input.tellg();
	const auto t   = any_of(tp, token);
	if (t.second) {
		return t;
	}
	tp.input.seekg(old);
	const auto o = any_of(tp, std::forward<Ts>(tokens)...);
	return { o.first + 1, o.second };
}

template<typename... Types>
inline error_info any_of(parameter& param, Types&&... tokens)
{
	static_assert(sizeof...(Types) > 0, "must provide at least one option");

	const auto old = param.backup();
	error_info error{};
	for (auto token : std::initializer_list<error_info (*)(param&)>{ tokens... }) {
		const auto err = token(param);
		if (!err) {
			return {};
		} else if (error < err) {
			err = token;
		}
		param.restore(old);
	}
	return error;
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
