#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

using namespace bia::tokenizer::token;

error_info parse::identifier(parameter& parameter)
{
	using namespace string::encoding;
	auto first        = true;
	auto streambuf    = parameter.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::make_finally([outenc] { free_encoder(outenc); });
	std::ostream output{ &streambuf };

	while (true) {
		const auto pos = parameter.input.tellg();
		const auto cp  = parameter.encoder.read(parameter.input);
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
			// valid identifier
			if (!first) {
				parameter.input.seekg(pos);
				// zero terminate
				outenc->put(output, 0);
				parameter.bundle.emplace_back(token::identifier{ streambuf.finish(resource::type::string) });
				return {};
			}
			// not an identifier
			return parameter.make_error(error::code::bad_identifier, -1);
		}
		}
	}
}
