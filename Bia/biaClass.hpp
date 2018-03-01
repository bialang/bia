#pragma once

#include <cstdio>
#include <memory>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaClassContext.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClass : public BiaMember
{
public:
	inline BiaClass(std::shared_ptr<BiaClassContext> p_pClassContext, std::shared_ptr<_CLASS> p_pInstance) : m_pClassContext(std::move(p_pClassContext)), m_instance(std::move(p_pInstance))
	{
	}

	// Inherited via BiaMember
	inline virtual void Undefine() override
	{
		ReplaceObject<BiaUndefined>();
	}
	inline virtual void Print() override
	{
		printf("<%s at %p>", typeid(decltype(*this)).name(), this);
	}
	inline virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaClass<_CLASS>>(*this);
	}
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return typeid(_CLASS*) == p_type || typeid(_CLASS) == p_type;
	}
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	inline virtual int32_t Test() override
	{
		throw exception::BadCallException("Not implemented.");
	}
	/**
	 * @see	BiaMember::TestCall().
	*/
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		return 0;
	}
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		if (auto pMember = m_pClassContext->GetMember(p_szName))
			return pMember;

		throw exception::SymbolException("Unknown member.");
	}

protected:
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
	{
		throw exception::BadCastException("Not implemented.");
	}
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		if (typeid(_CLASS*) == p_type)
			return &m_instance.pInstance;
		else if (typeid(_CLASS) == p_type)
			return m_instance.pInstance;
		else
			throw exception::BadCastException("Not implemented.");
	}

private:
	struct ObjectContainer
	{
		inline ObjectContainer(std::shared_ptr<_CLASS> p_pInstance) : pInstanceHandler(std::move(p_pInstance))
		{
			pInstance = pInstanceHandler.get();
		}

		std::shared_ptr<_CLASS> pInstanceHandler;
		_CLASS * pInstance;
	};

	std::shared_ptr<BiaClassContext> m_pClassContext;
	
	ObjectContainer m_instance;
};

}
}
}