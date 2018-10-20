#include "double_member.hpp"


namespace bia
{
namespace framework
{
namespace native
{

thread_local double_member::tmp_value double_member::_tmp_value;

double_member::double_member(double _value)
{
	mpf_init2(_data.get(), BIA_MIN_FLOAT_PRECISION);
	mpf_set_d(_data.get(), _value);
}

double_member::double_member(mpf_t _value)
{
	mpf_init_set(_data.get(), _value);
}

double_member::double_member(const data_type & _data) noexcept : _data(_data)
{
}

double_member::~double_member()
{
	if (_data.only_owner()) {
		mpf_clear(_data.get());
	}
}

void double_member::print() const
{
	mpf_out_str(stdout, 10, 0, _data.get());
}

void double_member::copy(member * _destination)
{
	_destination->replace_this<double_member>(_data.get());
}

void double_member::refer(member * _destination)
{
	_destination->replace_this<double_member>(_data);
}

void double_member::clone(member * _destination)
{
	copy(_destination);
}

int64_t double_member::to_int() const
{
	if (false) {
		throw std::overflow_error("");
	}

	return convert<int64_t>();
}

double double_member::to_double() const
{
	return mpf_get_d(_data.get());
}

void * double_member::native_data(native::NATIVE_TYPE _type)
{
	return const_cast<void*>(const_native_data(_type));
}

const void * double_member::const_native_data(native::NATIVE_TYPE _type) const
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
		_tmp_value.float_value = static_cast<float>(mpf_get_d(_data.get()));

		return &_tmp_value.float_value;
	case NATIVE_TYPE::DOUBLE:
		_tmp_value.double_value = mpf_get_d(_data.get());

		return &_tmp_value.double_value;
	default:
		break;
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

}
}
}