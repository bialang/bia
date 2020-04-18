#ifndef BIA_TOKENZIER_TOKEN_PARSE_STRING_HPP_
#define BIA_TOKENZIER_TOKEN_PARSE_STRING_HPP_

#include "../parameter.hpp"

#include <exception/syntax_error.hpp>
#include <string/encoding/unicode.hpp>
#include <util/finally.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details string(parameter& parameter)
{
	using namespace string::encoding;

	if (parameter.encoder.read(parameter.input) != '"') {
		return { parameter.input.tellg(), "expected '\"'" };
	}

	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = encoder::get_instance(encoder::standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { encoder::free_instance(outenc); });
	auto escape       = false;
	std::ostream output(&streambuf);

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);

#define BIA_IMPL_STRING(a, b)                                                                                \
case a: {                                                                                                    \
	if (escape) {                                                                                            \
		outenc->put(output, b);                                                                              \
		escape = false;                                                                                      \
		continue;                                                                                            \
	}                                                                                                        \
	break;                                                                                                   \
}

		switch (cp) {
			BIA_IMPL_STRING('a', '\a')
			BIA_IMPL_STRING('b', '\b')
			BIA_IMPL_STRING('f', '\f')
			BIA_IMPL_STRING('n', '\n')
			BIA_IMPL_STRING('r', '\r')
			BIA_IMPL_STRING('t', '\t')
			BIA_IMPL_STRING('v', '\v')
		case string::encoding::encoder::eof: return { parameter.input.tellg(), "expected '\"'" };
		case '"': {
			if (!escape) {
				// zero terminate
				outenc->put(output, 0);
				parameter.bundle.add({ token::string{ streambuf.finish(resource::type::string) } });

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

#undef BIA_IMPL_STRING

		escape = false;

		outenc->put(output, cp);
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif