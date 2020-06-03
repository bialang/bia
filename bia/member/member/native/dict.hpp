#ifndef BIA_MEMBER_NATIVE_DICT_HPP_
#define BIA_MEMBER_NATIVE_DICT_HPP_

#include "../member.hpp"
#include "../native/string.hpp"

#include <gc/object/pointer.hpp>
#include <map>
#include <thread/lock/guard.hpp>
#include <thread/lock/mutex.hpp>
#include <util/gsl.hpp>

namespace bia {
namespace member {
namespace native {

class dict : public member
{
public:
	struct compare
	{
		bool operator()(gc::object::immutable_pointer<const string> left,
		                gc::object::immutable_pointer<const string> right) const noexcept
		{
			return left->compare(*right) < 0;
		}
	};

	typedef std::map<gc::object::immutable_pointer<const string>, gc::object::pointer<member>, compare>
	    map_type;

	/**
	 * Constructor.
	 */
	dict() noexcept
	{}
	~dict()
	{
		printf("bye im getting destroyed: dict, %p\n", this);
	}
	void put(util::not_null<const string*> key, util::not_null<member*> value)
	{
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };

		_map.emplace(key.get(), value.get());
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };

		return !_map.empty();
	}
	gc::gcable<member> copy() const override
	{
		return {};
	}
	gc::gcable<member> invoke(gc::stack_view stack, parameter_count_type count) override
	{
		return copy();
	}
	gc::gcable<member> operation(const member& right, std::uint8_t op) override
	{
		return {};
	}
	member* get(const native::string& name) override
	{
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };
		const auto result = _map.find({ &name });

		if (result != _map.end()) {
			return result->second;
		}

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
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };

		for (const auto& i : _map) {
			gc_mark(i.first.get(), mark);
			gc_mark(i.second.get(), mark);
		}
	}
	const map_type& map() noexcept
	{
		return _map;
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{}

private:
	map_type _map;
	mutable thread::lock::mutex _mutex;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
