#pragma once

#include <typeinfo>
#include <cstdio>


namespace bia
{
namespace api
{
namespace framework
{

class BiaMember
{
public:
	virtual ~BiaMember() = default;


	/**
	 * Prints the contents of this object.
	 *
	 * @since	3.42.93.567
	 * @date	18-Dec-17
	*/
	inline virtual void Print()
	{
		printf("<Empty member at %p>", this);
	}
	/**
	 * Checks whether the specified type matches this object.
	 *
	 * @since	3.42.93.567
	 * @date	18-Dec-17
	 *
	 * @param	p_type	Defines the type.
	 *
	 * @return	true if they match, otherwise false.
	*/
	inline virtual bool IsType(const std::type_info & p_type) const
	{
		return false;
	}
};

}
}
}