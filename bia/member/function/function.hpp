#ifndef BIA_MEMBER_FUNCTION_FUNCTION_HPP_
#define BIA_MEMBER_FUNCTION_FUNCTION_HPP_

#include "../member.hpp"

#include <bia/gc/object/pointer.hpp>
#include <bia/gc/stack_view.hpp>
#include <bia/log/log.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/util/gsl.hpp>
#include <vector>

namespace bia {
namespace member {
namespace function {

class function : public member
{
public:
	typedef std::vector<std::pair<std::size_t, member*>> bindings_type;

	function(gc::object::immutable_pointer<const util::byte> data, std::size_t code_size,
	         std::size_t binding_size, bindings_type bindings = {}) noexcept
	    : _code{ data }, _size{ code_size }, _binding_size{ binding_size }, _bindings{ std::move(bindings) }
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
		return gc::gc::active_gc()->construct<function>(*this);
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
		return {};
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

		for (const auto& i : _bindings) {
			if (i.second) {
				gc::object::gc_mark(i.second, mark);
			}
		}
	}
	gc::gcable<member> initiate(const gc::stack_view& parent)
	{
		bindings_type bindings;

		// bind variables
		util::span<const util::byte*> binding_input{ _code.get() + _size, _binding_size };

		while (!binding_input.empty()) {
			const auto binding = resource::deserialize_binding(binding_input);

			bindings.push_back({ binding.second, parent.local_at(binding.first) });
			BIA_LOG(DEBUG, "binding {} to {}", binding.first, binding.second);
		}

		return gc::gc::active_gc()->construct<function>(_code, _size, _binding_size, std::move(bindings));
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{
		gc.register_gcable(_code.get());

		for (const auto& i : _bindings) {
			gc.register_gcable(i.second);
		}
	}

private:
	gc::object::immutable_pointer<const util::byte> _code;
	const std::size_t _size;
	const std::size_t _binding_size;
	const bindings_type _bindings;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
