#ifndef BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_

#include "../parameter.hpp"
#include "identifier.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details expression(parameter& tp);

inline exception::syntax_details member(parameter& tp)
{
	if (auto err = identifier(tp)) {
		return err;
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif