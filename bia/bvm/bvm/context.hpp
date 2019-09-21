#pragma once

#include <gc/gc.hpp>


namespace bia
{
namespace bvm
{

class context
{
public:
	bia::gc::gc* gc();
private:
};

}
}