#pragma once

#include "toolset.hpp"
#include "compiler_value.hpp"
#include "operator.hpp"


namespace bia
{
namespace compiler
{

class compile_compare_operation
{
public:
	compile_compare_operation(machine::platform::toolset & _toolset);

	compiler_value operate(compiler_value _left, framework::operator_type _operator, compiler_value _right);

private:
	machine::platform::toolset & _toolset;
};

}
}