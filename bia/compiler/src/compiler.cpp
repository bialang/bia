#include "compiler/compiler.hpp"

#include "compiler/elve/expression.hpp"

#include <exception/implementation_error.hpp>
#include <util/gsl.hpp>

using namespace bia::compiler;

compiler::compiler(std::ostream& instructions, std::ostream& resource) noexcept
    : _writer{ instructions }, _resources{ resource }
{
	// open the script scope
	_variables.open_scope();
}

void compiler::finish()
{
	_writer.finish();
	_resources.finish();
}

void compiler::receive(util::not_null<const token*> first, util::not_null<const token*> last)
{
	for (auto i = first.get(), c = last.get(); i < c; ++i) {
		printf("token %p = %zi\n", i, i->value.index());
	}

	for (auto i = first.get(), c = last.get(); i < c; ++i) {
		switch (static_cast<token::type>(i->value.index())) {
		case token::type::keyword: {
			switch (i->value.get<token::keyword>()) {
			case token::keyword::let: i = _decl(i, c); break;
			default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
			}

			break;
		}
		default:
			// todo: remove destination
			i = elve::expression(_create_present(), i, c, bytecode::member::tos{});
			break;
		}

		BIA_EXPECTS(static_cast<token::type>(i->value.index()) == token::type::cmd_end);
	}
}

const compiler::token* compiler::_decl(const token* first, const token* last)
{
	BIA_EXPECTS(static_cast<token::type>(first->value.index()) == token::type::keyword);

	const auto index = _variables.index_of(first[1].value.get<token::identifier>().memory);

	// overwrite existing variable
	if (index.second) {
		// overwriting of other scopes not implemented
		BIA_EXPECTS(index.first.scope_id == 0);

		return elve::expression(_create_present(), first + 2, last,
		                        bytecode::member::local{ index.first.id });
	}

	_variables.add(first[1].value.get<token::identifier>().memory);

	return elve::expression(_create_present(), first + 2, last, bytecode::member::tos{});
}

elve::present compiler::_create_present() noexcept
{
	return { _variables, _writer, _resources };
}
