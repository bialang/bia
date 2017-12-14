#pragma once

#include <string>

#include "biaGlobal.h"
#include "biaMemberHolder.h"
#include "biaScope.h"
#include "biaByteStream.h"
#include "biaMachineSettings.h"
#include "biaMachineStack.h"
#include "biaModuleHandler.h"
#include "biaTemplateTable.h"
#include "biaParameter.h"
#include "biaStaticFunction.h"
#include "biaLambdaFunction.h"
#include "biaClassWrapper.h"


namespace bia
{
namespace machine
{

class BiaMachineContext
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_settings	(Optional)	Defines the machine settings.
	*/
	inline BiaMachineContext(BiaMachineSettings p_settings = BiaMachineSettings()) : m_stack(p_settings.unStackSize), m_scope(p_settings.unMaxElementsPerCell) {}
	BIA_API void Execute(stream::BiaByteStream p_byteCode);
	template<typename _RETURN, typename... _ARGS>
	inline void SetFunction(std::string p_stName, _RETURN(*p_pStaticFunction)(_ARGS...))
	{
		if (!p_stName.empty())
		{
			api::framework::BiaMemberHolder holder;

			holder.Initialize<api::framework::executable::BiaStaticFunction<decltype(p_pStaticFunction)>>(p_pStaticFunction);

			m_scope.AddVariable(std::move(p_stName), std::move(holder), false);
		}
	}
	template<typename _LAMBDA>
	inline void SetFunction(std::string p_stName, _LAMBDA && p_function)
	{
		if (!p_stName.empty())
		{
			api::framework::BiaMemberHolder holder;

			holder.Initialize<api::framework::executable::BiaLambdaFunction<_LAMBDA>>(std::forward<_LAMBDA>(p_function));

			m_scope.AddVariable(std::move(p_stName), std::move(holder), false);
		}
	}
	template<typename _LAMBDA>
	inline void SetFunction(std::string p_stName, _LAMBDA * p_function)
	{
		if (!p_stName.empty())
		{
			api::framework::BiaMemberHolder holder;

			holder.Initialize<api::framework::executable::BiaLambdaFunction<_LAMBDA>>(p_function);

			m_scope.AddVariable(std::move(p_stName), std::move(holder), false);
		}
	}
	/**
	 * Creates a variable.
	 *
	 * @since	2.36.76.437
	 * @date	30-Aug-17
	 *
	 * @param   p_stName	Defines the name of the variable.
	 * @param	p_variable	Defines the variable itself.
	*/
	template<typename T>
	inline void SetVariable(std::string p_stName, T && p_variable)
	{
		api::BiaParameter param;

		api::framework::MemberCreator(param.GetInitializationDestination(), std::forward<T>(p_variable));
		param.ConfirmInitialization();

		//Set type
		if (auto pTemplate = m_templates.GetTemplate(api::framework::BiaTemplateTable::GetName<std::remove_pointer<std::remove_reference<T>::type>::type>()))
		{
			api::framework::BiaMember::SET_PARAMETER_DATA data;

			data.pMembers = &pTemplate->m_pMembers;
			param.GetMember()->SetParameter(api::framework::BiaMember::SET_PARAMETER::MEMBERS, data);
		}

		m_scope.AddVariable(std::move(p_stName), std::move(param.MoveMemberHolder()), false);
	}
	/**
	 * Clears the scope.
	 *
	 * @since	2.37.78.453
	 * @date	02-Sep-17
	*/
	inline void ClearScope()
	{
		m_scope.ClearAll();
	}
	/**
	 * Returns a reference to the template table.
	 *
	 * @since	2.36.76.437
	 * @date	30-Aug-17
	 *
	 * @return  The reference to the template table.
	*/
	inline api::framework::BiaTemplateTable & GetTemplateTable()
	{
		return m_templates;
	}
	/**
	 * Returns a reference to the module handler.
	 *
	 * @since	2.36.76.437
	 * @date	30-Aug-17
	 *
	 * @return  The reference to the module handler.
	*/
	inline BiaModuleHandler & GetModuleHandler()
	{
		return m_moduleHandler;
	}
	/**
	 * Returns the member matching the name.
	 *
	 * @since	2.36.76.437
	 * @date	30-Aug-17
	 *
	 * @param   p_stName	Defines the name.
	 *
	 * @throws	bia::exception::SymbolException	Thrown when the key is unknown.
	 *
	 * @return  The matching member.
	*/
	inline scope::BiaScopeReference GetMember(std::string p_stName)
	{
		return m_scope.GetVariable(BiaKey(std::move(p_stName)));
	}

private:
	friend BiaMachineHelper;
	friend api::framework::executable::BiaBiaFunction;

	BiaMachineStack m_stack;	/**	Defines the stack for function calls.	*/
	scope::BiaScope m_scope;	/**	Holds all declared variables and functions.	*/
	BiaModuleHandler m_moduleHandler;	/**	Handles all pre-registered modules and monitors all imported definitions.	*/

	api::BiaParameter m_accumulator;	/**	Defines the accumulator for the machine.	*/
	api::framework::BiaTemplateTable m_templates;	/**	Holds all class templates.	*/

	stream::BiaByteStream * m_pCode;	/**	Stores the byte code of the executable script.	*/


	/**
	 * Initiates this context.
	 *
	 * @since	1.4.10.71
	 * @date	19-Apr-17
	 *
	 * @param	[in]	p_pCode	Defines the pointer to the code stream.
	*/
	inline void InitiaiteContext(stream::BiaByteStream * p_pCode)
	{
		//Reset
		m_stack.Clear();
		m_accumulator.Clear();

		m_pCode = p_pCode;
	}
	/**
	 * Promotes the accumulator to a BiaClass if it is a raw class and if a template is available.
	 *
	 * @since	2.37.77.448
	 * @date	02-Sep-17
	*/
	inline void PromoteAccumulatorClass()
	{
		api::framework::BiaMember::GET_PARAMETER_DATA name;

		if (m_accumulator.GetMember()->GetParameter(api::framework::BiaMember::GET_PARAMETER::CLASS_HASH_CODE, name))
		{
			if (auto pTemplate = m_templates.GetTemplate(api::framework::BiaTemplateTable::GetName(name.iClassHashCode)))
			{
				api::framework::BiaMember::SET_PARAMETER_DATA data;

				data.classPromoteParams.pMembers = &pTemplate->m_pMembers;
				data.classPromoteParams.pOperators = &pTemplate->m_pOperators;
				m_accumulator.GetMember()->SetParameter(api::framework::BiaMember::SET_PARAMETER::CLASS_PROMOTE_PARAMS, data);
			}
		}
	}
	inline void ExecuteBia(stream::BiaByteStream p_byteCode)
	{

	}
	/**
	 * @see	bia::machine::BiaBiaFunction::Execute().
	*/
	//virtual bool Execute(api::BiaParameter & p_return, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, stream::BiaByteStream & p_byteCode) override;
};

}
}