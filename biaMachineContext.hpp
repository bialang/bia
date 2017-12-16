#pragma once

#include <unordered_map>
#include <map>
#include <string>

#include "biaConfig.hpp"
#include "biaMember.hpp"
#include "biaStorage.hpp"
#include "biaMachineCode.hpp"
#include "biaInputStream.hpp"


namespace bia
{
namespace machine
{

class BiaMachineContext final
{
public:
BiaMachineContext() : m_storage(34)
{}
	//void AddScript(std::string p_stScriptName, script);
	//void RemoveScript(std::string p_stScriptName);
	//void Run(std::string p_stScriptName);
	void Run(stream::BiaInputStream & p_script);

private:
	std::unordered_map<std::string, api::framework::BiaMember*> m_index;	/**	Stores all pointers to the known variables.	*/
	std::map<std::string, BiaMachineCode> m_scripts;	/**	Stores all scripts associated with this context.	*/

	BiaStorage<1> m_storage;


	BIA_INSTRUCTION_CALLING_CONVETION static void InstantiateInt_32(int32_t p_unValue, api::framework::BiaMember * p_pMember, BiaMachineCode * p_pThis);
	BIA_INSTRUCTION_CALLING_CONVETION static void InstantiateInt_64(int64_t p_unValue, api::framework::BiaMember * p_pMember, BiaMachineCode * p_pThis);
	BIA_INSTRUCTION_CALLING_CONVETION static void InstantiateInt0(api::framework::BiaMember * p_pMember, BiaMachineCode * p_pThis);
	BIA_INSTRUCTION_CALLING_CONVETION static void InstantiateIntP1(api::framework::BiaMember * p_pMember, BiaMachineCode * p_pThis);
	BIA_INSTRUCTION_CALLING_CONVETION static void InstantiateIntN1(api::framework::BiaMember * p_pMember, BiaMachineCode * p_pThis);
};

}
}