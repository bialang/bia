#include "big_int_member.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

thread_local big_int_member::tmp_value big_int_member::_tmp_value;

big_int_member::big_int_member()
{
}

big_int_member::big_int_member(int32_t _value) : _data(_value)
{
}

big_int_member::big_int_member(int64_t _value) : _data(_value)
{
}

big_int_member::big_int_member(const dependency::big_int & _value) : _data(_value)
{
}

big_int_member::big_int_member(const data_type & _data) noexcept : _data(_data)
{
}

void big_int_member::print() const
{
	_data->print(stdout);
	puts("");
}

void big_int_member::copy(member * _destination)
{
	_destination->template replace_this<big_int_member>(_data.get());
}

void big_int_member::refer(member * _destination)
{
	_destination->template replace_this<big_int_member>(_data);
}

void big_int_member::clone(member * _destination)
{
	copy(_destination);
}

void big_int_member::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int_member::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int_member::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int_member::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int_member::object_member(member * _destination, machine::string_manager::name_type _name)
{
	BIA_NOT_IMPLEMENTED;
}

int big_int_member::flags() const
{
	return F_BIG_INT | F_TO_INT | F_TO_DOUBLE;
}

int32_t big_int_member::test() const
{
	return static_cast<int32_t>(!_data->is_zero());
}

int32_t big_int_member::test_member(operator_type _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t big_int_member::test_int32(operator_type _operator, int32_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t big_int_member::test_int64(operator_type _operator, int64_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t big_int_member::test_double(operator_type _operator, double _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int64_t big_int_member::to_int() const
{
	return _data->to_int();
}

double big_int_member::to_double() const
{
	return _data->to_double();
}

void * big_int_member::native_data(native::NATIVE_TYPE _type)
{
	return const_cast<void*>(native_data(_type));
}

const void * big_int_member::const_native_data(native::NATIVE_TYPE _type) const
{
	switch (_type) {
	case NATIVE_TYPE::BOOL:
		_tmp_value.bool_value = !_data->is_zero();

		return &_tmp_value.bool_value;
	/*case NATIVE_TYPE::INT_8:
		_tmp_value.int8_value = convert<int8_t>();

		return &_tmp_value.int8_value;
	case NATIVE_TYPE::INT_16:
		_tmp_value.int16_value = convert<int16_t>();

		return &_tmp_value.int16_value;
	case NATIVE_TYPE::INT_32:
		_tmp_value.int32_value = convert<int32_t>();

		return &_tmp_value.int32_value;*/
	case NATIVE_TYPE::INT_64:
		_tmp_value.int64_value = _data->to_int();

		return &_tmp_value.int64_value;
	case NATIVE_TYPE::FLOAT:
		_tmp_value.float_value = static_cast<float>(_data->to_double());

		return &_tmp_value.float_value;
	case NATIVE_TYPE::DOUBLE:
		_tmp_value.double_value = _data->to_double();

		return &_tmp_value.double_value;
	default:
		break;
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

}
}
}