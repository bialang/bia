#pragma once

#include <cstdint>

#include "config.hpp"
#include "native_variable.hpp"
#include "share_def.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class int_member : public native_variable
{
public:
	typedef utility::share<int64_t> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.68.141.795
	 * @date 2-Dec-18
	 *
	 * @param _value The initial value.
	 *
	 * @throws See utility::share::share().
	*/
	BIA_EXPORT int_member(int32_t _value);
	/**
	 * Constructor.
	 *
	 * @since 3.68.141.795
	 * @date 2-Dec-18
	 *
	 * @param _value The initial value.
	 *
	 * @throws See utility::share::share().
	*/
	BIA_EXPORT int_member(int64_t _value);
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.68.141.795
	 * @date 2-Dec-18
	 *
	 * @param _data The data.
	*/
	BIA_EXPORT int_member(const data_type & _data) noexcept;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_t _operator, const member * _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_t _operator, int32_t _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_t _operator, int64_t _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_big_int(member * _destination, operator_t _operator, const dependency::big_int * _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_t _operator, double _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_t _name) override;
	BIA_EXPORT virtual int flags() const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_t _operator, member * _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_t _operator, int32_t _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_t _operator, int64_t _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_t _operator, double _right) const override;
	BIA_EXPORT virtual int64_t to_int() const override;
	BIA_EXPORT virtual double to_double() const override;
	BIA_EXPORT virtual const char * to_cstring(utility::buffer_builder * _builder) const override;

protected:
	BIA_EXPORT virtual int32_t int32_data() const override;
	BIA_EXPORT virtual int64_t int64_data() const override;
	BIA_EXPORT virtual double double_data() const override;

private:
	/** Holds the native integer. */
	data_type _data;
};

}
}
}