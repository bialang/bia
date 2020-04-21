#include "compiler/compiler.hpp"

#include "compiler/elve/expression.hpp"

#include <exception/implementation_error.hpp>
#include <log/log.hpp>
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

void compiler::receive(util::span<const token> tokens)
{
	for (auto& i : tokens) {
		printf("token %p = %zi\n", &i, i.value.index());
	}

	for (auto i = tokens.begin(); i != tokens.end(); ++i) {
		BIA_LOG(INFO, "processing {} tokens", tokens.end() - i);

		switch (static_cast<token::type>(i->value.index())) {
		case token::type::keyword: {
			switch (i->value.get<token::keyword>()) {
			case token::keyword::let: i = _decl({ i, tokens.end() }); break;
			default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
			}

			break;
		}
		default:
			// todo: remove destination
			i = elve::expression(_create_present(), { i, tokens.end() }, bytecode::member::tos{});

			break;
		}

		BIA_EXPECTS(static_cast<token::type>(i->value.index()) == token::type::cmd_end);
	}
}

const compiler::token* compiler::_decl(util::span<const token> tokens)
{
	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	BIA_LOG(INFO, "processing declaration");

	const auto index = _variables.index_of(tokens.data()[1].value.get<token::identifier>().memory);

	// overwrite existing variable
	if (index.second) {
		// overwriting of other scopes not implemented
		BIA_EXPECTS(index.first.scope_id == 0);

		return elve::expression(_create_present(), tokens.subspan(2),
		                        bytecode::member::local{ index.first.id });
	}

	_variables.add(tokens.data()[1].value.get<token::identifier>().memory);

	return elve::expression(_create_present(), tokens.subspan(2), bytecode::member::tos{});
}

elve::present compiler::_create_present() noexcept
{
	return { _variables, _writer, _resources };
}
