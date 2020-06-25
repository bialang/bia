#ifndef BIA_TOKENZIER_TOKEN_PARSE_REGEX_HPP_
#define BIA_TOKENZIER_TOKEN_PARSE_REGEX_HPP_

#include "../parameter.hpp"

#include <bia/exception/syntax_error.hpp>
#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details regex(parameter& parameter)
{
	using namespace string::encoding;

	if (parameter.encoder.read(parameter.input) != '/') {
		return { parameter.input.tellg(), "expected '/'" };
	}

	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { free_encoder(outenc); });
	auto escape       = false;
	std::ostream output{ &streambuf };

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);

		switch (cp) {
		case encoder::eof: return { parameter.input.tellg(), "expected '/'" };
		case '/': {
			if (!escape) {
				// zero terminate
				outenc->put(output, 0);
				parameter.bundle.add({ token::regex{ streambuf.finish(resource::type::regex) } });

				return {};
			}

			break;
		}
		case '\\': {
			if (!escape) {
				escape = true;

				continue;
			}

			break;
		}
		default: break;
		}

		// had no special meaning
		if (escape) {
			outenc->put(output, '\\');
		}

		escape = false;

		outenc->put(output, cp);
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
