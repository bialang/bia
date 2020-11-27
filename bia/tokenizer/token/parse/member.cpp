#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline error_info member_access(parameter& param)
{
	auto c        = param.encoder.read(param.input);
	auto nullable = false;
	if (c == '?') {
		nullable = true;
		c        = param.encoder.read(param.input);
	}
	if (c != '.') {
		return param.make_error(bia::error::code::, -1);
	}
	param.bundle.add({ nullable ? operator_::nullable_member_access : operator_::member_access });
	return parse::identifier(param);
}

error_info parse::member(parameter& param)
{
	if (const auto err = any_of(param, string, regex, identifier)) {
		return err;
	}
	while (true) {
		if (any_of(param, member_access)) {
			break;
		}
	}
	return {};
}
