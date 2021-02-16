#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::member_access(Parameter& param)
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
	param.bundle.emplace_back(nullable ? Operator::nullable_member_access : Operator::member_access);
	return parse::identifier(param);
}

Error_info parse::member_invocation(Parameter& param)
{
	return param.make_error(error::Code::expected_member_access);
}

Error_info parse::member_subscript(Parameter& param)
{
	return param.make_error(error::Code::expected_member_access);
}
