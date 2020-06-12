#ifndef BIA_MEMBER_NATIVE_KEY_VALUE_PAIR_HPP_
#define BIA_MEMBER_NATIVE_KEY_VALUE_PAIR_HPP_

#include "../member.hpp"
#include "string.hpp"

#include <bia/gc/gc.hpp>
#include <bia/gc/object/pointer.hpp>
#include <bia/log/log.hpp>
#include <cstring>

namespace bia {
namespace member {
namespace native {

class key_value_pair : public member
{
public:
	/**
	 * Constructor.
	 *
	 * @param key the key part
	 * @param value the value part
	 */
	key_value_pair(string* key, member* value) noexcept : _key{ key }, _value{ value }
	{}
	~key_value_pair()
	{
		BIA_LOG(DEBUG, "destroying key_value={}: {}: {}", _key.get(), _value.get(), static_cast<void*>(this));
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test(test_operator op, const member& right) const override
	{
		return 0;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<key_value_pair>(_key.get(), _value.get()).template to<member>();
	}
	gc::gcable<member> invoke(parameters_type params) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		return {};
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		return {};
	}
	member* get(const native::string& name) override
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
	string* key() const noexcept
	{
		return _key.get();
	}
	member* value() const noexcept
	{
		return _value.get();
	}
	void gc_mark_children(bool mark) const noexcept override
	{
		if (_key.get()) {
			gc::object::gc_mark(_key.get(), mark);
		}

		if (_value.get()) {
			gc::object::gc_mark(_value.get(), mark);
		}
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{}

private:
	gc::object::immutable_pointer<string> _key;
	gc::object::immutable_pointer<member> _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
