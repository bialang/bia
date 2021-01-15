#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::member_access(parameter& param)
{
	auto cp       = param.encoder.read(param.input);
	auto nullable = false;
	if (cp == '?') {
		nullable = true;
		cp       = param.encoder.read(param.input);
	}
	if (cp != '.') {
		return param.make_error(error::Code::expected_member_access, -1);
	}
	param.bundle.emplace_back(nullable ? operator_::nullable_member_access : operator_::member_access);
	return parse::identifier(param);
}

Error_info parse::member_invocation(parameter& param)
{
	return param.make_error(error::Code::expected_member_access);
}

Error_info parse::member_subscript(parameter& param)
{
	return param.make_error(error::Code::expected_member_access);
}
