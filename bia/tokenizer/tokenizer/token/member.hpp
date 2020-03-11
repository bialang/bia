#ifndef BIA_TOKENIZER_TOKEN_MEMBER_HPP_
#define BIA_TOKENIZER_TOKEN_MEMBER_HPP_

#include "token_parameter.hpp"
#include "identifier.hpp"

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details expression(token_parameter& tp);

inline exception::syntax_details member(token_parameter& tp)
{
	if (auto err = identifier(tp)) {
		return err;
	}

	return {};
}

}
} // namespace tokenizer
} // namespace bia

#endif