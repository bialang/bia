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

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _value The initial value.
	*/
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
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_value, _operator, _right), _destination);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_value, _operator, _right), _destination);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right)
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_value, _operator, _right), _destination);
	}
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
	virtual bool is_const() const override
	{
		return false;
	}
	virtual int32_t test() const override
	{
		return native::test(_value);
	}
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override
	{
		return test_operation(_value, _operator, _right);
	}
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override
	{
		return test_operation(_value, _operator, _right);
	}
	virtual int32_t test_double(operator_type _operator, double _right) const override
	{
		return test_operation(_value, _operator, _right);
	}

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
		} else {
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
			_destination->replace_this<int_member>(_value);
		} else {
			_destination->replace_this<double_member>(_value);
		}
	}
};

using int_member = native_member<int64_t>;
using double_member = native_member<double>;

}
}
}