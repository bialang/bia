#pragma once

#include <unordered_map>
#include <map>
#include <memory>

#include "biaConfig.hpp"
#include "biaMember.hpp"
#include "biaStorage.hpp"
#include "biaTemporaryStorage.hpp"
#include "biaMachineCode.hpp"
#include "biaVariableHandler.hpp"
#include "biaAllocator.hpp"
#include "biaNameManager.hpp"


#include "biaStaticFunction.hpp"
#include "biaMemberFunction.hpp"
#include "biaLambdaFunction.hpp"
#include "biaClassTemplate.hpp"


namespace bia
{
namespace machine
{

inline int lulu(int y)
{
	printf("lulululu %i\n", y);

	return y * 34;
}

typedef int(*rra)(int);

inline rra heyho(const char * b)
{
	puts("heyho");
	printf("your param: %s\n", b);

	return &lulu;
}

class BiaMachineContext final
{
public:
BiaMachineContext(std::shared_ptr<BiaAllocator> p_pAllocator) : m_storage(34), m_pAllocator(std::move(p_pAllocator)), m_nameManager(m_pAllocator.get())
{

	auto pAddress = m_storage.CreateElement<framework::executable::BiaStaticFunction<decltype(&heyho)>>(heyho);

	m_index.insert({ "test", pAddress });

	auto pasd = m_storage.CreateElement<framework::executable::BiaMemberFunction<decltype(&BiaMachineContext::lul)>>(&BiaMachineContext::lul);

	m_index.insert({ "lul", pasd });

	auto lul = [](int i, const char*, int) {
		//printf("hiasd askdw %f\n", *(float*)&i);
	};
	auto wd = m_storage.CreateElement<framework::executable::BiaLambdaFunction<decltype(lul)>>(std::move(lul));

	m_index.insert({ "wd", wd });

	class MyClass
	{
	public:
		~MyClass() {
			puts("im getting deleted");
		}
	};

	auto adw = m_storage.CreateElement<framework::object::BiaClassTemplate<MyClass>>(m_pAllocator.get(), &m_nameManager);
	adw->SetFunction("hey", heyho);
	m_index.insert({ "obj", adw });
}
	//void AddScript(std::string p_stScriptName, script);
	//void RemoveScript(std::string p_stScriptName);
	//void Run(std::string p_stScriptName);
	BIA_EXPORT void Run(const void * p_pScript, size_t p_iSize);
	BIA_EXPORT framework::BiaMember * GetGlobal(const std::string & p_stVariable);
	BIA_EXPORT framework::BiaMember * GetLocal(const std::string & p_stScriptName, const std::string & p_stVariable) = delete;
	void lul()
	{

	}
//private:
	//friend BiaCompiler;

	/*struct StringKey
	{
		inline StringKey(std::string p_stString) : stKey(std::move(p_stString))
		{

		}
		inline StringKey(const void * p_pBuffer, size_t p_iSize) : stKey(static_cast<const char*>(p_pBuffer), p_iSize)
		{

		}

		std::string stKey;
	};*/

	variable_index m_index;	/**	Stores all pointers to the known variables.	*/
	std::map<StringKey, BiaMachineCode> m_scripts;	/**	Stores all scripts associated with this context.	*/
	std::shared_ptr<BiaAllocator> m_pAllocator;	/**	Defines the memory allocator.	*/
	
	BiaNameManager m_nameManager;

	BiaStorage<16> m_storage;
	//BiaTemporaryStorage<framework::BiaMember, 16> m_temporaryStorage;


	/**
	 * Allocates and constructs the members and stores the addresses in 2D destination array.
	 *
	 * @since	3.45.96.586
	 * @date	1-Jan-18
	 *
	 * @param	p_cCount	Defines the count of the addresses.
	 * @param	[in,out]	p_ppDestination	Defines the destination.
	*/
	void ConstructTemporaryAddresses(int8_t p_cCount, framework::BiaMember ** p_ppDestination);
	/**
	 * Destroys and deallocates the given addresses.
	 *
	 * @since	3.45.96.586
	 * @date	1-Jan-18
	 *
	 * @param	p_cCount	Defines the count of the addresses.
	 * @param	[in,out]	p_ppAddresses	Defines the addresses that should be freed.
	*/
	void DestructTemporaryAddresses(int8_t p_cCount, framework::BiaMember ** p_ppAddresses);
	const char * NameAddressOf(const char * p_pcName, size_t p_iSize);
	const char * FormatAddressOf(const char * p_pcName, size_t p_iSize);
	const char * StringAddressOf(std::string p_stString);
	/**
	 * Returns the address of the member.
	 *
	 * @since	3.45.96.586
	 * @date	1-Jan-18
	 *
	 * @param	p_name	Defines the name of the member.
	 *
	 * @return	The address.
	*/
	framework::BiaMember * AddressOf(StringKey p_name);
};

}
}