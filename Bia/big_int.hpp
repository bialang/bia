#pragma once

#include <mpir/mpir.h>
#include <type_traits>
#include <cstdint>
#include <memory>

#include "config.hpp"
#include "allocator.hpp"


namespace bia
{
namespace dependency
{

class big_int
{
public:
	typedef typename std::remove_extent<mpz_t>::type type;

	BIA_EXPORT static void intialize(const std::shared_ptr<machine::memory::allocator> & _allocator);
	BIA_EXPORT static void add(type * _result, type * _left, type * _right);
	BIA_EXPORT static void add(type * _result, type * _left, int64_t _right);
	BIA_EXPORT static void sub(type * _result, type * _left, type * _right);
	BIA_EXPORT static void sub(type * _result, type * _left, int64_t _right);
	BIA_EXPORT static void sub(type * _result, int64_t * _left, type * _right);
	BIA_EXPORT static void mul(type * _result, type * _left, type * _right);
	BIA_EXPORT static void mul(type * _result, type * _left, int64_t _right);
	BIA_EXPORT static void div(type * _result, type * _left, type * _right);
	BIA_EXPORT static void div(type * _result, type * _left, int64_t _right);
	BIA_EXPORT static void div(type * _result, int64_t _left, type * _right);
	BIA_EXPORT static void free_int(type * _int);
	BIA_EXPORT static type * new_int();

private:
	static std::shared_ptr<machine::memory::allocator> _allocator;
};

}
}