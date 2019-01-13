#pragma once

#include <map>
#include <vector>

#include "member.hpp"
#include "virtual_translator.hpp"
#include "temp_counter.hpp"


namespace bia
{
namespace compiler
{

class scope_handler
{
public:
	typedef size_t scope_id_type;
	typedef const char* key_type;
	typedef machine::virtual_machine::virtual_translator::local_index_type variable_index_type;

	constexpr static variable_index_type not_found = -1;

	scope_handler(machine::virtual_machine::virtual_translator & _translator);
	void open_scope();
	void close_scope();
	bool no_open_scopes() const noexcept;
	variable_index_type declare(const char * _name);
	variable_index_type variable_index(const char * _name);

private:
	/** Counts the required amount of local variables. */
	temp_counter _counter;
	/** Holds all local variables associated with their name. */
	std::map<key_type, std::pair<variable_index_type, scope_id_type>> _variables;
	std::vector<variable_index_type> _variables_in_scopes;
	machine::virtual_machine::virtual_translator & _translator;
	/** Holds the position of the local variable creation. */
	machine::virtual_machine::virtual_translator::position_t _start_position;
};

}
}