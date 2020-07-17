#ifndef BIA_COMPILER_ELVE_FOR_EACH_HPP_
#define BIA_COMPILER_ELVE_FOR_EACH_HPP_

#include "../jump_manager.hpp"
#include "batch.hpp"
#include "expression.hpp"
#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type for_each(present present, tokens_type tokens)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() && is_keyword(tokens.data(), token::keyword::for_));

	// create space on stack for dest variable
	if (!present.variables.index_of(tokens.data()[1].value.get<token::identifier>().memory).second) {
		present.writer.write<true, bytecode::oc_instantiate>(
		    0, bytecode::member::local{
		           present.variables.add(tokens.data()[1].value.get<token::identifier>().memory).id });
	}

	bytecode::member::local dest{
		present.variables.index_of(tokens.data()[1].value.get<token::identifier>().memory).first.id
	};
	jump_manager jumper{ &present.writer.output() };
	bytecode::member::local generator{ present.variables.add_tmp().id };

	tokens = expression(present, tokens.subspan(2), generator);

	// get next value
	jumper.mark(jump_manager::destination::start);
	present.writer.write<true, bytecode::oc_invoke>(present.variables.latest_variable().id, 0, generator, dest);

	// test generator
	present.writer.write<true, bytecode::oc_test>(
	    static_cast<typename std::underlying_type<member::test_operator>::type>(member::test_operator::self),
	    generator, generator);
	jumper.jump(jump_manager::type::if_false, jump_manager::destination::end);

	// process batch
	tokens = batch(present, tokens);

	jumper.jump(jump_manager::type::unconditional, jump_manager::destination::start);
	jumper.mark(jump_manager::destination::end);
	present.variables.remove_tmp();

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
