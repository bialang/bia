#pragma once

#include <big_int.hpp>
#include <buffer_builder.hpp>
#include <simple_allocator.hpp>

#include "test.hpp"

using namespace bia::dependency;
using namespace bia::machine::memory;


class big_int_test
{
public:
  big_int_test();
  void test_set_get();
  void test_add();
  void test_sub();
  void test_mul();
  void test_div();
  void test_mod();
  void test_power();

private:
  simple_allocator _allocator;
  bia::utility::buffer_builder _builder;
  big_int _int;
};
