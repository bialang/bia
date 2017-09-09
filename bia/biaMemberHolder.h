#pragma once

#include <cstring>
#include <utility>

#include "biaException.h"
#include "biaMember.h"

#ifdef _DEBUG
#define BIA_MEMBER_HOLDER_SIZE 40
#else
#define BIA_MEMBER_HOLDER_SIZE 36
#endif


namespace bia
{
namespace api
{
namespace framework
{

class BiaMemberHolder
{
public:
	/**
	 * Constructor.
	*/
	inline BiaMemberHolder()
	{
		m_fFlags = 0;
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the instance that should be moved.
	*/
	inline BiaMemberHolder(BiaMemberHolder && p_move)
	{
		if (p_move.m_fFlags & F_INITIALIZED)
		{
			memcpy(m_acSpace, p_move.m_acSpace, sizeof(m_acSpace));

			p_move.m_fFlags = 0;
			m_fFlags = F_INITIALIZED;
		}
		else
			m_fFlags = 0;
	}
	inline ~BiaMemberHolder()
	{
		if (m_fFlags & F_INITIALIZED)
			reinterpret_cast<BiaMember*>(m_acSpace)->~BiaMember();
	}
	/**
	 * Clears the member holder effectively destroying the member.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void Clear()
	{
		if (m_fFlags & F_INITIALIZED)
		{
			reinterpret_cast<BiaMember*>(m_acSpace)->~BiaMember();

			m_fFlags = 0;
		}
	}
	/**
	 * Initializes the member holder.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_args	Defines the arguments that are needed to create the member.
	*/
	template<typename T, typename... _ARGS>
	inline void Initialize(_ARGS &&... p_args)
	{
		static_assert(std::is_base_of<BiaMember, T>::value, "Must be a deriviation of BiaMember.");
		static_assert(sizeof(T) <= sizeof(m_acSpace), "Invalid size of member holder space.");

		if (m_fFlags & F_INITIALIZED)
			reinterpret_cast<BiaMember*>(m_acSpace)->~BiaMember();
		else
			m_fFlags = F_INITIALIZED;

		new(m_acSpace) T(std::forward<_ARGS>(p_args)...);
	}
	/**
	 * Invalidates the previously fetched destination.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void InvalidDestination()
	{
		m_fFlags = 0;
	}
	/**
	 * Clears the space for a member.
	 *
	 * @remarks	If the initialization failed, bia::api::framework::BiaMemberHolder::InvalidDestination() must be called.
	 *
	 * @since	2.26.66.382
	 * @date	22-Jul-17
	 *
	 * @return  The destination.
	*/
	inline void * GetDestination()
	{
		if (m_fFlags & F_INITIALIZED)
			reinterpret_cast<BiaMember*>(m_acSpace)->~BiaMember();
		else
			m_fFlags = F_INITIALIZED;

		return m_acSpace;
	}
	/**
	 * Gets the member that is being held on to.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the member holded is empty.
	 *
	 * @return  The member.
	*/
	inline BiaMember * GetMember()
	{
		if (m_fFlags & F_INITIALIZED)
			return reinterpret_cast<BiaMember*>(m_acSpace);
		
		throw exception::AccessViolationException("Cannot request data from an uninitialized member.");
	}
	inline BiaMemberHolder & operator=(BiaMemberHolder && p_right)
	{
		if (m_fFlags & F_INITIALIZED)
			reinterpret_cast<BiaMember*>(m_acSpace)->~BiaMember();

		if (p_right.m_fFlags & F_INITIALIZED)
		{
			memcpy(m_acSpace, p_right.m_acSpace, sizeof(m_acSpace));

			p_right.m_fFlags = 0;
			m_fFlags = F_INITIALIZED;
		}
		else
			m_fFlags = 0;

		return *this;
	}

private:
	enum FLAGS : unsigned char
	{
		F_INITIALIZED = 0x1
	};

	char m_acSpace[BIA_MEMBER_HOLDER_SIZE];	/**	Defines the space where the member is stored.	*/
	unsigned char m_fFlags;	/**	Defines additional flags used to describe the state of the holder.	*/
};

}
}
}