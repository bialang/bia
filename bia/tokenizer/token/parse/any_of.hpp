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

inline std::pair<std::size_t, bool> any_of(Parameter& param, util::Czstring token)
{
	while (*token) {
		if (param.reader.read() != *token++) {
			return { 0, false };
		}
	}
	return { 0, true };
}

template<typename... Types>
inline std::pair<std::size_t, bool> any_of(Parameter& param, util::Czstring token, Types&&... tokens)
{
	const auto old = param.reader.backup();
	const auto t   = any_of(param, token);
	if (t.second) {
		return t;
	}
	param.reader.restore(old);
	const auto o = any_of(param, std::forward<Types>(tokens)...);
	return { o.first + 1, o.second };
}

template<typename... Types>
inline Error_info any_of(Parameter& param, Types&&... tokens)
{
	static_assert(sizeof...(Types) > 0, "must provide at least one option");

	const auto old = param.backup();
	Error_info error{};
	for (auto token : { tokens... }) {
		const auto err = token(param);
		if (!err) {
			return {};
		} else if (!error || error < err) {
			error = err;
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
