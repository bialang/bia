#pragma once

#include <cstddef>

#include "native_variable.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class cstring_member final : public native_variable
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _string The zero-terminated string.
	*/
	cstring_member(const char * _string) noexcept;
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _string The zero-terminated string.
	 * @param _length The length of the string.
	*/
	cstring_member(const char * _string, size_t _length) noexcept;
	virtual void print() const override;
	virtual void clone(member * _destination) override;
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) override;
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override;
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override;
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) override;
	virtual int get_flags() const override;
	virtual int32_t test() const override;
	virtual int32_t test_member(operator_type _operator, member * _right) const override;
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override;
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override;
	virtual int32_t test_double(operator_type _operator, double _right) const override;
	virtual int64_t to_int() const override;
	virtual double to_double() const override;

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override;
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override;

private:
	/** The zero-terminated C style pointer. */
	const char * _string;
	/** The length of the string. */
	size_t _length;
};

}
}
}