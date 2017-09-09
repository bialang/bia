#pragma once

#include <stdint.h>

#include "biaMember.h"
#include "biaMemberCreator.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace object
{

class BiaClassOperatorBase
{
public:
	virtual ~BiaClassOperatorBase() = default;
	/**
	 * Executes the operator function.
	 *
	 * @param	[in,out]	p_pLeft	Defines the left-hand side.
	 * @param	[in,out]	p_pRight	Defines the right-hand side.
	 * @param	[in,out]	p_pDestination	Defines the result.
	 *
	 * @return	Returns -1 if it fails; 0 on success (void); 1 on success and a return value written to the destination.
	*/
	virtual int ExecuteOperation(void * p_pLeft, BiaMember * p_pRight, void * p_pDestination) = 0;
};

template<typename _LEFT, typename _RIGHT, typename _DESTINATION>
class BiaClassOperator final : public BiaClassOperatorBase
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines a member operation function.
	*/
	inline BiaClassOperator(_DESTINATION(_LEFT::*p_pFunction)(_RIGHT))
	{
		m_operator.pMemberFunction = p_pFunction;
		m_bStaticFunction = false;
	}
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines a static operation function.
	*/
	inline BiaClassOperator(_DESTINATION(*p_pFunction)(_LEFT, _RIGHT))
	{
		m_operator.pStaticFunction = p_pFunction;
		m_bStaticFunction = true;
	}
	/**
	 * @see	BiaClassOperatorBase::ExecuteOperation().
	*/
	inline virtual int ExecuteOperation(void * p_pLeft, BiaMember * p_pRight, void * p_pDestination) override
	{
		std::remove_cv<std::remove_reference<_RIGHT>::type>::type * pRight;

		//Cast right
		if (!p_pRight->Cast(pRight))
			return -1;

		//Static function
		if (m_bStaticFunction)
			MemberCreator(p_pDestination, m_operator.pStaticFunction(*static_cast<_LEFT*>(p_pLeft), *pRight));
		//Member function
		else
			MemberCreator(p_pDestination, (static_cast<_LEFT*>(p_pLeft)->*m_operator.pMemberFunction)(*pRight));

		return 1;
	}

private:
	union
	{
		_DESTINATION(_LEFT::*pMemberFunction)(_RIGHT);
		_DESTINATION(*pStaticFunction)(_LEFT, _RIGHT);
	} m_operator;
	bool m_bStaticFunction;
};

template<typename _LEFT, typename _RIGHT>
class BiaClassOperator<_LEFT, _RIGHT, void> final : public BiaClassOperatorBase
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines a member operation function.
	*/
	inline BiaClassOperator(void(_LEFT::*p_pFunction)(_RIGHT))
	{
		m_operator.pMemberFunction = p_pFunction;
		m_bStaticFunction = false;
	}
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines a static operation function.
	*/
	inline BiaClassOperator(void(*p_pFunction)(_LEFT, _RIGHT))
	{
		m_operator.pStaticFunction = p_pFunction;
		m_bStaticFunction = true;
	}
	/**
	 * @see	BiaClassOperatorBase::ExecuteOperation().
	*/
	inline virtual int ExecuteOperation(void * p_pLeft, BiaMember * p_pRight, void * p_pDestination) override
	{
		std::remove_cv<std::remove_reference<_RIGHT>::type>::type * pRight;

		//Cast right
		if (!p_pRight->Cast(pRight))
			return -1;

		//Static function
		if (m_bStaticFunction)
			m_operator.pStaticFunction(*static_cast<_LEFT*>(p_pLeft), *pRight);
		//Member function
		else
			(static_cast<_LEFT*>(p_pLeft)->*m_operator.pMemberFunction)(*pRight);

		return 0;
	}

private:
	union
	{
		void(_LEFT::*pMemberFunction)(_RIGHT);
		void(*pStaticFunction)(_LEFT, _RIGHT);
	} m_operator;
	bool m_bStaticFunction;
};

}
}
}
}