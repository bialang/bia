#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

bia::tokenizer::token::Error_info bia::tokenizer::token::parse::string(parameter& parameter)
{
	if (parameter.encoder.read(parameter.input) != '"') {
		return parameter.make_error(error::Code::expected_string, -1);
	}

	using namespace string::encoding;
	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::finallay([outenc] { free_encoder(outenc); });
	auto escape       = false;
	std::ostream output{ &streambuf };

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);

#define BIA_IMPL_STRING(a, b)                                                                                \
	case a: {                                                                                                  \
		if (escape) {                                                                                            \
			outenc->put(output, b);                                                                                \
			escape = false;                                                                                        \
			continue;                                                                                              \
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
		case Encoder::eof: return parameter.make_error(error::Code::expected_string, -1);
		case '"': {
			if (!escape) {
				// zero terminate
				outenc->put(output, 0);
				parameter.bundle.emplace_back(Token::string{ streambuf.finish(resource::type::string) });
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

		escape = false;
		outenc->put(output, cp);

#undef BIA_IMPL_STRING
	}
}
