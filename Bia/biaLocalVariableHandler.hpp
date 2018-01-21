#pragma once

#include <string>
#include <vector>
#include <map>

#include "biaMember.hpp"


namespace bia
{
namespace compiler
{

class BiaLocalVariableHandler
{
public:
	void DeleteVariable(const std::string & p_stName);
	framework::BiaMember * GetVariable(const std::string & p_stName);
	framework::BiaMember * AddVariable(std::string p_stName);
	std::vector<framework::BiaMember*> GetAllUsedAddresses();

private:
	std::map<std::string, framework::BiaMember*> m_knownVariables;	/**	Stores all known variables.	*/

	std::vector<framework::BiaMember*> m_vpDeletedAddresses;	/**	Stores the addresses of all variables that were deleted in the script. The memory, however, is still useable.	 */
};

}
}