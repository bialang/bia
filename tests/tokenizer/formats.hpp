#pragma once

#include <bia/tokenizer/token/parse/tokens.hpp>
#include <ostream>

using namespace bia::tokenizer;

inline std::ostream& operator<<(std::ostream& out, const token::Token::Sequence& sequence)
{
	out << "Sequence{ " << static_cast<int>(sequence.type) << ", " << sequence.count << " }";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const token::Token::Value& value)
{
	using namespace token;
	out << "Value{ ";
	if (value.is_type<Token::Sequence>()) {
		out << value.get<Token::Sequence>();
	} else {
		out << value.index();
	}
	out << " }";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const token::Parameter& param)
{
	out << "bundle[" << param.bundle.size() << "]={";
	for (std::size_t i = 0; i < param.bundle.size(); ++i) {
		if (i) {
			out << ", ";
		}
		out << i << ": " << param.bundle[i].value;
	}
	out << "}";
	return out;
}

#include <catch2/catch.hpp>
