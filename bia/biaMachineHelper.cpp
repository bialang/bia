#include "biaMachineHelper.h"
#include "biaModule.h"

#include <Windows.h>


namespace bia
{
namespace machine
{

bool BiaMachineHelper::ImportModule(BiaMachineContext * p_pContext)
{
	auto usModuleSize = p_pContext->m_pCode->Read<unsigned short>();

	if (p_pContext->m_pCode->pcCursor + usModuleSize + 1 > p_pContext->m_pCode->pcByteCodeEnd || p_pContext->m_pCode->pcCursor[usModuleSize])
		throw exception::InvalidByteCodeException("Invalid import parameter.");

	auto pszModule = reinterpret_cast<const char*>(p_pContext->m_pCode->pcCursor);
	p_pContext->m_pCode->pcCursor += usModuleSize + 1;

	//Alias
	auto ucAliasSize = p_pContext->m_pCode->Read<unsigned char>();
	auto pszAlias = reinterpret_cast<const char*>(p_pContext->m_pCode->pcCursor);

	if (p_pContext->m_pCode->pcCursor + ucAliasSize + 1 > p_pContext->m_pCode->pcByteCodeEnd)
		throw exception::InvalidByteCodeException("Invalid import parameter.");

	p_pContext->m_pCode->pcCursor += ucAliasSize + 1;

	//Specific
	auto ucSpecificSize = p_pContext->m_pCode->Read<unsigned char>();
	auto pcSpecific = reinterpret_cast<const char*>(p_pContext->m_pCode->pcCursor);

	if (p_pContext->m_pCode->pcCursor + ucSpecificSize > p_pContext->m_pCode->pcByteCodeEnd)
		throw exception::InvalidByteCodeException("Invalid import parameter.");

	p_pContext->m_pCode->pcCursor += ucSpecificSize;

	//Check if module is pre-registered
	if (auto pDefinition = p_pContext->m_moduleHandler.GetDefinition(std::string(pszModule, usModuleSize), std::string(pcSpecific, ucSpecificSize)))
	{
		api::framework::BiaMemberHolder member;
		auto pszName = pDefinition(&member);

		//If an alias was defined
		if (ucAliasSize)
			pszName = pszAlias;

		p_pContext->m_scope.AddVariable(std::string(pszName), std::move(member), false);

		return true;
	}
	//Load library
	else if (auto pModule = LoadLibrary(pszModule))
	{
		//Check version
		if (auto pVersion = reinterpret_cast<BiaModuleVersion>(GetProcAddress(pModule, BIA_MODULE_VERSION_NAME)))
		{
			if (pVersion() != BIA_MODULE_VERSION)
				return false;
		}
		else
			return false;
		
		std::string stFunctionName;

		if (ucSpecificSize)
		{
			stFunctionName.reserve(sizeof(BIA_MODULE_DEFINITION_NAME) + ucSpecificSize);

			stFunctionName.assign(BIA_MODULE_DEFINITION_NAME, sizeof(BIA_MODULE_DEFINITION_NAME) - 1).append(pcSpecific, ucSpecificSize);
		}
		else
			stFunctionName.assign(BIA_MODULE_DEFINITION_NAME, sizeof(BIA_MODULE_DEFINITION_NAME) - 1);

		//Load function
		if (auto pFunction = reinterpret_cast<BiaModuleDefinition>(GetProcAddress(pModule, stFunctionName.c_str())))
		{
			api::framework::BiaMemberHolder member;
			auto pszName = pFunction(&member);

			//If an alias was defined
			if (ucAliasSize)
				pszName = pszAlias;

			p_pContext->m_scope.AddVariable(std::string(pszName), std::move(member), false);

			return true;
		}

		FreeLibrary(pModule);
	}

	return false;
}

}
}