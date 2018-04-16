#pragma once

#include <unordered_map>
#include <map>
#include <memory>
#include <type_traits>
#include <istream>

#include "config.hpp"
#include "member.hpp"
#include "biaTemporaryStorage.hpp"
#include "machine_code.hpp"
#include "biaVariableHandler.hpp"
#include "allocator.hpp"
#include "name_manager.hpp"
#include "biaStaticFunction.hpp"
#include "biaMemberFunction.hpp"
#include "biaLambdaFunction.hpp"
#include "biaClassTemplate.hpp"


namespace bia
{
namespace machine
{

class machine_context final
{
public:
	/**
	 * Constructor.
	 *
	 * @param	_allocator	Defines the memory allocator.
	*/
	machine_context(std::shared_ptr<allocator> _allocator);
	~machine_context();
	//void AddScript(std::string p_stScriptName, std::istream & p_script);
	/**
	 * Sets the script under the given name.
	 *
	 * @remarks	If a script with the name exists, the old script will be overriden.
	 *
	 * @since	3.63.123.707
	 * @date	2-Apr-18
	 *
	 * @param	p_stScriptName	Defines the name of the script.
	 * @param	p_pcScript	Defines the script.
	 * @param	p_iSize	Defines the size of the script in bytes.
	 *
	 * @return	true if the script was set, otherwise false.
	*/
	bool SetScript(std::string p_stScriptName, const char * p_pcScript, size_t p_iSize);
	//bool Execute(std::istream & p_script);
	/**
	 * Executes the given script.
	 *
	 * @since	3.63.123.707
	 * @date	2-Apr-18
	 *
	 * @param	p_pcScript	Defines the script.
	 * @param	p_iSize	Defines the size of the script in bytes.
	 *
	 * @return	true if the script was executed, otherwise false.
	*/
	bool Execute(const char * p_pcScript, size_t p_iSize);
	/**
	 * Executes the script associated with the name.
	 *
	 * @since	3.63.123.707
	 * @date	2-Apr-18
	 *
	 * @param	p_stScriptName	Defines the name of the script.
	 *
	 * @return	true if the script was executed, otherwise false.
	*/
	bool ExecuteScript(const std::string & p_stScriptName);
	/**
	 * Returns the script associated with the name.
	 *
	 * @since	3.63.123.707
	 * @date	2-Apr-18
	 *
	 * @param	p_stScriptName	Defines the name of the script.
	 *
	 * @return	The pointer to the executable machine code if it succeeds, otherwise null.
	*/
	machine_code * GetScript(const std::string & p_stScriptName);
	allocator * get_allocator() noexcept;
	framework::BiaMember * GetGlobal(const std::string & p_stVariable);
	framework::BiaMember * GetLocal(const std::string & p_stScriptName, const std::string & p_stVariable) = delete;
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
	template<typename _Ty, typename... _ARGS>
	inline _Ty * SetMember(StringKey p_name, _ARGS &&... p_args)
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
	template<typename _Ty>
	inline framework::object::BiaClassTemplate<_Ty> * SetTemplate(StringKey p_name)
	{
		return SetMember<framework::object::BiaClassTemplate<_Ty>>(std::move(p_name), m_pAllocator.get(), &m_nameManager);
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
	inline framework::executable::BiaStaticFunction< _RETURN, _ARGS...> * SetFunction(StringKey p_name, _RETURN(*p_pFunction)(_ARGS...))
	{
		return SetMember<framework::executable::BiaStaticFunction< _RETURN, _ARGS...>>(std::move(p_name), p_pFunction);
	}
	/**
	 * Sets a lambda function.
	 *
	 * @since	3.61.122.691
	 * @date	20-Mar-18
	 *
	 * @param	p_name	Defines the name of the member.
	 * @param	p_lambda	Defines the lambda function.
	 *
	 * @return	The pointer to the lambda function. Do not ever delete the pointer.
	*/
	template<typename _LAMBDA>
	inline framework::executable::BiaLambdaFunction<_LAMBDA> * SetLambda(StringKey p_name, _LAMBDA p_lambda)
	{
		return SetMember<framework::executable::BiaLambdaFunction<_LAMBDA>>(std::move(p_name), std::move(p_lambda));
	}
	/**
	 * Sets a lambda function.
	 *
	 * @since	3.61.122.691
	 * @date	20-Mar-18
	 *
	 * @param	p_name	Defines the name of the member.
	 * @param	p_pLambda	Defines the address of the lambda function.
	 *
	 * @return	The pointer to the lambda function. Do not ever delete the pointer.
	*/
	template<typename _LAMBDA>
	inline framework::executable::BiaLambdaFunction<_LAMBDA> * SetLambda(StringKey p_name, std::shared_ptr<_LAMBDA> p_pLambda)
	{
		return SetMember<framework::executable::BiaLambdaFunction<_LAMBDA>>(std::move(p_name), p_pLambda);
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
	std::map<std::string, BiaMachineCode> m_scripts;	/**	Stores all scripts associated with this context.	*/
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
	const char * name_address(const char * p_pcName, size_t p_iSize);
	const char * format_address(const char * p_pcName, size_t p_iSize);
	const char * string_address(std::string p_stString);
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
	framework::member * member_address(StringKey p_name);
	/**
	 * Compiles the script and returns the executable machine code.
	 *
	 * @since	3.63.123.707
	 * @date	2-Apr-18
	 *
	 * @param	p_pScript	Defines the script.
	 * @param	p_iSize	Defines the size of the script in bytes.
	 *
	 * @return	The executable machine code.
	*/
	machine_code compile_script(const void * p_pScript, size_t p_iSize);
};

}
}