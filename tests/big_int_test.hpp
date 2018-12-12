#pragma once

#include <big_int.hpp>

#include "test.hpp"

using namespace bia::dependency;


class big_int_test
{
public:
  static void arithmetic_test();

  void test_add();
  void test_sub();

private:
  big_int _int;
};
