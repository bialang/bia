#ifndef BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_
#define BIA_TOKENZIER_TOKEN_IDENTIFIER_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>
#include <string/encoding/unicode.hpp>
#include <util/finally.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details identifier(token_parameter& tp)
{
	using namespace string::encoding;

	auto first        = true;
	auto streambuf    = tp.manager.start_memory(true);
	const auto outenc = encoder::get_instance(encoder::standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { encoder::free_instance(outenc); });

	std::ostream output(&streambuf);

	while (true) {
		const auto pos = tp.input.tellg();
		const auto cp  = tp.encoder.read(tp.input);

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
			tp.input.seekg(pos);

			// valid identifier
			if (!first) {
				// zero terminate
				outenc->put(output, 0);
				
				auto mem = tp.manager.stop_memory(false);

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