#ifndef BIA_TOKENIZER_SYNTAX_HPP_
#define BIA_TOKENIZER_SYNTAX_HPP_

#include "lexer.hpp"

#include <memory>

namespace bia {
namespace tokenizer {

/**
 * Contains the grammar of the Bia language.
*/
class syntax
{
public:
	/**
	 * Initialize the rules for the Bia syntax.
	*/
	static void initialize();
	static void finalize();
	static const lexer& default_syntax() noexcept;

private:
	static std::unique_ptr<lexer> default_lexer;
};

} // namespace tokenizer
} // namespace bia

#endif