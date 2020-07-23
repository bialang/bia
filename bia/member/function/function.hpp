#ifndef BIA_MEMBER_FUNCTION_FUNCTION_HPP_
#define BIA_MEMBER_FUNCTION_FUNCTION_HPP_

#include "../member.hpp"

#include <bia/gc/object/pointer.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace member {
namespace function {

class function : public member
{
public:
	function(util::span<const util::byte*> code) noexcept : _code{ code.data() }, _size{ code.size() }
	{}
	~function()
	{}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test(test_operator op, const member& right) const override
	{
		return 1;
	}
	gc::gcable<member> copy() const override
	{
		return {};
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override;
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		return {};
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		return {};
	}
	gc::gcable<member> get(const native::string& name) override
	{
		return nullptr;
	}
	float_type as_float() const noexcept override
	{
		return {};
	}
	int_type as_int() const noexcept override
	{
		return {};
	}
	bool as_data(const std::type_info& type, void* output) override
	{
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		return false;
	}
	void gc_mark_children(bool mark) const noexcept override
	{
		gc::object::gc_mark(_code.get(), mark);
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{
		gc.register_gcable(_code.get());
	}

private:
	gc::object::immutable_pointer<const util::byte> _code;
	const std::size_t _size;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
