#pragma once

#include <cstdint>
#include <iostream>

#include "config.hpp"
#include "allocator.hpp"
#include "operator.hpp"
#include "member.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_disassembler
{
public:
	BIA_EXPORT static void disassemble(memory::allocation<const uint8_t> _code);

private:
	template<typename... Args>
	static void print_all(Args... _args)
	{
		print(_args...);
	}
	static void print()
	{
		std::cout << '\n';
	}
	template<typename... Args>
	static void print(const char * _str, Args... _args)
	{
		std::cout << _str;

		print(_args...);
	}
	template<typename... Args>
	static void print(double _immediate, Args... _args)
	{
		std::cout << _immediate;

		print(_args...);
	}
	template<typename... Args>
	static void print(framework::operator_t _operator, Args... _args)
	{
		std::cout << "operator";

		print(_args...);
	}

	template<typename Type, typename... Args>
	static void print(Type _immediate, Args... _args)
	{
		std::cout << +_immediate;

		print(_args...);
	}
	template<typename Type>
	static Type read(const uint8_t *& _cursor)
	{
		auto _tmp = *reinterpret_cast<const Type*>(_cursor);

		_cursor += sizeof(Type);

		return _tmp;
	}
};

}
}
}