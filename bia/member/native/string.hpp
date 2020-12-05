#ifndef BIA_MEMBER_NATIVE_STRING_HPP_
#define BIA_MEMBER_NATIVE_STRING_HPP_

#include "../member.hpp"

#include <bia/gc/object/pointer.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace member {
namespace native {

class string : public member
{
public:
	/**
	 * Constructor.
	 *
	 * @param value the string
	 */
	string(gc::object::immutable_pointer<char> value) noexcept;
	~string();
	flag_type flags() const override;
	test_type test(test_operator op, const member& right) const override;
	gc::gcable<member> copy() const override;
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override;
	gc::gcable<member> operation(const member& right, infix_operator op) override;
	gc::gcable<member> self_operation(self_operator op) override;
	gc::gcable<member> get(const native::string& name) override;
	bool as_data(const std::type_info& type, void* output) override;
	bool as_data(const std::type_info& type, void* output) const override;
	int compare(const string& other) const noexcept;
	int compare(util::czstring other) const noexcept;
	void gc_mark_children(bool mark) const noexcept override;
	gc::object::immutable_pointer<char> value() const;

protected:
	void register_gcables(gc::gc& gc) const noexcept override;

private:
	/** the garbage collectible string */
	gc::object::immutable_pointer<char> _value;

	gc::gcable<string> _lower() const;
	gc::gcable<string> _upper() const;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
