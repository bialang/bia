#pragma once

#include <cstdint>
#include <cstdlib>
#include <algorithm>

#include "config.hpp"
#include "native_variable.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

#include <mpir/mpir.h>


class int_member : public native_variable
{
public:
	typedef utility::share<__mpz_struct> data_type;


	/**
	 * Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _value The value of the MPIR big integer.
	 *
	 * @throws See utility::share::share().
	*/
	int_member(int32_t _value);
	/**
	 * Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _value The value of the MPIR big integer.
	 *
	 * @throws See utility::share::share().
	*/
	int_member(int64_t _value);
	/**
	 * Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _value The value of the MPIR big integer.
	 *
	 * @throws See utility::share::share().
	*/
	int_member(mpz_t _value);
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @param _data The data.
	*/
	int_member(const data_type & _data) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	*/
	~int_member();
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
		double double_value;
	};

	/** Holds the MPIR big integer. */
	data_type _data;
	/** A temporary value used for convertion. */
	static thread_local tmp_value _tmp_value;

	/**
	 * Converts the signed C++ integral to an MPIR integer.
	 *
	 * @remarks The MPIR integer must be large enough to hold the C++ type.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @tparam Type The signed C++ integral.
	 *
	 * @param _signed The signed value.
	*/
	template<typename Type>
	void set(Type _signed) noexcept
	{
		auto _value = &_data.get();
		auto _unsigned = abs(_signed);
		constexpr auto _needed = (sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;

		for (_value->_mp_size = 0; _value->_mp_size < _needed && _unsigned; ++_value->_mp_size) {
			_value->_mp_d[_value->_mp_size] = _unsigned & GMP_NUMB_MASK;
			_unsigned >>= GMP_NUMB_BITS;
		}

		if (_signed < 0) {
			_value->_mp_size = -_value->_mp_size;
		}
	}
	/**
	 * Converts the MPIR integer to a signed C++ integral.
	 *
	 * @remarks If the type can't hold all the data, only the least significant bits will be converted.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @tparam Type The signed C++ integral.
	 *
	 * @return The converted value.
	*/
	template<typename Type>
	Type convert() const noexcept
	{
		Type _converted = 0;
		auto _value = &_data.get();
		auto _needed = std::min<int64_t>((sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS, abs(_value->_mp_size));

		while (_needed--) {
			_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_needed] & GMP_NUMB_MASK;
		}

		return _value->_mp_size < 0 ? -_converted : _converted;
	}
};

}
}
}