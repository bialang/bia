#pragma once

#include <unordered_map>
#include <map>
#include <memory>
#include <type_traits>

#include "biaConfig.hpp"
#include "biaMember.hpp"
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
	BiaMachineContext(std::shared_ptr<BiaAllocator> p_pAllocator) : m_pAllocator(std::move(p_pAllocator)), m_nameManager(m_pAllocator.get())
	{
		class MyClass
		{
		public:
			MyClass(int a, const char * p) {
				printf("im getting %i cons %s tructed\n", a, p);
			}
			~MyClass() {
				puts("im getting deleted");
			}
		};

		SetTemplate<MyClass>("obj")->SetFunction("hey", &heyho)->SetConstructor<int, const char*>();
	}
	~BiaMachineContext();
	//void AddScript(std::string p_stScriptName, script);
	//void RemoveScript(std::string p_stScriptName);
	//void Run(std::string p_stScriptName);
	BIA_EXPORT void Run(const void * p_pScript, size_t p_iSize);
	BIA_EXPORT framework::BiaMember * GetGlobal(const std::string & p_stVariable);
	BIA_EXPORT framework::BiaMember * GetLocal(const std::string & p_stScriptName, const std::string & p_stVariable) = delete;
	/**
	 * Sets a member directly.
	 *
	 * @remarks	The member type must be a deriviate of framework::BiaMember.
	 *
	 * @since	3.61.122.691
	 * @date	20-Mar-18
	 *
	 * @param	p_name	Defines the name of the member.
	 * @param	p_args	Defines the arguments needed to create the member.
	 *
	 * @return	The pointer to the member. Do not ever delete the pointer.
	*/
	template<typename T, typename... _ARGS>
	inline T * SetMember(StringKey p_name, _ARGS &&... p_args)
	{
		auto allocation = m_pAllocator->ConstructBlocks<framework::BiaMember, T>(1, machine::BiaAllocator::MEMORY_TYPE::NORMAL, std::forward<_ARGS>(p_args)...);

#if defined(BIA_CPP_17)
		//m_members.insert_or_assign(m_pNameManager->GetNameAddress(p_stName.c_str(), p_stName.length()), std::move(allocation));
#else
		m_index[std::move(p_name)] = std::move(allocation);
#endif

		return static_cast<T*>(allocation.pAddress);
	}
	/**
	 * Sets a class template.
	 *
	 * @since	3.61.122.691
	 * @date	20-Mar-18
	 *
	 * @param	p_name	Defines the name of the member.
	 *
	 * @return	The pointer to the class template. Do not ever delete the pointer.
	*/
	template<typename T>
	inline framework::object::BiaClassTemplate<T> * SetTemplate(StringKey p_name)
	{
		return SetMember<framework::object::BiaClassTemplate<T>>(std::move(p_name), m_pAllocator.get(), &m_nameManager);
	}
	/**
	 * Sets a static function.
	 *
	 * @since	3.61.122.691
	 * @date	20-Mar-18
	 *
	 * @param	p_name	Defines the name of the member.
	 * @param	p_pFunction	Defines the address of the function.
	 *
	 * @return	The pointer to the static function. Do not ever delete the pointer.
	*/
	template<typename _RETURN, typename... _ARGS>
	inline framework::executable::BiaStaticFunction< _RETURN(*)(_ARGS...)> * SetFunction(StringKey p_name, _RETURN(*p_pFunction)(_ARGS...))
	{
		return SetMember<framework::executable::BiaStaticFunction< _RETURN(*)(_ARGS...)>>(std::move(p_name), p_pFunction);
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