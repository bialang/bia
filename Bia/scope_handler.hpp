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
	typedef temp_counter::counter_t variable_index_t;

	constexpr static variable_index_t not_found = -1;

	scope_handler(machine::virtual_machine::virtual_translator & _translator);
	void open_scope();
	void close_scope();
	bool no_open_scopes() const noexcept;
	variable_index_t declare(const char * _name);
	variable_index_t variable_index(const char * _name);
	variable_index_t max_needed() const noexcept;

private:
	/** Counts the required amount of local variables. */
	temp_counter _counter;
	/** Counts the max required amount of local variables. */
	variable_index_t _max_needed;
	/** Holds all local variables associated with their name. */
	std::map<key_type, std::pair<variable_index_t, scope_id_type>> _variables;
	std::vector<variable_index_t> _variables_in_scopes;
	machine::virtual_machine::virtual_translator & _translator;
	/** Holds the position of the local variable creation. */
	machine::virtual_machine::virtual_translator::position_t _start_position;
};

}
}