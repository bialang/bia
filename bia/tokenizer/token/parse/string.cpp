#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

bia::tokenizer::token::Error_info bia::tokenizer::token::parse::string(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (param.reader.read() != '"') {
		return param.make_error(error::Code::expected_string, ranger.range());
	}

	using namespace string::encoding;
	auto streambuf    = param.manager.start_memory(true);
	const auto outenc = get_encoder(Standard::utf_8);
	const auto free   = util::finallay([outenc] { free_encoder(outenc); });
	auto escape       = false;
	std::ostream output{ &streambuf };

	while (true) {
		const auto cp = param.reader.read();

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
		case Encoder::eof: return param.make_error(error::Code::expected_string, ranger.range());
		case '"': {
			if (!escape) {
				// zero terminate
				outenc->put(output, 0);
				param.bundle.emplace_back(Token::String{ streambuf.finish(resource::Type::string) }, ranger.range());
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
