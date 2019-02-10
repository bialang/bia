#pragma once

#include <type_traits>

#include "object_variable.hpp"
#include "instance_holder_def.hpp"


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
	raw_object(Ty && _object);
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @param _data The data.
	*/
	raw_object(const data_type & _data) noexcept;
	/**
	 * Constructor.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @param [in] _object The object address. This address must not be null.
	 * @param _owner true if this object is in charge of deallocating the object or not.
	*/
	raw_object(machine::memory::allocation<Type> _object, bool _owner) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count, machine::stack * _stack) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_t _operator, const member * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_t _operator, int32_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_t _operator, int64_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_t _operator, double _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_t _name) override;
	virtual int flags() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_t _operator, member * _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_t _operator, int32_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_t _operator, int64_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_t _operator, double _right) const override;
	virtual int64_t to_int() const override;
	virtual double to_double() const override;
	member * promote() const;

protected:
	virtual void * data(const std::type_info & _type) override;
	virtual const void * const_data(const std::type_info & _type) const override;

private:
	data_type _data;
};

}
}
}
