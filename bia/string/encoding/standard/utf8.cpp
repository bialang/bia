#include "utf8.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>

using namespace bia::string::encoding::standard;

inline bia::string::encoding::Code_point next(std::istream& input)
{
	const auto tmp = input.get();
	if (tmp == std::istream::traits_type::eof()) {
		BIA_THROW(bia::error::Code::unfinished_utf_sequence);
	} else if ((tmp & 0xc0) != 0x80) {
		BIA_THROW(bia::error::Code::bad_utf_sequence);
	}
	return static_cast<bia::string::encoding::Code_point>(tmp & 0x3f);
}

void UTF8::put(std::ostream& output, Code_point cp) const
{
	if (cp < 0) {
		BIA_THROW(error::Code::bad_unicode);
	} else if (cp <= 0x7f) {
		const char data[]{ util::narrow_cast<char>(cp) };
		output.write(data, sizeof(data));
	} else if (cp <= 0x7ff) {
		const char data[]{ util::narrow_cast<char>(0xc0 | (cp >> 6 & 0x1f)),
			               util::narrow_cast<char>(0x80 | (cp & 0x3f)) };
		output.write(data, sizeof(data));
	} else if (cp <= 0xffff) {
		const char data[]{ util::narrow_cast<char>(0xe0 | (cp >> 12 & 0x1f)),
			               util::narrow_cast<char>(0x80 | (cp >> 6 & 0x3f)),
			               util::narrow_cast<char>(0x80 | (cp & 0x3f)) };
		output.write(data, sizeof(data));
	} else if (cp <= 0x10ffff) {
		const char data[]{ util::narrow_cast<char>(0xf0 | (cp >> 18 & 0x07)),
			               util::narrow_cast<char>(0x80 | (cp >> 12 & 0x3f)),
			               util::narrow_cast<char>(0x80 | (cp >> 6 & 0x3f)),
			               util::narrow_cast<char>(0x80 | (cp & 0x3f)) };
		output.write(data, sizeof(data));
	} else {
		BIA_THROW(error::Code::bad_unicode);
	}
}

bia::string::encoding::Code_point UTF8::read(std::istream& input) const
{
	const auto first = input.get();
	if (first == std::istream::traits_type::eof()) {
		input.clear();
		return eof;
	}

	if (!(first & 0x80)) {
		return static_cast<Code_point>(first);
	} else if ((first & 0xe0) == 0xc0) {
		return static_cast<Code_point>((first & 0x1f) << 6 | next(input));
	} else if ((first & 0xf0) == 0xe0) {
		const auto second = next(input);
		return static_cast<Code_point>((first & 0x0f) << 12 | second << 6 | next(input));
	} else if ((first & 0xf8) == 0xf0) {
		const auto second = next(input);
		const auto third  = next(input);
		return static_cast<Code_point>((first & 0x07) << 18 | second << 12 | third << 6 | next(input));
	}
	BIA_THROW(error::Code::bad_utf_sequence);
}
