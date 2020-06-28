#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

bia::exception::syntax_details bia::tokenizer::token::parse::string(parameter& parameter)
{
	using namespace string::encoding;

	if (parameter.encoder.read(parameter.input) != '"') {
		return { parameter.input.tellg(), "expected '\"'" };
	}

	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { free_encoder(outenc); });
	auto escape       = false;
	std::ostream output(&streambuf);

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);

#define BIA_IMPL_STRING(a, b)                                                                                \
	case a: {                                                                                                \
		if (escape) {                                                                                        \
			outenc->put(output, b);                                                                          \
			escape = false;                                                                                  \
			continue;                                                                                        \
		}                                                                                                    \
		break;                                                                                               \
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
