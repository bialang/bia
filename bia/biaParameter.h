#pragma once

#include <utility>
#include <algorithm>

#include "biaMemberHolder.h"
#include "biaScopeElement.h"
#include "biaException.h"



namespace bia
{
namespace api
{

class BiaParameter
{
public:
	enum class TYPE : unsigned char
	{
		NONE,
		MEMBER,
		REFERENCE
	};

	/**
	 * Constructor.
	*/
	inline BiaParameter()
	{
		m_type = TYPE::NONE;
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaParameter(BiaParameter && p_move)
	{
		if (p_move.m_type != TYPE::NONE)
		{
			memcpy(m_acSpace, p_move.m_acSpace, sizeof(m_acSpace));
			m_type = p_move.m_type;
			p_move.m_type = TYPE::NONE;
		}
		else
			m_type = TYPE::NONE;
	}
	inline ~BiaParameter()
	{
		Clear();
	}
	/**
	 * Initializes the parameter with a member holder.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_args	Defines the arguments that should be passed to the member.
	*/
	template<typename T, typename... _ARGS>
	inline void Initialize(_ARGS &&... p_args)
	{
		Clear();

		(new(m_acSpace) framework::BiaMemberHolder())->Initialize<T, _ARGS...>(std::forward<_ARGS>(p_args)...);
		m_type = TYPE::MEMBER;
	}
	/**
	 * Clears the parameter.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void Clear()
	{
		switch (m_type)
		{
		case TYPE::MEMBER:
			reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)->~BiaMemberHolder();

			break;
		case TYPE::REFERENCE:
			reinterpret_cast<machine::scope::BiaScopeReference*>(m_acSpace)->~BiaScopeReference();

			break;
		default:
			break;
		}

		m_type = TYPE::NONE;
	}
	/**
	 * Confirms the initialization destination.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void ConfirmInitialization()
	{
		m_type = TYPE::MEMBER;
	}
	/**
	 * Invalidates the cloning destination.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void CancelCloning()
	{
		reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)->InvalidDestination();
		reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)->~BiaMemberHolder();

		m_type = TYPE::NONE;
	}
	/**
	 * Returns the initialization destination.
	 *
	 * @remarks	The initialization must be confirmed with BiaParameter::ConfirmInitialization() after success.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The initialization destination.
	*/
	inline void * GetInitializationDestination()
	{
		if (m_type != TYPE::NONE)
		{
			Clear();

			m_type = TYPE::NONE;
		}

		return m_acSpace;
	}
	/**
	 * Initiates the parameter with a member holder and returns the cloning destination.
	 *
	 * @remarks	If the cloning fails, BiaParameter::CancelCloning() will be required to be called.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The cloning destination.
	*/
	inline void * GetCloningDestination()
	{
		if (m_type != TYPE::MEMBER)
		{
			Clear();

			new(m_acSpace) framework::BiaMemberHolder();
			m_type = TYPE::MEMBER;
		}

		return reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)->GetDestination();
	}
	/**
	 * Returns the size space where the member holder is stored.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The size.
	*/
	inline constexpr static size_t GetArraySize()
	{
		return sizeof(m_acSpace);
	}
	/**
	 * Returns the type of the parameter.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The type.
	*/
	inline TYPE GetType() const
	{
		return m_type;
	}
	/**
	 * Returns the member.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the parameter is empty.
	 *
	 * @return  The pointer to the member.
	*/
	inline framework::BiaMember * GetMember()
	{
		switch (m_type)
		{
		case TYPE::MEMBER:
			return reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)->GetMember();
		case TYPE::REFERENCE:
			return reinterpret_cast<machine::scope::BiaScopeReference*>(m_acSpace)->GetMemberHolder().GetMember();
		default:
			break;
		}

		throw exception::AccessViolationException("Invalid access on empty parameter.");
	}
	/**
	 * Moves the member holder out of this parameter.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the parameter does not hold a member holder.
	 *
	 * @return  The member holder.
	*/
	inline framework::BiaMemberHolder MoveMemberHolder()
	{
		if (m_type == TYPE::MEMBER)
		{
			m_type = TYPE::NONE;

			return framework::BiaMemberHolder(std::move(*reinterpret_cast<framework::BiaMemberHolder*>(m_acSpace)));
		}

		throw exception::AccessViolationException("Invalid access on parameter.");
	}
	/**
	 * Moves the scope reference out of this parameter.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the parameter does not hold a scope reference.
	 *
	 * @return  The scope reference.
	*/
	inline machine::scope::BiaScopeReference MoveScopeReference()
	{
		if (m_type == TYPE::REFERENCE)
		{
			m_type = TYPE::NONE;

			return machine::scope::BiaScopeReference(std::move(*reinterpret_cast<machine::scope::BiaScopeReference*>(m_acSpace)));
		}

		throw exception::AccessViolationException("Invalid access on parameter.");
	}
	inline BiaParameter & operator=(BiaParameter p_right)
	{
		Clear();

		if (p_right.m_type != TYPE::NONE)
		{
			memcpy(m_acSpace, p_right.m_acSpace, sizeof(m_acSpace));
			m_type = p_right.m_type;
			p_right.m_type = TYPE::NONE;
		}

		return *this;
	}
	inline BiaParameter & operator=(machine::scope::BiaScopeReference p_right)
	{
		Clear();

		new(m_acSpace) machine::scope::BiaScopeReference(std::move(p_right));
		m_type = TYPE::REFERENCE;

		return *this;
	}

private:
	char m_acSpace[(std::max)({ sizeof(framework::BiaMemberHolder),
		sizeof(machine::scope::BiaScopeReference) })];	/**	Defines the space where the parameter stores its object.	*/
	TYPE m_type;	/**	Defines the type of the parameter.	*/
};

}
}