#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "biaClassWrapper.h"
#include "biaKey.h"
#include "biaHasher.h"


namespace bia
{
namespace api
{
namespace framework
{

class BiaTemplateTable
{
public:
	/**
	 * Adds a template to the template table.
	 *
	 * @since	1.21.57.340
	 * @date	11-Jul-17
	 *
	 * @param   p_stName	Defines the name of the template.
	 * @param	[in]	p_pTemplate	Defines the template.
	 *
	 * @return  true if it succeeded, otherwise false.
	*/
	inline bool AddTemplate(std::string p_stName, std::shared_ptr<object::BiaClassWrapperBase> p_pTemplate)
	{
		if (!p_stName.empty())
		{
			machine::BiaKey key(std::move(p_stName));

			if (p_pTemplate && m_table.find(key) == m_table.end())
			{
				m_table.insert({ p_pTemplate->UniqueName(), p_pTemplate });
				m_table.insert({ std::move(key), std::move(p_pTemplate) });

				return true;
			}
		}

		return false;
	}
	/**
	 * Converts the type to a runtime unique name.
	 *
	 * @since	1.0.3.20
	 * @date	12-Apr-17
	 *
	 * @param   p_type	Defines the type.
	 *
	 * @return  The unique name.
	*/
	inline static std::string GetName(const std::type_info & p_type)
	{
		return std::to_string(p_type.hash_code());
	}
	inline static std::string GetName(size_t p_iHashCode)
	{
		return std::to_string(p_iHashCode);
	}
	template<typename T>
	inline static std::string GetName()
	{
		return std::to_string(typeid(T).hash_code());
	}
	/**
	 * Returns the template associated with the given key.
	 *
	 * @since	1.21.57.340
	 * @date	11-Jul-17
	 *
	 * @param   p_key	Defines the key.
	 *
	 * @return  A pointer to the template if it succeeds, otherwise null.
	*/
	inline const object::BiaClassWrapperBase * GetTemplate(const machine::BiaKey & p_key)
	{
		auto pResult = m_table.find(p_key);

		return pResult != m_table.end() ? pResult->second.get() : nullptr;
	}

private:
	std::unordered_map<machine::BiaKey, std::shared_ptr<object::BiaClassWrapperBase>, utility::bia_hasher> m_table;
};

}
}
}