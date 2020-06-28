#ifndef BIA_MEMBER_FUNCTION_GENERATOR_HPP_
#define BIA_MEMBER_FUNCTION_GENERATOR_HPP_

#include "method.hpp"

namespace bia {
namespace member {
namespace function {

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

		_valid = result.peek();

		return result;
	}

private:
	bool _valid = false;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
