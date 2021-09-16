#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::compiler;
using namespace bia::tokenizer::token;
using namespace bia::internal;

elve::Tokens elve::import_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(tokens.front().value == Token::Keyword::import);

	if (tokens.at(1).value.is_type<Token::Identifier>()) {
		const bool has_as = tokens.size() >= 3 && tokens[2].value == Token::Keyword::as;
		if (const auto module =
		      param.context.global_namespace().get_module(tokens[1].value.get<Token::Identifier>().memory)) {
			auto variable = param.symbols.create_temporary(module->definition);
			// TODO adjust size
			param.instructor.write<bytecode::Op_code::load_from_namespace>(bytecode::Size::bit_64, variable.offset,
			                                                               module->offset, 1);
			variable.flags = 0;
			param.symbols.promote_temporary(tokens[has_as ? 3 : 1].value.get<Token::Identifier>().memory, variable);
		} else {
			param.errors.add_error(error::Code::undefined_module, tokens.subspan(1, 1));
		}
		return tokens.subspan(has_as ? 4 : 2);
	} else {
		// TODO implement for strings
		BIA_ASSERT(false);
	}
	return tokens;
}
