#pragma once

#include <big_int_allocator.hpp>
#include <member_allocator.hpp>
#include <executable_allocator.hpp>

using namespace bia::machine;

class test;

class test_allocator
{ 
public:
	static memory::allocator * allocator()
	{
		return nullptr;
	}
	static memory::executable_allocator * executable_allocator()
	{
		return nullptr;
	}
	static memory::member_allocator * member_allocator()
	{
		return nullptr;
	}
	static memory::big_int_allocator * big_int_allocator()
	{
		return nullptr;
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

	static void init()
	{
		memory::big_int_allocator::initialize(shared_big_int_allocator());
	}
	static void deinit()
	{
	}
	static void start_monitoring()
	{
	}
	static void end_monitoring()
	{

	}
};