#pragma once

#include <simple_allocator.hpp>

using namespace bia::machine;

class test;


class test_allocator : public memory::simple_allocator
{
public:
	static memory::allocator * allocator()
	{
		return _test_allocator;
	}
	static memory::executable_allocator * executable_allocator()
	{
		return _test_allocator;
	}
	static memory::member_allocator * member_allocator()
	{
		return _test_allocator;
	}
	static memory::big_int_allocator * big_int_allocator()
	{
		return _test_allocator;
	}
	static std::shared_ptr<memory::allocator> shared_allocator()
	{
		return std::shared_ptr<memory::allocator>(allocator(), [](memory::allocator*) {});
	}
	static std::shared_ptr<memory::executable_allocator> shared_executable_allocator()
	{
		return std::shared_ptr<memory::executable_allocator>(executable_allocator(), [](memory::executable_allocator*) {});
	}
	static std::shared_ptr<memory::member_allocator> shared_member_allocator()
	{
		return std::shared_ptr<memory::member_allocator>(member_allocator(), [](memory::member_allocator*) {});
	}
	static std::shared_ptr<memory::big_int_allocator> shared_big_int_allocator()
	{
		return std::shared_ptr<memory::big_int_allocator>(big_int_allocator(), [](memory::big_int_allocator*) {});
	}

private:
	friend test;

	static test_allocator * _test_allocator;

	static void start_monitoring()
	{
		_test_allocator = new test_allocator();

		memory::big_int_allocator::initialize(shared_allocator());
	}
	static void end_monitoring()
	{

		delete _test_allocator;
		_test_allocator = nullptr;
	}
};