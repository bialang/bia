#include "compiler/compiler.hpp"

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
	_writer.write_end();
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
	const auto pair     = _expression(first + 2, last);

	// capturing not implemented
	BIA_EXPECTS(variable.first == _variables.current_scope());

	switch (static_cast<expression_value>(pair.second.index())) {
	case expression_value::integer:
		_writer.write_instruction<true, bytecode::oc_instantiate>(/*bytecode::local_member{ variable.first },*/
		                                                          pair.second.get<std::int64_t>());
		break;
	default: BIA_IMPLEMENTATION_ERROR("invaild expression type");
	}

	return pair.first;
}

std::pair<const compiler::token*,
          bia::util::variant<bia::bytecode::local_member, bia::bytecode::global_member, std::int64_t, double>>
    compiler::_expression(const token* first, const token* last)
{
	BIA_EXPECTS(first < last);
	//BIA_EXPECTS(static_cast<token::type>(first->value.index()) == token::type::constant_int);

	util::variant<bia::bytecode::local_member, bia::bytecode::global_member, std::int64_t, double> data;

	data.emplace<std::int64_t>(first->value.get<token::keyword>() == token::keyword::true_ ? 1 : 0);

	return { first + 2, std::move(data) };
}