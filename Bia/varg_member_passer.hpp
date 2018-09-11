#pragma once

#include "static_passer.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

class varg_member_passer : protected static_passer
{
public:
	varg_member_passer(passer & _passer) noexcept : static_passer(_passer)
	{
		_caller_pops_parameters = true;
		_caller_pops_padding = true;

#if defined(BIA_ARCHITECTURE_X86_32)
		_integral_passed = 2;
		_floating_point_passed = 0;
#elif defined(BIA_COMPILER_MSVC)
		_integral_passed = 4;
		_floating_point_passed = 0;
#else
		_integral_passed = 6;
		_floating_point_passed = 8;
#endif
	}
	virtual void pop_all() override
	{
		static_passer::pop_all();
	}
	template<typename _Ty>
	void pass_varg(_Ty _value)
	{
		pass(_value);
	}
	template<typename _First, typename _Second, typename _Third, typename _Fourth>
	void pass_all(_First _first, _Second _second, _Third _third, _Fourth _fourth)
	{
		static_assert(!(std::is_floating_point<_First>::value || std::is_floating_point<_Second>::value || std::is_floating_point<_Third>::value || std::is_floating_point<_Fourth>::value), "All parameters must be of integral types.");

		_integral_passed = 0;

		static_passer::pass_all(_first, _second, _third, _fourth);

#if defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		// All floating point values are pushed onto the stack (mov al, 0)
		_passer._output.write_all(0xb0_8, 0x00_8);
#endif
	}
	pass_count_type compensatory_pushes()
	{
		return (align_stack(_passer._stack_offset * element_size) - _passer._stack_offset * element_size) / element_size;
	}
};

}
}
}