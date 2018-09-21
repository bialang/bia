#pragma once

#include "config.hpp"
#include "interpreter.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief The syntax of Bia.
 *
 * Creates and initializes the interpreter with all grammar rules for Bia.
*/
class syntax
{
public:
	/**
	 * Returns the interpreter with the Bia syntax.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The interpreter.
	*/
	BIA_EXPORT static const grammar::interpreter & interpreter() noexcept;

private:
	/**	Defines the interpreter for the Bia grammar.	*/
	static grammar::interpreter _interpreter;

	/**
	 * Creates an interpreter with the Bia rules.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @throws See interpreter::set_rule().
	 *
	 * @return The newly created interpreter.
	*/
	BIA_EXPORT static grammar::interpreter init_rules();
};

}
}
