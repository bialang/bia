#pragma once

#include "native_variable.hpp"
#include "share_def.hpp"
#include "string_resource.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename Char_type>
class cstring_member final : public native_variable
{
public:
	typedef machine::string_manager::string_t data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _string The zero-terminated string.
	 *
	 * @throws See utility::share::share().
	*/
	cstring_member(const Char_type * _string);
	cstring_member(machine::string_manager::string_wrapper<Char_type> _string) noexcept;
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.65.134.742
	 * @date 1-Aug-18
	 *
	 * @param _data The data of the referred object.
	*/
	cstring_member(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_t _operator, const member * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_t _operator, int32_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_t _operator, int64_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_big_int(member * _destination, operator_t _operator, const dependency::big_int * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_t _operator, double _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::name_manager::name_t _name) override;
	virtual int flags() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_t _operator, member * _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_t _operator, int32_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_t _operator, int64_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_t _operator, double _right) const override;
	virtual int64_t to_int() const override;
	virtual double to_double() const override;
	const char * to_cstring(utility::buffer_builder * _builder) const override;

protected:
	virtual void * data(const std::type_info & _type, bool & _success) override;
	virtual const void * const_data(const std::type_info & _type, bool & _success) const override;

private:
	/** The zero-terminated C style string, its size and its length. */
	data_type _data;

	static void print(const char * _string);
	template<typename Type>
	static void print(const Type * _string) noexcept;
};

}
}
}
