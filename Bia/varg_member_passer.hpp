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
#elif defined(BIA_COMPILER_MSVC)
		_integral_passed = 4;
#else
		_integral_passed = 4;
		_floating_point_passed = 8;
#endif
	}
	virtual void pop_all() override
	{
		static_passer::pop_all();
	}
	template<typename Type>
	void pass_varg(Type _value)
	{
		pass(_value);
	}
	template<typename First, typename Second, typename Third, typename Fourth>
	void pass_all(First _first, Second _second, Third _third, Fourth _fourth)
	{
		static_assert(!(std::is_floating_point<First>::value || std::is_floating_point<Second>::value || std::is_floating_point<Third>::value || std::is_floating_point<Fourth>::value), "All parameters must be of integral types.");

#if defined(BIA_ARCHITECTURE_X86_32) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		// Move to ecx because of virtual member call
		register_pass<ecx>(_first);

		static_passer::pass_all(register_offset<ecx, void, false>(), _second, _third, _fourth);
#elif defined(BIA_ARCHITECTURE_X86_32) && defined(BIA_COMPILER_MSVC)
		static_passer::pass_all(_first, _second, _third, _fourth);
#elif defined(BIA_ARCHITECTURE_X86_64)
		_integral_passed = 0;

		static_passer::pass_all(_first, _second, _third, _fourth);

#if defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG)
		// All floating point values are pushed onto the stack (mov al, 0)
		_passer._output->write_all(0xb0_8, 0x00_8);
#endif
#endif
	}
	constexpr static pass_count_type varg_register_passes()
	{
#if defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		return 2;
#else
		return 0;
#endif
	}
	pass_count_type compensatory_pushes()
	{
		pass_count_type _count = (align_stack(_passer._stack_offset * element_size) - _passer._stack_offset * element_size) / element_size;

		for (pass_count_type i = 0; i < _count; ++i) {
			pass_varg(reserved_parameter());
		}

		return _count;
	}
};

}
}
}
