#include "int_member.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

thread_local int_member::tmp_value int_member::_tmp_value;

int_member::int_member(int32_t _value) : _data(_value)
{
}

int_member::int_member(int64_t _value) : _data(_value)
{
}

int_member::int_member(const dependency::big_int & _value) : _data(_value)
{
}

int_member::int_member(const data_type & _data) noexcept : _data(_data)
{
}

int_member::~int_member()
{
}

void int_member::print() const
{
	//mpz_out_str(stdout, 10, &_data.get());
	puts("");
}

void int_member::copy(member * _destination)
{
	_destination->template replace_this<int_member>(_data.get());
}

void int_member::refer(member * _destination)
{
	_destination->template replace_this<int_member>(_data);
}

void int_member::clone(member * _destination)
{
	copy(_destination);
}

void int_member::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void int_member::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void int_member::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void int_member::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	BIA_NOT_IMPLEMENTED;
}

void int_member::object_member(member * _destination, machine::string_manager::name_type _name)
{
	BIA_NOT_IMPLEMENTED;
}

int int_member::flags() const
{
	return 0;
}

int32_t int_member::test() const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t int_member::test_member(operator_type _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t int_member::test_int32(operator_type _operator, int32_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t int_member::test_int64(operator_type _operator, int64_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t int_member::test_double(operator_type _operator, double _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int64_t int_member::to_int() const
{
	BIA_NOT_IMPLEMENTED;
}

double int_member::to_double() const
{
	BIA_NOT_IMPLEMENTED;
}

void * int_member::native_data(native::NATIVE_TYPE _type)
{
	return const_cast<void*>(native_data(_type));
}

const void * int_member::const_native_data(native::NATIVE_TYPE _type) const
{
	BIA_NOT_IMPLEMENTED;
	/*switch (_type) {
	case NATIVE_TYPE::BOOL:
		_tmp_value.bool_value = static_cast<bool>(_data.get()._mp_size);

		return &_tmp_value.bool_value;
	case NATIVE_TYPE::INT_8:
		_tmp_value.int8_value = convert<int8_t>();

		return &_tmp_value.int8_value;
	case NATIVE_TYPE::INT_16:
		_tmp_value.int16_value = convert<int16_t>();

		return &_tmp_value.int16_value;
	case NATIVE_TYPE::INT_32:
		_tmp_value.int32_value = convert<int32_t>();

		return &_tmp_value.int32_value;
	case NATIVE_TYPE::INT_64:
		_tmp_value.int64_value = convert<int64_t>();

		return &_tmp_value.int64_value;
	case NATIVE_TYPE::FLOAT:
		_tmp_value.float_value = static_cast<float>(mpz_get_d(&_data.get()));

		return &_tmp_value.float_value;
	case NATIVE_TYPE::DOUBLE:
		_tmp_value.double_value = mpz_get_d(&_data.get());

		return &_tmp_value.double_value;
	default:
		break;
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);*/
}

}
}
}