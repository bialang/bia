#include "compiler/compiler.hpp"

#include "compiler/elve/expression.hpp"
#include "compiler/jump_manager.hpp"

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

	for (auto i = tokens.begin(); i != tokens.end();) {
		BIA_LOG(INFO, "processing {} tokens", tokens.end() - i);

		i = _stmt({ i, tokens.end() });
	}
}

const compiler::token* compiler::_stmt(util::span<const token> tokens)
{
	BIA_EXPECTS(!tokens.empty());

	auto i = tokens.data();

	switch (static_cast<token::type>(i->value.index())) {
	case token::type::keyword: {
		switch (i->value.get<token::keyword>()) {
		case token::keyword::let: i = _decl({ i, tokens.end() }); break;
		case token::keyword::import: i = _import({ i, tokens.end() }); break;
		case token::keyword::while_: i = _while({ i, tokens.end() }); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
		}

		break;
	}
	default:
		// todo: remove destination
		i = elve::expression(_create_present(), { i, tokens.end() }, bytecode::member::tos{});

		_writer.write<true, bytecode::oc_drop>(1);

		break;
	}

	BIA_EXPECTS(i != tokens.end() && static_cast<token::type>(i->value.index()) == token::type::cmd_end);

	return i + 1;
}

const compiler::token* compiler::_decl(util::span<const token> tokens)
{
	BIA_EXPECTS(tokens.size() > 2 &&
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

const compiler::token* compiler::_import(util::span<const token> tokens)
{
	BIA_EXPECTS(tokens.size() >= 2 &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword);

	const auto variable = _variables.index_of(tokens.data()[1].value.get<token::identifier>().memory);
	const bytecode::member::resource name{ _resources.index_of(
		tokens.data()[1].value.get<token::identifier>().memory) };

	// overwrite existing variable
	if (variable.second) {
		// overwriting of other scopes not implemented
		BIA_EXPECTS(variable.first.scope_id == 0);

		_writer.write<true, bytecode::oc_import>(name, bytecode::member::local{ variable.first.id });
	} else {
		_variables.add(tokens.data()[1].value.get<token::identifier>().memory);

		_writer.write<true, bytecode::oc_import>(name, bytecode::member::tos{});
	}

	return tokens.data() + 2;
}

const compiler::token* compiler::_while(util::span<const token> tokens)
{
	jump_manager manager{ &_writer.output() };

	manager.mark(jump_manager::destination::start);

	tokens = tokens.subspan(elve::expression(_create_present(), tokens.subspan(1), bytecode::member::tos{}) -
	                        tokens.data());

	auto count = tokens.data()->value.get<token::batch>().count;

	_writer.write<true, bytecode::oc_test>(bytecode::member::tos{});
	_writer.write<true, bytecode::oc_drop>(1);
	manager.jump(jump_manager::type::if_false, jump_manager::destination::end);

	tokens = tokens.subspan(1);

	while (count--) {
		// flow control
		if (static_cast<token::type>(tokens.data()->value.index()) == token::type::keyword) {
			switch (tokens.data()->value.get<token::keyword>()) {
			case token::keyword::break_:
				manager.jump(jump_manager::type::unconditional, jump_manager::destination::end);
				break;
			case token::keyword::continue_:
				manager.jump(jump_manager::type::unconditional, jump_manager::destination::start);
				break;
			default: goto gt_continue;
			}

			BIA_EXPECTS(tokens.size() >= 2 &&
			            static_cast<token::type>(tokens.data()[1].value.index()) == token::type::cmd_end);

			tokens = tokens.subspan(2);
		} else {
		gt_continue:;
			tokens = tokens.subspan(_stmt(tokens) - tokens.data());
		}
	}

	manager.jump(jump_manager::type::unconditional, jump_manager::destination::start);
	manager.mark(jump_manager::destination::end);

	return tokens.data();
}

elve::present compiler::_create_present() noexcept
{
	return { _variables, _writer, _resources };
}
