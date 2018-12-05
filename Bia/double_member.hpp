#pragma once

#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <type_traits>

#include "config.hpp"
#include "native_variable.hpp"
#include "share_def.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class double_member : public native_variable
{
public:
	typedef double double_type;
	typedef utility::share<double_type> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _value The initial value.
	 *
	 * @throws See utility::share::share().
	*/
	double_member(double _value);
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _data The data.
	*/
	double_member(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override;
	virtual int flags() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override;
	virtual int64_t to_int() const override;
	virtual double to_double() const override;

protected:
	virtual void * native_data(native::NATIVE_TYPE _type) override;
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const override;

private:
	union tmp_value
	{
		bool bool_value;
		int8_t int8_value;
		int16_t int16_value;
		int32_t int32_value;
		int64_t int64_value;
		float float_value;
	};

	/** Holds the float value. */
	data_type _data;
	/** A temporary value used for convertion. */
	static thread_local tmp_value _tmp_value;
};

}
}
}