#pragma once

#include <memory>

#include "biaGlobal.h"
#include "biaParameter.h"
#include "biaException.h"


namespace bia
{
namespace machine
{

class BiaMachineStack
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_unStackElements	Defines the amount of stack elements.
	*/
	inline BiaMachineStack(unsigned int p_unStackElements) : m_pStack(new api::BiaParameter[p_unStackElements + 1])
	{
		m_unMaxElements = p_unStackElements;
		m_unElementCount = 0;
	}
	/**
	 * Clears the stack.
	 *
	 * @since	1.7.22.156
	 * @date	22-Apr-17
	*/
	inline void Clear()
	{
		for (auto i = m_pStack.get(); m_unElementCount; ++i, --m_unElementCount)
			i->Clear();
	}

private:
	friend BiaMachineHelper;
	friend BiaMachineContext;

	std::unique_ptr<api::BiaParameter[]> m_pStack;	/**	Defines the memory used by the stack.	*/

	unsigned int m_unMaxElements;	/**	Defines the maximum amount of elements that can be stored in the stack.	*/
	unsigned int m_unElementCount;	/**	Defines the current amount of elements stored in the stack.	*/

	/**
	 * Pops the last parameters.
	 *
	 * @since	1.4.10.71
	 * @date	19-Apr-17
	 *
	 * @param   p_ucParameterCount	Defines the amount of parameters.
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the pointer is out of bounds.
	*/
	inline void PopParameters(unsigned char p_ucParameterCount)
	{
		if (p_ucParameterCount > m_unElementCount)
			throw exception::AccessViolationException("Stack underflow.");

		m_unElementCount -= p_ucParameterCount;

		for (auto i = m_pStack.get() + m_unElementCount; p_ucParameterCount--; ++i)
			i->Clear();
	}
	/**
	 * Returns the base pointer of the parameter list with the reverse offset.
	 *
	 * @since	1.4.10.71
	 * @date	19-Apr-17
	 *
	 * @param	p_ucParameterCount	Defines the count of the parameters.
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the pointer is out of bounds.
	 *
	 * @return  The base pointer.
	*/
	inline api::BiaParameter * GetStackBasePointer(unsigned char p_ucParameterCount)
	{
		if (p_ucParameterCount > m_unElementCount)
			throw exception::AccessViolationException("Stack underflow.");

		return m_pStack.get() + m_unElementCount - p_ucParameterCount;
	}
	/**
	 * Returns the next parameter and pushes it onto the stack.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the stack is full.
	 *
	 * @return  The next parameter.
	*/
	inline api::BiaParameter * GetAndPush()
	{
		if (m_unElementCount < m_unMaxElements)
			return m_pStack.get() + m_unElementCount++;
		else
			throw exception::AccessViolationException("Stack overflow.");
	}
	/**
	 * Returns the end pointer of the parameter list.
	 *
	 * @since	1.4.10.71
	 * @date	19-Apr-17
	 *
	 * @return  The end pointer.
	*/
	inline const api::BiaParameter * GetStackEndPointer() const
	{
		return m_pStack.get() + m_unElementCount;
	}
	inline BiaMachineStack & operator+=(api::BiaParameter && p_right)
	{
		//Check if stack is full
		if (m_unElementCount < m_unMaxElements)
			m_pStack.get()[m_unElementCount++] = std::move(p_right);
		else
			throw exception::AccessViolationException("Stack overflow.");

		return *this;
	}
	inline BiaMachineStack & operator+=(scope::BiaScopeReference && p_right)
	{
		//Check if stack is full
		if (m_unElementCount < m_unMaxElements)
			m_pStack.get()[m_unElementCount++] = std::move(p_right);
		else
			throw exception::AccessViolationException("Stack overflow.");

		return *this;
	}
};

}
}