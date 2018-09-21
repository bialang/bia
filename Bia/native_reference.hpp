#pragma once

#include <type_traits>

#include "native_variable.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename Type>
class native_reference final : public native_variable
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param [in] _ptr The reference.
	*/
	explicit native_reference(Type * _ptr) noexcept
	{
		this->_ptr = _ptr;
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param [in] _ptr The reference.
	*/
	explicit native_reference(Type & _ref) noexcept
	{
		this->_ptr = &_ref;
	}
	virtual void print() override
	{
		//machine::link::Print(*m_pValue);
	}

private:
	/** The reference. */
	Type * _ptr;
};

}
}
}
