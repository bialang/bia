#ifndef BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_

#include "../parameter.hpp"
#include "identifier.hpp"
#include "parameter_list.hpp"

#include <bia/exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details member(parameter& parameter)
{
	auto once = false;

	while (true) {
		if (const auto err = identifier(parameter)) {
			return once ? exception::syntax_details{} : err;
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

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
