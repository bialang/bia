#include "int_member.hpp"


namespace bia
{
namespace framework
{
namespace native
{

int_member::int_member(int32_t _value)
{
	mpz_init2(_data.get(), std::max<int>(BIA_MIN_INT_SIZE, sizeof(_value) * 8));

	set(_value);
}

int_member::int_member(int64_t _value)
{
	mpz_init2(_data.get(), std::max<int>(BIA_MIN_INT_SIZE, sizeof(_value) * 8));

	set(_value);
}

int_member::int_member(mpz_t _value)
{
	mpz_init_set(_data.get(), _value);
}

int_member::int_member(const data_type & _data) noexcept : _data(_data)
{
}

int_member::~int_member()
{
	if (_data.only_owner()) {
		mpz_clear(_data.get());
	}
}

void int_member::print() const
{
	mpz_out_str(stdout, 10, _data.get());
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

int64_t int_member::to_int() const
{
	// Check if it fits
	if (false) {
		throw std::overflow_error("");
	}

	return convert<int64_t>();
}

double int_member::to_double() const
{
	return mpz_get_d(_data.get());
}

void * int_member::native_data(native::NATIVE_TYPE _type)
{
	return const_cast<void*>(native_data(_type));
}

const void * int_member::const_native_data(native::NATIVE_TYPE _type) const
{
	switch (_type) {
	case NATIVE_TYPE::BOOL:
		_tmp_value.bool_value = static_cast<bool>(_data.get()->_mp_size);

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
		_tmp_value.float_value = static_cast<float>(mpz_get_d(_data.get()));

		return &_tmp_value.float_value;
	case NATIVE_TYPE::DOUBLE:
		_tmp_value.double_value = mpz_get_d(_data.get());

		return &_tmp_value.double_value;
	default:
		break;
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

int32_t int_member::test() const
{
	return static_cast<bool>(_data.get()->_mp_size);
}

}
}
}