#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

elve::Tokens elve::import_stmt(Parameter& param, Tokens tokens)
{
	BIA_ASSERT(false);
	// BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Keyword::import);
	// BIA_ASSERT(tokens.at(1).value.is_type<Token::Identifier>());
	// if (const auto module = param.context.import(tokens[1].value.get<Token::Identifier>().memory)) {
	// 	const auto variable = param.symbols.create_temporary(module->definition);
	// 	const auto index    = param.serializer.index_of(tokens[1].value.get<Token::Identifier>().memory);
	// 	param.instructor.write<bytecode::Op_code::load_from_context, memory::gc::String>(variable.location.offset,
	// 	                                                                                 index);
	// 	param.symbols.promote_temporary(tokens[1].value.get<Token::Identifier>().memory, variable);
	// } else {
	// 	param.errors.add_error(error::Code::module_not_found, tokens.subspan(1, 1));
	// }
	// return tokens.subspan(2);
}
