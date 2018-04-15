#pragma once

#include "interpreter.hpp"
#include "interpreter_ids.hpp"


namespace bia
{
namespace grammar
{

class syntax
{
public:
	/**
	 * Returns the interpreter with the Bia syntax.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @return	The interpreter.
	*/
	static const interpreter & get_interpreter() noexcept;

private:
	/**	Defines the interpreter for the Bia grammar.	*/
	static interpreter _interpreter;


	static interpreter init_rules();
};

}
}