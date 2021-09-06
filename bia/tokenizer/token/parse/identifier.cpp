#include "tokens.hpp"

#include <bia/string/encoding/unicode.hpp>
#include <bia/util/finally.hpp>

using namespace bia;
using namespace bia::tokenizer::token;

struct comparator
{
	const char** first;
	const char** last;

	comparator(const char** first, const char** last) noexcept
	{
		this->first = first;
		this->last  = last;
	}
	void next(bia::string::encoding::code_point_type cp) noexcept
	{
		if (first == last || cp < 'a' || cp > 'z') {
			return;
		}

		// find beginning
		const auto c = static_cast<char>(cp);
		for (; first != last; ++first) {
			if (**first == c) {
				break;
			}
		}

		for (auto i = first; i != last; ++i) {
			if (**i) {
				if (**i != c) {
					last = i;
					break;
				}
				++*i;
			}
		}
	}
	const char** result() const noexcept
	{
		if (first != last && !**first) {
			return first;
		}
		return nullptr;
	}
};

error::Bia parse::identifier(Parameter& param)
{
	using namespace string::encoding;
	const char* values[]{ "as",   "break",  "continue", "defer", "drop",   "else", "error", "false",
		                    "for",  "from",   "fun",      "if",    "import", "in",   "let",   "mut",
		                    "null", "return", "scoped",   "true",  "type",   "use",  "while", "yield" };
	comparator keywords{ values, values + sizeof(values) / sizeof(const char*) };
	auto first        = true;
	auto streambuf    = param.manager.start_memory(true);
	const auto outenc = get_encoder(standard_encoding::utf_8);
	const auto free   = util::finallay([outenc] { free_encoder(outenc); });
	const auto ranger = param.begin_range();
	std::ostream output{ &streambuf };

	while (true) {
		const auto state = param.reader.backup();
		const auto cp    = param.reader.read();
		switch (category_of(cp)) {
		case Category::Ll:
		case Category::Lu:
		case Category::Lt:
		case Category::Lo:
		case Category::Pc:
		case Category::Nl: first = false;
		case Category::Nd:
		case Category::No: {
			// add to output
			if (!first) {
				outenc->put(output, cp);
				keywords.next(cp);
				break;
			}
			BIA_ATTR_FALLTHROUGH;
		}
		default: {
			// valid identifier
			if (!first && !keywords.result()) {
				param.reader.restore(state);
				// zero terminate
				outenc->put(output, 0);
				param.bundle.emplace_back(Token::Identifier{ streambuf.finish(resource::Type::string) },
				                          ranger.range());
				return {};
			}
			// not an identifier
			return param.make_error(error::Code::bad_identifier, ranger.range());
		}
		}
	}
}
