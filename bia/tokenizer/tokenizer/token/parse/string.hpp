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

	std::ostream output(&streambuf);

	while (true) {
		const auto cp = parameter.encoder.read(parameter.input);

		if (cp == '"') {
			// zero terminate
			outenc->put(output, 0);
			parameter.bundle.add({ token::string{ streambuf.finish(resource::type::string) } });
			
			return {};
		}

		outenc->put(output, cp);
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif