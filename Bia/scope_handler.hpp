#pragma once

#include "member.hpp"


namespace bia
{
namespace compiler
{

class scope_handler
{
public:

	void open_scope();
	void close_scope();
	void declare(const char * _name);
	int get_variable_id(const char * _name);
private:
};

}
}