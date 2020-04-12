#include "compiler/compiler.hpp"

#include "compiler/elve/expression.hpp"

#include <exception/implementation_error.hpp>
#include <util/gsl.hpp>

using namespace bia::compiler;

compiler::compiler(std::ostream& output) noexcept : _writer(output)
{
	// open the script scope
	_variables.open_scope();
}

void compiler::finish()
{
	_writer.finish();
}

void compiler::receive(util::not_null<const token*> first, util::not_null<const token*> last)
{
	for (auto i = first.get(), c = last.get(); i != c;) {
		switch (static_cast<token::type>(i->value.index())) {
		case token::type::keyword: {
			switch (i->value.get<token::keyword>()) {
			case token::keyword::let: i = _decl(i, c); break;
			default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
			}

			break;
		}
		default: BIA_IMPLEMENTATION_ERROR("invalid token type");
		}
	}
}

const compiler::token* compiler::_decl(const token* first, const token* last)
{
	BIA_EXPECTS(static_cast<token::type>(first->value.index()) == token::type::keyword);

	const auto variable = _variables.index_of(first[1].value.get<token::identifier>().memory);

	// push onto stack
	if (variable.second == _variables.latest_variable()) {
		return elve::expression(_writer, first + 2, last, bytecode::member::tos{});
	}

	// overwrite existing; todo: remove cast
	return elve::expression(_writer, first + 2, last,
	                        bytecode::member::local{ (std::uint16_t) variable.second });
}
