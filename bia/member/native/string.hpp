#ifndef BIA_MEMBER_NATIVE_STRING_HPP_
#define BIA_MEMBER_NATIVE_STRING_HPP_

#include "../member.hpp"

#include <bia/gc/gc.hpp>
#include <bia/gc/object/pointer.hpp>
#include <bia/log/log.hpp>
#include <cstring>

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
	string(gc::object::immutable_pointer<char> value) noexcept : _value(value)
	{}
	~string()
	{
		BIA_LOG(DEBUG, "destroying string='{}': {}", _value.get(), static_cast<void*>(this));
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return _value.get()[0] ? 1 : 0;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<string>(_value).template to<member>();
	}
	gc::gcable<member> invoke(parameters_type params) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		if (op == infix_operator::addition && dynamic_cast<const string*>(&right)) {
			const auto len0 = std::char_traits<char>::length(_value.get());
			const auto len1 =
			    std::char_traits<char>::length(static_cast<const string*>(&right)->_value.get());
			auto mem = gc::gc::active_gc()->allocate(len0 + len1 + 1);

			std::memcpy(mem.peek(), _value.get(), len0);
			std::memcpy(static_cast<char*>(mem.peek()) + len0,
			            static_cast<const string*>(&right)->_value.get(), len1);

			static_cast<char*>(mem.peek())[len0 + len1] = 0;

			return gc::gc::active_gc()
			    ->construct<string>(static_cast<char*>(mem.release()))
			    .template to<member>();
		}

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
		if (type == typeid(const char*)) {
			*static_cast<const char**>(output) = _value.get();

			return true;
		}

		return false;
	}
	int compare(const string& other) const noexcept
	{
		return std::strcmp(_value.get(), other._value.get());
	}
	void gc_mark_children(bool mark) const noexcept override
	{
		gc::object::gc_mark(_value.get(), mark);
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{
		gc.register_gcable(_value.get());
	}

private:
	/** the garbage collectible string */
	gc::object::immutable_pointer<char> _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
