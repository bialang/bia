#pragma once

#include <type_traits>
#include <cstdarg>
#include <utility>

#include "member.hpp"
#include "undefined_member.hpp"
#include "share.hpp"
#include "type_traits.hpp"
#include "constructor_chain.hpp"
#include "machine_context.hpp"
#include "static_function.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty>
class raw_object : public member
{
public:
	/** The data of @ref raw_object. The first parameter is a pointer to the real data and the second is a boolean defining whether the first parameter needs to be deallocated or not. */
	typedef utility::share<std::pair<_Ty*, bool>> data_type;

	/**
	 * Move-Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @param [in,out] _object The object that should be set.
	 *
	 * @throws See constructor_chain().
	*/
	template<typename _T, typename A = typename std::enable_if<std::is_same<typename std::remove_cv<typename std::remove_reference<_T>::type>::type, typename std::remove_cv<typename std::remove_reference<_Ty>::type>::type>::value, int>::type>
	raw_object(_T && _object) : _data(nullptr, false)
	{
		_data.get().first = constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), std::forward<_T>(_object));
		_data.get().second = true;
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
	raw_object(_Ty * _object, bool _owner) noexcept : _data(nullptr, _owner)
	{
	}
	/**
	 * Destructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @throws See machine::memory::allocator::destroy().
	*/
	~raw_object()
	{
		if (_data.only_owner() && _data.get().second) {
			machine::machine_context::active_allocator()->destroy<_Ty>({ _data.get().first, sizeof(_Ty) });
		}
	}
	virtual void undefine() noexcept override
	{
		replace_this<undefined_member>();
	}
	virtual void print() const override
	{
		printf("<%s at %p>\n", typeid(_Ty).name(), this);
	}
	virtual void copy(member * _destination) override
	{
		_destination->replace_this<raw_object<_Ty>>(constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), *_data.get().first), true);
	}
	virtual void refer(member * _destination) override
	{
		_destination->replace_this<raw_object<_Ty>>(_data);
	}
	virtual void clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void execute(member * _destination) override
	{
		promote()->execute(_destination);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		auto _this = promote();
		va_list _args;
		va_start(_args, _count);

		_this->execute_count(_destination, _count, _args);

		va_end(_args);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		auto _this = promote();
		va_list _args;
		va_start(_args, _count);

		_this->execute_format(_destination, _format, _count, _args);

		va_end(_args);
	}
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		return promote()->operator_call(_destination, _operator, _right);
	}
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		return promote()->operator_call_int32(_destination, _operator, _right);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		return promote()->operator_call_int64(_destination, _operator, _right);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		return promote()->operator_call_double(_destination, _operator, _right);
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t test() const override
	{
		return promote()->test();
	}
	virtual int32_t test_member(operator_type _operator, member * _right) const override
	{
		return promote()->test_member(_operator, _right);
	}
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override
	{
		return promote()->test_int32(_operator, _right);
	}
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override
	{
		return promote()->test_int64(_operator, _right);
	}
	virtual int32_t test_double(operator_type _operator, double _right) const override
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
	virtual member * object_member(machine::string_manager::name_type _name) override
	{
		static executable::static_function<void, int> a(&raw_object<_Ty>::asd);
		printf("your addr: %p\n", &a);
		return &a;

		BIA_NOT_IMPLEMENTED;
	}
	static void asd(int a)
	{
		printf("michse said hello%i\n", a);
	}
	member * promote() const
	{
		return nullptr;
	}

protected:
	virtual void * native_data(native::NATIVE_TYPE _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual void * data(const std::type_info & _type) override
	{
		if (!std::is_const<_Ty>::value) {
			if (typeid(_Ty) == _type) {
				return const_cast<typename std::remove_cv<_Ty>::type*>(_data.get().first);
			} else if (typeid(_Ty*) == _type) {
				return &_data.get().first;
			}
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_data(const std::type_info & _type) const override
	{
		if (typeid(_Ty) == _type) {
			return _data.get().first;
		} else if (typeid(_Ty*) == _type) {
			return &_data.get().first;
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	data_type _data;
};

}
}
}