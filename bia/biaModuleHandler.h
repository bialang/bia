#pragma once

#include <set>
#include <string>
#include <map>

#include "biaModule.h"


namespace bia
{
namespace machine
{

class BiaModuleHandler
{
public:
	/**
	 * Sets the definition for the given parameters. If the definition already exists, it will be overwritten.
	 *
	 * @since	2.35.75.432
	 * @date	29-Aug-17
	 *
	 * @param   p_stModule	Defines the name of the module.
	 * @param	p_stSpecific	Defines the name of the specific.
	 * @param	p_pDefinition	Defines the definition.
	 *
	*/
	inline void SetSpecific(std::string p_stModule, const std::string & p_stSpecific, BiaModuleDefinition p_pDefinition)
	{
		if (p_pDefinition)
		{
			//Format
			p_stModule.reserve(p_stModule.size() + p_stSpecific.size() + 4);
			p_stModule.append(".bll", 4).append(p_stSpecific);

			m_preRegisteredModules[std::move(p_stModule)] = p_pDefinition;
		}
	}
	/**
	 * Returns the definition for the given parameters.
	 *
	 * @since	2.35.75.432
	 * @date	29-Aug-17
	 *
	 * @param   p_stModule	Defines the name of the module. Needs a trailing '.bll'.
	 * @param	p_stSpecific	Defines the name of the specific.
	 *
	 * @return  The definition if it succeeds, otherwise null.
	*/
	inline BiaModuleDefinition GetDefinition(std::string p_stModule, const std::string & p_stSpecific)
	{
		//Format
		p_stModule.reserve(p_stModule.size() + p_stSpecific.size());
		p_stModule.append(p_stSpecific);

		auto pResult = m_preRegisteredModules.find(p_stModule);

		return pResult != m_preRegisteredModules.end() ? pResult->second : nullptr;
	}
private:
	std::map<std::string, BiaModuleDefinition> m_preRegisteredModules;	/**	Holds all pre-registered modules. These modules have priority over the .bll files.	*/
};

}
}