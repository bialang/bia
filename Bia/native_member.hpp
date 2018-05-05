#pragma once

#include <type_traits>

#include "type_traits.hpp"
#include "native_variable.hpp"
#include "exception.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"
#include "print.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename _Ty>
class native_member final : public native_variable
{
public:
	typedef native_member<int64_t> int_member;
	typedef native_member<double> double_member;

	native_member(typename std::enable_if<std::is_same<_Ty, int64_t>::value || std::is_same<_Ty, double>::value, _Ty>::type _value) noexcept
	{
		this->_value = _value;
	}
	virtual void print() const override
	{
		machine::link::print(_value);
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<native_member<_Ty>>(_value);
	}
	//inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
	//{
	//	auto fRightNativeType = p_pRight->GetNativeType();

	//	//64 bit int operand
	//	if (fRightNativeType & NTF_INT_64)
	//		return OperatorCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>(), p_pDestination);
	//	//Float
	//	else if (fRightNativeType & NTF_FLOAT)
	//		return OperatorCallFloat(p_unOperator, *p_pRight->Cast<float>(), p_pDestination);
	//	//Double
	//	else if (fRightNativeType & NTF_DOUBLE)
	//		return OperatorCallDouble(p_unOperator, *p_pRight->Cast<double>(), p_pDestination);

	//	throw exception::OperatorException("Invalid type on native operation.");
	//}
	//inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	//{
	//	CreateResultMember(operation_chooser<_Ty>::OperationResult(m_value, p_unOperator, p_nRight), p_pDestination);
	//}
	//inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	//{
	//	CreateResultMember(operation_chooser<_Ty>::OperationResult(m_value, p_unOperator, p_llRight), p_pDestination);
	//}
	//inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	//{
	//	CreateResultMember(operation_chooser<_Ty>::OperationResult(m_value, p_unOperator, p_rRight), p_pDestination);
	//}
	//inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	//{
	//	CreateResultMember(operation_chooser<_Ty>::OperationResult(m_value, p_unOperator, p_rRight), p_pDestination);
	//}
	//inline virtual void OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination) override
	//{
	//	throw exception::BadCallException("String values are not supported.");
	//}
	//inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	//{
	//	auto fRightNativeType = p_pRight->GetNativeType();

	//	//64 bit int operand
	//	if (fRightNativeType & NTF_INT_64)
	//		return OperatorAssignCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>());
	//	//Float
	//	else if (fRightNativeType & NTF_FLOAT)
	//		return OperatorAssignCallFloat(p_unOperator, *p_pRight->Cast<float>());
	//	//Double
	//	else if (fRightNativeType & NTF_DOUBLE)
	//		return OperatorAssignCallDouble(p_unOperator, *p_pRight->Cast<double>());

	//	throw exception::OperatorException("Invalid type on native operation.");
	//}
	//inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	//{
	//	operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_nRight);
	//}
	//inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	//{
	//	operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_llRight);
	//}
	//inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	//{
	//	operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_rRight);
	//}
	//inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	//{
	//	operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_rRight);
	//}
	//inline virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) override
	//{
	//	throw exception::BadCallException("String values are not supported.");
	//}
	//inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	//{
	//	throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	//}
	//inline virtual void Clone(BiaMember * p_pDestination) override
	//{
	//	p_pDestination->ReplaceObject<BiaNative<_Ty>>(m_value);
	//}
	virtual bool is_const() const override
	{
		return false;
	}
	//inline virtual int GetNativeType() const override
	//{
	//	//Integral
	//	if (std::is_same<_Ty, int64_t>::value)
	//		return NTF_INT_8 | NTF_INT_16 | NTF_INT_32 | NTF_INT_64;
	//	//Float
	//	else if (std::is_same<_Ty, float>::value)
	//		return NTF_FLOAT;
	//	//Double
	//	else if (std::is_same<_Ty, double>::value)
	//		return NTF_DOUBLE;
	virtual int32_t test() const override
	{
		return native::test(_value);
	}
	//	return NTF_NONE;
	//}
	//inline virtual int32_t Test() override
	//{
	//	return native::Test(m_value);
	//}
	//inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	//{
	//	auto fRightNativeType = p_pRight->GetNativeType();

	//	//64 bit int operand
	//	if (fRightNativeType & NTF_INT_64)
	//		return TestCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>());
	//	//Float
	//	else if (fRightNativeType & NTF_FLOAT)
	//		return TestCallFloat(p_unOperator, *p_pRight->Cast<float>());
	//	//Double
	//	else if (fRightNativeType & NTF_DOUBLE)
	//		return TestCallDouble(p_unOperator, *p_pRight->Cast<double>());

	//	throw exception::OperatorException("Invalid type on native operation.");
	//}
	//inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	//{
	//	return test_operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_nRight);
	//}
	//inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	//{
	//	return test_operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_llRight);
	//}
	//inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	//{
	//	return test_operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_rRight);
	//}
	//inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	//{
	//	return test_operation_chooser<_Ty>::Operation(m_value, p_unOperator, p_rRight);
	//}
	//inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	//{
	//	throw exception::OperatorException("Cannot compare an integral to a string.");
	//}

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override
	{
		// Integral
		if (std::is_same<_Ty, int64_t>::value) {
			switch (_type) {
			case NATIVE_TYPE::BOOL:
				_non_zero = static_cast<bool>(_value);

				return &_non_zero;
			case NATIVE_TYPE::INT_8:
			case NATIVE_TYPE::INT_16:
			case NATIVE_TYPE::INT_32:
			case NATIVE_TYPE::INT_64:
				return &_value;
			default:
				break;
			}
		} // Double
		else if (std::is_same<_Ty, double>::value) {
			switch (_type) {
			case NATIVE_TYPE::BOOL:
				_non_zero = static_cast<bool>(_value);

				return &_non_zero;
			case NATIVE_TYPE::DOUBLE:
				return &_value;
			default:
				break;
			}
		}

		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override
	{
		return get_native_data(_type);
	}

private:
	/** The arithmetic value of type: int64_t, float or double. */
	_Ty _value;
	/** True if the value is non zero. */
	bool _non_zero;


	template<typename _Ty>
	static void create_result_member(_Ty && _value, member * _destination) noexcept
	{
		if (std::is_integral<_Ty>::value) {
			_destination->replace_this<int_member>(p_value);
		} else if (std::is_same<_Ty, double>::value) {
			_destination->replace_this<double_member>(p_value);
		} else {
			throw BIA_IMPLEMENTATION_EXCEPTION("Implementation error.");
		}
	}
};

using int_member = native_member<int64_t>;
using double_member = native_member<double>;

}
}
}