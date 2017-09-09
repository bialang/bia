#pragma once

#include <vector>

#include "biaScopeElement.h"
#include "biaScopeStorage.h"
#include "biaException.h"
#include "biaKey.h"


namespace bia
{
namespace machine
{
namespace scope
{

class BiaScope
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_unMaxElements	Defines the maximum amount of elements per cell.
	*/
	inline BiaScope(unsigned int p_unMaxElements) : m_container(p_unMaxElements) {}
	/**
	 * Adds a scope reference.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   [in,out]	p_key	Defines the key.
	 * @param	[in,out]	p_reference	Defines the scope reference.
	 * @param	p_bCreateNew	If true a new variable will be declared no matter what, otherwise the last one will be overwritten.
	*/
	inline void AddVariable(BiaKey && p_key, BiaScopeReference && p_reference, bool p_bCreateNew)
	{
		auto & vVariables = m_index[std::move(p_key)];

		if (vVariables.empty() || p_bCreateNew)
			vVariables.push_back(std::move(p_reference));
		else
			vVariables.back() = std::move(p_reference);
	}
	/**
	 * Adds a member holder.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   [in,out]	p_key	Defines the key.
	 * @param	[in,out]	p_member	Defines the member.
	 * @param	p_bCreateNew	If true a new variable will be declared no matter what, otherwise the last one will be overwritten.
	*/
	inline void AddVariable(BiaKey && p_key, api::framework::BiaMemberHolder && p_member, bool p_bCreateNew)
	{
		auto & vVariables = m_index[std::move(p_key)];

		if (vVariables.empty() || p_bCreateNew)
			vVariables.push_back(scope::BiaScopeReference(m_container.Insert(std::move(p_member))));
		else
			vVariables.back() = scope::BiaScopeReference(m_container.Insert(std::move(p_member)));
	}
	/**
	 * Opens a new scope.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void OpenScope()
	{
		m_vScopes.push_back(m_container.GetState());
	}
	/**
	 * Closes the last opened scope.
	 *
	 * @remarks	If no open scope are left, the behavior is undefined.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void CloseScope()
	{
		m_container.PopLastElements(m_vScopes.back());
		m_vScopes.pop_back();
	}
	/**
	 * Clears the scope completly.
	 *
	 * @since	2.37.78.453
	 * @date	02-Sep-17
	*/
	inline void ClearAll()
	{
		m_vScopes.clear();
		m_index.clear();
		m_container.Clear();
	}
	/**
	 * Returns a reference associated with the specified key.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_key	Defines the key.
	 *
	 * @throws	bia::exception::SymbolException	Thrown when the key is unknown.
	 *
	 * @return  The reference.
	*/
	inline scope::BiaScopeReference GetVariable(const BiaKey & p_key)
	{
		auto pResult = m_index.find(p_key);

		//Found
		if (pResult != m_index.end())
		{
			if (!pResult->second.empty())
				return pResult->second.back();
		}

		throw exception::SymbolException("Unknown variable.");
	}

private:
	scope_container m_container;	/**	Defines the container holding all scope elements.	*/
	scope_index m_index;	/**	Defines the index of the scope.	*/
	std::vector<std::pair<unsigned int, unsigned int>> m_vScopes;	/**	Defines the currently open scopes.	*/
};

}
}
}