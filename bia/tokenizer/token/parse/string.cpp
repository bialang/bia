#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

bia::tokenizer::token::error_info bia::tokenizer::token::parse::string(parameter& parameter)
{
	if (parameter.encoder.read(parameter.input) != '"') {
		return parameter.make_error(error::code::expected_string, -1);
	}

	using namespace string::encoding;
	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { free_encoder(outenc); });
	auto escape       = false;
	std::ostream output{ &streambuf };

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);
		switch (cp) {
		case encoder::eof: return parameter.make_error(error::code::expected_string, -1);
		case '"': {
			if (!escape) {
				// zero terminate
				outenc->put(output, 0);
				parameter.bundle.emplace_back(token::string{ streambuf.finish(resource::type::string) });
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
	}
}
