#pragma once

#include <vector>
#include <unordered_map>

#include "biaMemberHolder.h"
#include "biaKey.h"
#include "biaHasher.h"
#include "biaException.h"


namespace bia
{
namespace machine
{
namespace scope
{

class BiaScopeStorage;
class BiaScopeReference;

class BiaScopeElement
{
public:
	api::framework::BiaMemberHolder member;	/**	Defines the member.	*/

	/**
	 * Constructor.
	 *
	 * @param	[in,out]	p_member	Defines the member.
	 * @param	p_uiIdentifier	Defines an unique id for this element.
	*/
	inline BiaScopeElement(api::framework::BiaMemberHolder && p_member, unsigned int p_uiIdentifier, bool p_bGlobal) : member(std::move(p_member))
	{
		m_unCounter = p_bGlobal ? 0 : 1;
		m_uiIdentifier = p_uiIdentifier;
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaScopeElement(BiaScopeElement && p_move) : member(std::move(p_move.member))
	{
		m_unCounter = p_move.m_unCounter;
		m_uiIdentifier = p_move.m_uiIdentifier;
		p_move.m_uiIdentifier = 0;
	}
	BiaScopeElement(const BiaScopeElement&) = delete;
	inline ~BiaScopeElement()
	{
		m_uiIdentifier = 0;
	}
	inline BiaScopeElement & operator=(BiaScopeElement && p_right)
	{
		member = std::move(p_right.member);
		m_unCounter = p_right.m_unCounter;
		m_uiIdentifier = p_right.m_uiIdentifier;
		p_right.m_uiIdentifier = 0;

		return *this;
	}

private:
	friend BiaScopeReference;
	friend BiaScopeStorage;

	unsigned int m_unCounter;	/**	Defines the amount of references that point to this element.	*/
	unsigned int m_uiIdentifier;	/**	Defines the unique id of this element. 0 indicates that this element is invalid.	*/
};

class BiaScopeReference
{
public:
	BiaScopeElement * pElement;	/**	Defines the element that this object refers to.	*/

	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pElement	Defines the element that should be referenced.
	*/
	inline BiaScopeReference(BiaScopeElement * p_pElement)
	{
		pElement = p_pElement;
		m_uiIdentifier = p_pElement->m_uiIdentifier;

		++p_pElement->m_unCounter;
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaScopeReference(BiaScopeReference && p_move)
	{
		pElement = p_move.pElement;
		p_move.pElement = nullptr;
		m_uiIdentifier = p_move.m_uiIdentifier;
	}
	/**
	 * Copy-Constructor.
	 *
	 * @param	p_copy	Defines the reference that should be copied.
	*/
	inline BiaScopeReference(const BiaScopeReference & p_copy)
	{
		pElement = p_copy.pElement;
		m_uiIdentifier = p_copy.m_uiIdentifier;

		if (pElement)
			++pElement->m_unCounter;
	}
	inline ~BiaScopeReference()
	{
		CutLink();
	}
	/**
	 * Cuts the link to the element.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void CutLink()
	{
		if (pElement)
		{
			if (pElement->m_uiIdentifier == m_uiIdentifier)
			{
				//Destruct. This element was constructed in BiaScopeStorage
				if (!--pElement->m_unCounter)
					pElement->~BiaScopeElement();
			}

			pElement = nullptr;
		}
	}
	/**
	 * Returns the member holder of the element.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when no valid element is referenced.
	 *
	 * @return  A reference to the member holder.
	*/
	inline api::framework::BiaMemberHolder & GetMemberHolder()
	{
		if (m_uiIdentifier != pElement->m_uiIdentifier)
			exception::AccessViolationException("Invalid access on deleted element.");

		return pElement->member;
	}
	inline BiaScopeReference & operator=(BiaScopeReference && p_right)
	{
		CutLink();

		pElement = p_right.pElement;
		p_right.pElement = nullptr;
		m_uiIdentifier = p_right.m_uiIdentifier;

		return *this;
	}

private:
	unsigned int m_uiIdentifier;	/**	Defines the id of the element that is referenced.	*/
};

typedef std::unordered_map<BiaKey, std::vector<BiaScopeReference>, utility::bia_hasher> scope_index;

}
}
}