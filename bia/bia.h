#pragma once

#include "biaGlobal.h"
#include "biaMachineContext.h"
#include "biaStream.h"


namespace bia
{

class Bia
{
public:
	/**
	 * Initializes Bia.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	*/
	BIA_API static void Initialize();
	/**
	 * Reserved for future use.
	*/
	BIA_API static void Finalize();
	/**
	 * Compiles the specified buffer.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pcCode	Defines the code.
	 * @param	p_iSize	Defines the size of the code.
	 * @param	[in,out]	p_compiled	Defines the compiled byte code.
	 *
	 * @return  true if the code was successfully compiled, otherwise false.
	*/
	BIA_API static bool Compile(const char * p_pcCode, size_t p_iSize, stream::BiaStream & p_compiled);
};


/**
 * Casts the given object to the specified C++ type.
 *
 * @remarks	The lifetime of the input object - not the reference - must not be shorter than the output.
 *
 * @since	2.36.76.437
 * @date	30-Aug-17
 *
 * @param   [in]	p_object	Defines a reference to the object.
 *
 * @throws	bia::exception::AccessViolationException	Thrown when the object reference is invalid.
 * @throws	bia::exception::BadCastException	Thrown when an invalid cast was performed.
 *
 * @return  A reference to the output type.
*/
template<typename T>
inline T & Cast(machine::scope::BiaScopeReference & p_object)
{
	T * pOutput;

	if (p_object.GetMemberHolder().GetMember()->Cast<T>(pOutput))
		return *pOutput;

	throw exception::BadCastException("Invalid cast.");
}

/**
 * Returns the conditional output of the object.
 *
 * @since	2.37.77.448
 * @date	02-Sep-17
 *
 * @param   [in]	p_object	Defines a reference to the object.
 *
 * @throws	bia::exception::AccessViolationException	Thrown when the object reference is invalid.
 * @throws	bia::exception::BadCallException	Thrown when the conditional output cannot be retrieved.
 *
 * @return  The conditional ouput.
*/
inline bool Conditional(machine::scope::BiaScopeReference & p_object)
{
	switch (p_object.GetMemberHolder().GetMember()->Conditional())
	{
	case 1:
		return true;
	case 0:
		return false;
	default:
		throw exception::BadCallException("Invalid conditional call.");
	}
}

inline void ParameterMakerHelper(api::BiaParameter * p_pOutput)
{
}

template<typename T, typename... _ARGS>
inline void ParameterMakerHelper(api::BiaParameter * p_pOutput, T && p_next, _ARGS &&... p_args)
{
	api::framework::MemberCreator(p_pOutput->GetInitializationDestination(), std::forward<T>(p_next));
	p_pOutput++->ConfirmInitialization();

	ParameterMakerHelper(p_pOutput, std::forward<_ARGS>(p_args)...);
}

/**
 * Executes the given object with the given parameters.
 *
 * @since	2.37.77.448
 * @date	02-Sep-17
 *
 * @param   [in,out]	p_context	Defines the machine context for execution.
 * @param   [in]	p_object	Defines a reference to the object.
 * @param	p_args	Defines the arguments that should be passed.
 *
 * @throws	bia::exception::AccessViolationException	Thrown when the object reference is invalid.
 * @throws	bia::exception::BadCallException	Thrown when the call is invalid.
 *
 * @return  The resulting value of the execution.
*/
template<typename... _ARGS>
inline api::BiaParameter Execute(machine::BiaMachineContext & p_context, machine::scope::BiaScopeReference & p_object, _ARGS &&... p_args)
{
	api::BiaParameter aParameters[std::max<size_t>(sizeof...(p_args), 1)];
	api::BiaParameter result;

	ParameterMakerHelper(aParameters, std::forward<_ARGS>(p_args)...);

	auto nResult = p_object.GetMemberHolder().GetMember()->Execute(result.GetInitializationDestination(), nullptr, aParameters, aParameters + sizeof...(_ARGS), &p_context);

	if (nResult >= 0)
	{
		if (nResult > 0)
			result.ConfirmInitialization();

		return result;
	}

	throw exception::BadCallException("Invalid function call.");
}

}