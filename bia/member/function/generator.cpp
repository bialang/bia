#include "generator.hpp"

#include "../native/integer.hpp"

bia::member::member* bia::member::function::stop_iteration = new bia::member::native::integer<int>{ 0 };
