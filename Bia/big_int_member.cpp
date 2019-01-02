#include "big_int_member.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename Right>
inline void big_int_member_operation(dependency::big_int & _left, dependency::big_int & _destination, operator_type _operator, Right && _right)
{
	switch (_operator) {
	case O_ASSIGN:
		_left.set(_right);

		return;
	case O_ASSIGN_PLUS:
	case O_PLUS:
	{
		_left.add(_right, _destination);

		return;
	}
	case O_ASSIGN_MINUS:
	case O_MINUS:
	{
		_left.subtract(_right, _destination);

		return;
	}
	case O_ASSIGN_MULTIPLY:
	case O_MULTIPLY:
	{
		_left.multiply(_right, _destination);

		return;
	}
	case O_ASSIGN_DIVIDE:
	case O_DIVIDE:
	{
		_left.divide(_right, _destination);

		return;
	}
	case O_ASSIGN_MODULUS:
	case O_MODULUS:
	{
		_left.modulo(_right, _destination);

		return;
	}
	case O_ASSIGN_DOUBLE_MULTIPLY:
	case O_DOUBLE_MULTIPLY:
	{
		_left.power(_right, _destination);

		return;
	}
	default:
		break;
	}

	throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
}

template<typename Right>
inline void big_int_member_operation(dependency::big_int & _left, operator_type _operator, Right && _right)
{
	switch (_operator) {
	case O_ASSIGN:
		_left.set(_right);

		return;
	case O_ASSIGN_PLUS:
	case O_PLUS:
	{
		_left.add(_right);

		return;
	}
	case O_ASSIGN_MINUS:
	case O_MINUS:
	{
		_left.subtract(_right);

		return;
	}
	case O_ASSIGN_MULTIPLY:
	case O_MULTIPLY:
	{
		_left.multiply(_right);

		return;
	}
	case O_ASSIGN_DIVIDE:
	case O_DIVIDE:
	{
		_left.divide(_right);

		return;
	}
	case O_ASSIGN_MODULUS:
	case O_MODULUS:
	{
		_left.modulo(_right);

		return;
	}
	case O_ASSIGN_DOUBLE_MULTIPLY:
	case O_DOUBLE_MULTIPLY:
	{
		_left.power(_right);

		return;
	}
	default:
		break;
	}

	throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
}


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
	auto _flags = _right->flags();

	if (_flags & F_BIG_INT) {
		if (_destination == this) {
			big_int_member_operation(_data.get(), _operator, static_cast<const big_int_member*>(_right)->_data.get());
		} else {
			big_int_member_operation(_data.get(), _destination->template replace_this<big_int_member>()->_data.get(), _operator, static_cast<const big_int_member*>(_right)->_data.get());
		}

		return;
	}

	BIA_NOT_IMPLEMENTED;
}

void big_int_member::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	if (_destination == this) {
		big_int_member_operation(_data.get(), _operator, _right);
	} else {
		big_int_member_operation(_data.get(), _destination->template replace_this<big_int_member>()->_data.get(), _operator, _right);
	}
}

void big_int_member::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	if (_destination == this) {
		big_int_member_operation(_data.get(), _operator, _right);
	} else {
		big_int_member_operation(_data.get(), _destination->template replace_this<big_int_member>()->_data.get(), _operator, _right);
	}
}

void BIA_MEMBER_CALLING_CONVENTION big_int_member::operator_call_big_int(member * _destination, operator_type _operator, const dependency::big_int * _right)
{
	if (_destination == this) {
		big_int_member_operation(_data.get(), _operator, *_right);
	} else {
		big_int_member_operation(_data.get(), _destination->template replace_this<big_int_member>()->_data.get(), _operator, *_right);
	}
}

void big_int_member::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	if (_destination == this) {
		big_int_member_operation(_data.get(), _operator, _right);
	} else {
		big_int_member_operation(_data.get(), _destination->template replace_this<big_int_member>()->_data.get(), _operator, _right);
	}
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
	if (_operator == O_EQUALS && _right->flags() & F_BIG_INT) {
		return _data->compare(static_cast<big_int_member*>(_right)->_data.get()) == 0;
	}

	BIA_NOT_IMPLEMENTED;
}

int32_t big_int_member::test_int32(operator_type _operator, int32_t _right) const
{
	if (_operator == O_EQUALS) {
		return _data->compare(_right) == 0;
	}

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

const char * big_int_member::to_cstring(utility::buffer_builder * _builder) const
{
	_data->to_string(*_builder);

	return _builder->buffer<char>();
}

int32_t big_int_member::int32_data() const
{
	return static_cast<int32_t>(_data->cast_int());
}

int64_t big_int_member::int64_data() const
{
	return _data->cast_int();
}

double big_int_member::double_data() const
{
	return _data->cast_double();
}

}
}
}