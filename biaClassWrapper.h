#pragma once

#include <string>
#include <vector>
#include <memory>

#include "biaGlobal.h"
#include "biaIniter.h"
#include "biaClass.h"
#include "biaStaticFunction.h"
#include "biaMemberFunction.h"
#include "biaStaticMemberFunction.h"
#include "biaLambdaFunction.h"
#include "biaLambdaMemberFunction.h"
#include "biaMemberHolder.h"
#include "biaParameter.h"
#include "biaClassOperator.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace object
{

class BiaClassWrapperBase
{
public:
	/**
	 * Constructor.
	*/
	inline BiaClassWrapperBase() : m_pMembers(new members()), m_pOperators(new operators()) {}
	virtual ~BiaClassWrapperBase() = default;
	/**
	 * Creates an instance.
	 *
	 * @param   [out]	p_pDestination	Defines the output destination of the instance.
	 * @param	[in,out]	p_pBegin	Defines the beginning of the parameter list.
	 * @param	p_pEnd	Defines the end of the parameter list.
	 *
	 * @return  true if it succeeded, otherwise false.
	*/
	virtual bool CreateInstance(void * p_pDestination, BiaParameter * p_pBegin, const BiaParameter * p_pEnd) const = 0;
	/**
	 * Returns a runtime unique name of the class.
	 *
	 * @return  A runtime unique name.
	*/
	virtual std::string UniqueName() const = 0;

protected:
	friend machine::BiaMachineContext;	//Befriended in order to grant access to the members to promote non-Bia created classes.


	std::shared_ptr<members> m_pMembers;	/**	Defines the members of the created intance.	*/
	std::shared_ptr<operators> m_pOperators;	/**	Defines the operators of the created instance.	*/

	std::vector<std::unique_ptr<BiaInitializerBase>> m_vpConstructors;	/**	Defines the usable constructors of a class. */
};

template<typename _CLASS>
class BiaClassWrapper final : public BiaClassWrapperBase
{
public:
	/**
	 * Constructor.
	*/
	inline BiaClassWrapper()
	{
		m_uiIdCounter = 0;
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaClassWrapper(BiaClassWrapper && p_move) : BiaClassWrapperBase(std::move(p_move))
	{
		m_uiIdCounter = p_move.m_uiIdCounter;
		p_move.m_uiIdCounter = 0;
	}
	inline BiaClassWrapper(const BiaClassWrapper&) = delete;
	/**
	 * @see	BiaClassWrapperBase::CreateInstance().
	*/
	inline virtual bool CreateInstance(void * p_pDestination, BiaParameter * p_pBegin, const BiaParameter * p_pEnd) const override
	{
		auto iSize = m_vpConstructors.size();

		if (iSize > 0)
		{
			for (auto i = &m_vpConstructors[0], cond = &m_vpConstructors[iSize - 1]; i <= cond; ++i)
			{
				if (auto pInstance = (*i)->Initialize(p_pBegin, p_pEnd))
				{
					(new(p_pDestination) BiaMemberHolder())->Initialize<BiaClass<_CLASS>>(static_cast<_CLASS*>(pInstance), m_pMembers, m_pOperators);

					return true;
				}
			}
		}

		return false;
	}
	/**
	 * @see	BiaClassWrapperBase::UniqueName().
	*/
	inline virtual std::string UniqueName() const override
	{
		return std::to_string(typeid(_CLASS).hash_code());
	}
	/**
	 * Adds a constructor.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  This.
	*/
	template<typename... _ARGS>
	inline BiaClassWrapper * AddConstructor()
	{
		m_vpConstructors.push_back(std::unique_ptr<BiaInitializerBase>(new BiaInitializer<_CLASS, _ARGS...>()));

		return this;
	}
	/**
	 * Adds a function.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_stName	Defines the name of the function.
	 * @param	p_pFunction	Defines the function.
	 *
	 * @return  This.
	*/
	template<typename _RETURN, typename... _ARGS>
	inline BiaClassWrapper * SetFunction(std::string p_stName, _RETURN(_CLASS::*p_pFunction)(_ARGS...))
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaMemberFunction<decltype(p_pFunction)>>(p_pFunction);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	/**
	 * Adds a function.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_stName	Defines the name of the function.
	 * @param	p_pFunction	Defines the function.
	 *
	 * @return  This.
	*/
	template<typename _RETURN, typename... _ARGS>
	inline BiaClassWrapper * SetFunction(std::string p_stName, _RETURN(_CLASS::*p_pFunction)(_ARGS...) const)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaMemberFunction<decltype(p_pFunction)>>(p_pFunction);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	/**
	 * Adds a function.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_stName	Defines the name of the function.
	 * @param	p_pFunction	Defines the function.
	 *
	 * @return  This.
	*/
	template<typename _RETURN, typename... _ARGS>
	inline BiaClassWrapper * SetFunction(std::string p_stName, _RETURN(*p_pFunction)(_ARGS...))
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaStaticFunction<decltype(p_pFunction)>>(p_pFunction);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	/**
	 * Adds a function.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_stName	Defines the name of the function.
	 * @param	p_pFunction	Defines the function.
	 *
	 * @return  This.
	*/
	template<typename _LAMBDA>
	inline BiaClassWrapper * SetFunction(std::string p_stName, _LAMBDA && p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaFunction<_LAMBDA>>(std::forward<_LAMBDA>(p_function));

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	/**
	 * Adds a function.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_stName	Defines the name of the function.
	 * @param	p_pFunction	Defines the function.
	 *
	 * @return  This.
	*/
	template<typename _LAMBDA>
	inline BiaClassWrapper * SetFunction(std::string p_stName, _LAMBDA * p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaFunction<_LAMBDA>>(p_function);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	/**
	 * Sets an operator for the given id.
	 *
	 * @since	2.38.81.467
	 * @date	09-Sep-17
	 *
	 * @param   p_uiOperatorId	Defines the operator id. See BiaMember::OPERATORS.
	 * @param	p_function	Defines the operator.
	 *
	 * @return  This.
	*/
	inline BiaClassWrapper * SetOperator(uint32_t p_uiOperatorId, std::unique_ptr<BiaClassOperatorBase> p_function)
	{
		if (p_function)
			m_pOperators->operator[](p_uiOperatorId) = std::move(p_function);

		return this;
	}
	template<typename _RETURN, typename... _ARGS>
	inline BiaClassWrapper * SetSMFunction(std::string p_stName, _RETURN(*p_pFunction)(_CLASS*, _ARGS...))
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaStaticMemberFunction<decltype(p_pFunction), _CLASS>>(p_pFunction);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	template<typename _LAMBDA>
	inline BiaClassWrapper * SetSMFunction(std::string p_stName, _LAMBDA && p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaMemberFunction<_LAMBDA, _CLASS>>(std::forward<_LAMBDA>(p_function));

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
	}
	template<typename _LAMBDA>
	inline BiaClassWrapper * SetSMFunction(std::string p_stName, _LAMBDA * p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaMemberFunction<_LAMBDA, _CLASS>>(p_function);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return this;
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

		m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(param.MoveMemberHolder()), ++m_uiIdCounter, false));
	}

private:
	unsigned int m_uiIdCounter;	/**	Defines the unqiue id counter for the members.	*/
};

}
}
}
}