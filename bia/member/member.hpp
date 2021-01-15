#ifndef BIA_MEMBER_MEMBER_HPP_
#define BIA_MEMBER_MEMBER_HPP_

#include "operator_.hpp"

#include <bia/gc/gcable.hpp>
#include <bia/gc/object/base.hpp>
#include <cstdint>
#include <typeinfo>

namespace bia {
namespace member {
namespace native {

class string;

} // namespace native

/**
 * The base type for all member types. All members are gc objects and must provide the following functions.
 */
class member : public gc::object::base
{
public:
	/** the flag type */
	typedef int flag_type;
	/** the type for testing operations; is able to hold at least: -1, 0 and 1 */
	typedef int test_type;

	/**
	 * Additional flags describing the member and how its going to behave in certain situations.
	 */
	enum flag : flag_type
	{
		flag_none = 0,
		/** if set a clone operations should be a copy; this is intended for easy to copy and mutable members
		 */
		flag_clone_is_copy = 0x1,
		/** if the member has a native numerical representaion */
		flag_numeric        = 0x2,
		flag_floating_point = flag_numeric | 0x4
	};

	virtual ~member() = default;
	/**
	 * Returns the set flags of this member.
	 *
	 * @returns the flags
	 */
	virtual flag_type flags() const = 0;
	/**
	 * Tests this member.
	 *
	 * @note if the operation type is `test_operator::self`, right must be `*this`
	 *
	 * @param op the operation type
	 * @param right the right-hand side
	 * @returns `1` if the test succeeded, otherwise `0`
	 */
	virtual test_type test(test_operator op, const member& right) const = 0;
	/**
	 * Creates a new copy of this member.
	 *
	 * @returns a fresh copy of this member
	 */
	virtual gc::gcable<member> copy() const = 0;
	/**
	 * Executes an infix operation on this member and returns the result.
	 *
	 * @param right the right hand side of the operation
	 * @param op the operation type
	 * @returns the result of this operation
	 */
	virtual gc::gcable<member> operation(const member& right, infix_operator op) = 0;
	/**
	 * Executes a self operation on this member and returns the result.
	 *
	 * @param op the operation type
	 * @returns the result of this operation
	 */
	virtual gc::gcable<member> self_operation(self_operator op) = 0;
	/**
	 * Returns the member with the specified name.
	 *
	 * @param name the name of the member
	 * @returns the member or `nullptr` if it does not exist
	 */
	virtual gc::gcable<member> get(const native::string& name)           = 0;
	virtual bool as_data(const std::type_info& type, void* output)       = 0;
	virtual bool as_data(const std::type_info& type, void* output) const = 0;
};

} // namespace member
} // namespace bia

#endif
