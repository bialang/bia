#ifndef BIA_MEMBER_FUNCTION_GENERATOR_HPP_
#define BIA_MEMBER_FUNCTION_GENERATOR_HPP_

#include "../native/string.hpp"
#include "method.hpp"

namespace bia {
namespace member {
namespace function {

extern member* stop_iteration;

template<typename Parent>
class generator;

template<bool Refer, typename Function>
class generator<method<Refer, Function>> : public method<Refer, Function>
{
public:
	using method<Refer, Function>::method;

	member::test_type test(test_operator op, const member& right) const override
	{
		return _valid;
	}
	gc::gcable<member> copy() const override
	{
		return {};
		// return gc::gc::active_gc()->construct<iterator>(_instance, _function);
	}
	gc::gcable<member> invoke(member::parameters_type params) override
	{
		auto result = method<Refer, Function>::invoke(params);

		if (!(_valid = result.peek() != stop_iteration)) {
			return {};
		}

		return result;
	}
	gc::gcable<member> get(const native::string& name) override
	{
		if (!name.compare("__iter__")) {
			return this;
		}

		return method<Refer, Function>::get(name);
	}

private:
	bool _valid = false;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
