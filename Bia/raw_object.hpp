#pragma once

#include <type_traits>
#include <cstdarg>
#include <utility>

#include "object_variable.hpp"
#include "constructor_chain.hpp"
#include "machine_context.hpp"
#include "instance_holder.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
class raw_object : public object_variable
{
public:
	typedef instance_holder<Type> data_type;

	/**
	 * Move-Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @tparam Ty The real type.
	 * @tparam Switch Enables this constructor if @a Ty is valid.
	 *
	 * @param [in,out] _object The object that should be set.
	 *
	 * @throws See constructor_chain().
	*/
	template<typename Ty, typename Switch = typename std::enable_if<std::is_same<typename std::remove_cv<typename std::remove_reference<Ty>::type>::type, typename std::remove_cv<typename std::remove_reference<Type>::type>::type>::value, int>::type>
	raw_object(Ty && _object) : _data(constructor_chain_wrapper<Type>(machine::machine_context::active_allocator(), std::forward<Ty>(_object)), true)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @param _data The data.
	*/
	raw_object(const data_type & _data) noexcept : _data(_data)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @param [in] _object The object address. This address must not be null.
	 * @param _owner true if this object is in charge of deallocating the object or not.
	*/
	raw_object(machine::memory::allocation<Type> _object, bool _owner) noexcept : _data(_object, _owner)
	{
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		printf("<%s at %p>\n", typeid(Type).name(), this);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		_destination->replace_this<raw_object<Type>>(constructor_chain_wrapper<Type>(machine::machine_context::active_allocator(), *_data.get()), true);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<raw_object<Type>>(_data);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		promote()->execute(_destination);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override
	{
		BIA_NOT_IMPLEMENTED;
		auto _this = promote();
		force::va_list_wrapper _args;
		va_start(_args.args, _count);

		_this->execute_count(_destination, _reserved, _count, _args.args);

		va_end(_args.args);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		BIA_NOT_IMPLEMENTED;
		auto _this = promote();
		force::va_list_wrapper _args;
		va_start(_args.args, _count);

		_this->execute_format(_destination, _format, _count, _args.args);

		va_end(_args.args);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		return promote()->operator_call(_destination, _operator, _right);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		return promote()->operator_call_int32(_destination, _operator, _right);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		return promote()->operator_call_int64(_destination, _operator, _right);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		return promote()->operator_call_double(_destination, _operator, _right);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override
	{
		promote()->object_member(_destination, _name);
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override
	{
		return promote()->test();
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override
	{
		return promote()->test_member(_operator, _right);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override
	{
		return promote()->test_int32(_operator, _right);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override
	{
		return promote()->test_int64(_operator, _right);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override
	{
		return promote()->test_double(_operator, _right);
	}
	virtual int64_t to_int() const override
	{
		return promote()->to_int();
	}
	virtual double to_double() const override
	{
		return promote()->to_double();
	}
	member * promote() const
	{
		return nullptr;
	}

protected:
	virtual void * data(const std::type_info & _type) override
	{
		if (!std::is_const<Type>::value) {
			if (typeid(Type) == _type) {
				return const_cast<typename std::remove_cv<Type>::type*>(static_cast<Type*>(_data.get()));
			} else if (typeid(Type*) == _type) {
				return &_data.get();
			}
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_data(const std::type_info & _type) const override
	{
		if (typeid(Type) == _type) {
			return _data.get();
		} else if (typeid(Type*) == _type) {
			return &_data.get();
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	data_type _data;
};

}
}
}
