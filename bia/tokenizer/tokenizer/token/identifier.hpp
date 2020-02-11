#ifndef BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_
#define BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>
#include <util/finally.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details identifier(token_parameter& token_parameter)
{
	using namespace string::encoding;

	auto first     = true;
	auto streambuf = token_parameter.resource_manager.start_memory(true);
	auto outenc    = encoder::get_instance(encoder::standard_encoding::utf_8);
	auto free      = util::make_finally([outenc] { encoder::free_instance(outenc); });

	std::ostream output(&streambuf);

	while (true) {
		auto pos = token_parameter.input.tellg();
		auto cp  = token_parameter.encoder.read(token_parameter.input);

		switch (category_of(cp)) {
		case category::Ll:
		case category::Lu:
		case category::Lt:
		case category::Lo:
		case category::Pc:
		case category::Nl: first = false;
		case category::Nd:
		case category::No: {
			// add to output
			if (!first) {
				outenc->put(output, cp);

				break;
			}
		}
		default: {
			// invalid char -> reset
			input.seekg(pos);

			// valid identifier
			if (!first) {
				// zero terminate
				outenc->put(output, 0);
				streambuf.commit_close();

				return {};
			}

			// not an identifier
			return { pos, "invalid identifier" };
		}
		}
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif