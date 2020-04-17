#ifndef BIA_MEMBER_NATIVE_DICT_HPP_
#define BIA_MEMBER_NATIVE_DICT_HPP_

#include "../function/static_.hpp"
#include "../member.hpp"

#include <gc/object/pointer.hpp>
#include <map>
#include <thread/lock/guard.hpp>
#include <thread/lock/mutex.hpp>

namespace bia {
namespace member {
namespace native {

class dict : public member
{
public:
	/**
	 * Constructor.
	 */
	dict() noexcept
	{}
	~dict()
	{
		printf("bye im getting destroyed: dict, %p\n", this);
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
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
	member* get(const native::string& name) override
	{
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };
		const auto result = _map.find({ &name });

		if (result != _map.end()) {
			return result->second;
		}

		return nullptr;
	}

protected:
	void gc_mark_children(bool mark) const noexcept override
	{
		thread::lock::guard<thread::lock::mutex> lock{ _mutex };

		for (const auto& i : _map) {
			gc_mark(i.first.get(), mark);
			gc_mark(i.second.get(), mark);
		}
	}

private:
	struct compare
	{
		bool operator()(gc::object::immutable_pointer<const string> left,
		                gc::object::immutable_pointer<const string> right) const noexcept
		{
			return left->compare(*right) < 0;
		}
	};

	std::map<gc::object::immutable_pointer<const string>, gc::object::pointer<member>, compare> _map;
	mutable thread::lock::mutex _mutex;
};

} // namespace native
} // namespace member
} // namespace bia

#endif