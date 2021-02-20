#include "../jumper.hpp"
#include "../type/function.hpp"
#include "helpers.hpp"

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::import_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::import);
	BIA_ASSERT(tokens.at(1).value.is_type<Token::Identifier>());
	// TODO check with context
	const auto index    = param.serializer.index_of(tokens[1].value.get<Token::Identifier>().memory);
	const auto variable = param.symbols.create_temporary(new type::Function{ 99 });
	param.instructor.write<bytecode::Op_code::load_from_context, memory::gc::String>(variable.location.offset,
	                                                                                 index);
	param.symbols.promote_temporary(tokens[1].value.get<Token::Identifier>().memory, variable);
	return tokens.subspan(2);
}
