#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::member_access(Parameter& param)
{
	const auto ranger = param.begin_range();
	auto cp       = param.reader.read();
	auto nullable = false;
	if (cp == '?') {
		nullable = true;
		cp       = param.reader.read();
	}
	if (cp != '.') {
		return param.make_error(error::Code::expected_member_access, ranger.range());
	}
	param.bundle.emplace_back(nullable ? Operator::nullable_member_access : Operator::member_access, ranger.range());
	return parse::identifier(param);
}

Error_info parse::member_invocation(Parameter& param)
{
	return param.make_error(error::Code::expected_member_access, param.begin_range().range());
}

Error_info parse::member_subscript(Parameter& param)
{
	return param.make_error(error::Code::expected_member_access, param.begin_range().range());
}
