#include "tokenizer/token/identifier.hpp"
#include "tokenizer/token/statement.hpp"
#include "tokenizer/token/whitespace_eater.hpp"
#include "tokenizer/token/keyword.hpp"

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details single_stmt(std::istream& input, string::encoding::encoder& encoder,
                                      resource_manager& resource_manager)
{}

exception::syntax_details decl_stmt(std::istream& input, string::encoding::encoder& encoder,
                                    resource_manager& resource_manager)
{
	// compare let
	if (auto err = keyword("let", input, encoder, resource_manager)) {
		return err;
	}

	// whitespaces are required
	if (auto err = eat_whitespaces(input, encoder)) {
		return err;
	}

	identifier(input, encoder, resource_manager);

	// optional whitespaces
	eat_whitespaces(input, encoder);

	// compare '='
	auto pos = input.tellg();

	if (encoder.read(input) != '=') {
		return { pos, "expected assignment operator" };
	}

	// optional whitespaces
	eat_whitespaces(input, encoder);

	// read expression
	return expression(input, encoder, resource_manager);
}

} // namespace token
} // namespace tokenizer
} // namespace bia
