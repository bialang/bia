#pragma once

#include "biaMember.h"
#include "biaClassWrapperMember.h"
#include "biaScopeElement.h"


namespace bia
{
namespace api
{
namespace framework
{

class BiaNamespace final : public BiaMember
{
public:
	/**
	 * Constructor.
	*/
	inline BiaNamespace() : m_pMembers(new members())
	{
		m_uiIdCounter = 0;
	}
	inline virtual void Print() const override
	{
		printf("<%s with %zi memebers at 0x%p>", typeid(*this).name(), m_pMembers->size(), this);
	}
	inline virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNamespace(m_pMembers);

		return true;
	}
	inline virtual bool Store(BiaMember*) override
	{
		return false;
	}
	inline virtual bool Inc() override
	{
		return false;
	}
	inline virtual bool Dec() override
	{
		return false;
	}
	inline virtual bool LoadObject(const machine::BiaKey & p_object, void * p_pScopeReferenceDestination) override
	{
		auto pResult = m_pMembers->find(p_object);

		if (pResult != m_pMembers->end())
		{
			new(p_pScopeReferenceDestination) machine::scope::BiaScopeReference(&pResult->second);

			return true;
		}

		return false;
	}
	inline virtual int Conditional() const override
	{
		return -1;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		return -1;
	}
	inline virtual int SelfOperator(unsigned int, void*) override
	{
		return -1;
	}
	inline virtual int Execute(void*, void*, BiaParameter*, const BiaParameter*, machine::BiaMachineContext*) override
	{
		return -1;
	}
	inline virtual int Call(const machine::BiaKey & p_function, void * p_pReturnDestination, BiaParameter * p_pBegin, const BiaParameter * p_pEnd) override
	{
		auto pResult = m_pMembers->find(p_function);

		if (pResult != m_pMembers->end())
		{
			return pResult->second.member.GetMember()->Execute(p_pReturnDestination, nullptr, p_pBegin, p_pEnd, nullptr);
		}

		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return 0;
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
	inline BiaNamespace & AddFunction(std::string p_stName, _RETURN(*p_pFunction)(_ARGS...))
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaStaticFunction<decltype(p_pFunction)>>(p_pFunction);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return *this;
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
	inline BiaNamespace & AddFunction(std::string p_stName, _LAMBDA && p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaFunction<_LAMBDA>>(std::forward<_LAMBDA>(p_function));

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return *this;
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
	inline BiaNamespace & AddFunction(std::string p_stName, _LAMBDA * p_function)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<executable::BiaLambdaFunction<_LAMBDA>>(p_function);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return *this;
	}
	template<typename T>
	inline BiaNamespace & AddConstant(std::string p_stName, const T & p_constant)
	{
		///TODO: make actually constant
		if (!p_stName.empty())
		{
			char acHolder[sizeof(BiaMemberHolder)];

			MemberCreator(acHolder, p_constant);

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(*reinterpret_cast<BiaMemberHolder*>(acHolder)), ++m_uiIdCounter, false));
		}

		return *this;
	}
	inline BiaNamespace & AddTemplate(std::string p_stName, std::shared_ptr<object::BiaClassWrapperBase> p_pMembers)
	{
		if (!p_stName.empty())
		{
			BiaMemberHolder holder;

			holder.Initialize<object::BiaClassWrapperMember>(std::move(p_pMembers));

			m_pMembers->insert_or_assign(std::move(p_stName), machine::scope::BiaScopeElement(std::move(holder), ++m_uiIdCounter, false));
		}

		return *this;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return nullptr;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return nullptr;
	}
	inline virtual TYPE IsType(const std::type_info&, unsigned int, bool) const override
	{
		return TYPE::INVALID;
	}
	inline virtual bool IsType(NATIVE_TYPE, bool) const override
	{
		return false;
	}

private:
	unsigned int m_uiIdCounter;

	std::shared_ptr<members> m_pMembers;


	/**
	 * Constructor. For cloning purposes.
	*/
	BiaNamespace(std::shared_ptr<members> p_pMemeber) : m_pMembers(std::move(p_pMemeber)) 
	{
		m_uiIdCounter = 0;
	}
};

}
}
}