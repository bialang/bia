#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

bia::exception::syntax_details bia::tokenizer::token::parse::regex(parameter& parameter)
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
