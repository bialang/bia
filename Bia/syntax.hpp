#pragma once

#include "config.hpp"
#include "lexer.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief The syntax of Bia.
 *
 * Creates and initializes the lexer with all grammar rules for Bia.
*/
class syntax
{
public:
	/**
	 * Returns the lexer with the Bia syntax.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The lexer.
	*/
	BIA_EXPORT static const grammar::lexer & lexer() noexcept;

private:
	/**	The lexer for the Bia grammar. */
	static grammar::lexer _lexer;

	/**
	 * Creates a lexer with the Bia rules.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @throws See lexer::set_rule().
	 *
	 * @return The newly created lexer.
	*/
	BIA_EXPORT static grammar::lexer init_rules();
};

}
}
