#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::assign_stmt(Parameter& param)
{
	param.bundle.emplace_back(Token::Statement_type::assign_statement, param.begin_range().range());
	if (const auto err = identifier(param)) {
		return err;
	}
	spacer(param);

	auto ranger = param.begin_range();
	if (param.reader.read() != '=') {
		return param.make_error(error::Code::expected_assignment, ranger.range());
	}
	param.bundle.emplace_back(Operator::assign, ranger.range());
	spacer(param);
	return multi_expression(param);
}
