#ifndef BIA_MEMBER_NATIVE_DETAIL_REGEX_MATCH_HPP_
#define BIA_MEMBER_NATIVE_DETAIL_REGEX_MATCH_HPP_

#include "../../member.hpp"

#include <bia/gc/object/pointer.hpp>
#include <regex>

namespace bia {
namespace member {
namespace native {
namespace detail {

class regex_match : public member
{
public:
	regex_match(gc::object::immutable_pointer<char> string, std::cmatch match);
	flag_type flags() const override;
	test_type test(test_operator op, const member& right) const override;
	gc::gcable<member> copy() const override;
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override;
	gc::gcable<member> operation(const member& right, infix_operator op) override;
	gc::gcable<member> self_operation(self_operator op) override;
	gc::gcable<member> get(const native::string& name) override;
	float_type as_float() const noexcept override;
	int_type as_int() const noexcept override;
	bool as_data(const std::type_info& type, void* output) override;
	bool as_data(const std::type_info& type, void* output) const override;
	void gc_mark_children(bool mark) const noexcept override;

protected:
	void register_gcables(gc::gc& gc) const noexcept override;

private:
	gc::object::immutable_pointer<char> _string;
	std::cmatch _match;

	gc::gcable<string> _group(std::size_t index) const;
};

} // namespace detail
} // namespace native
} // namespace member
} // namespace bia

#endif
