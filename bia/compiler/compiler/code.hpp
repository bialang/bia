#pragma once

#include <cstddef>

namespace bia {
namespace compiler {

class code
{
public:
	code(const void* b, const void* e) : b(b), e(e)
	{}
	code(const code& copy) = delete;
	const void* begin() const noexcept
	{
		return b;
	}
	const void* end() const noexcept
	{
		return e;
	}
	/*
	 Returns the count of required local members.

	 @returns the count
	*/
	std::size_t local_member_count() const
	{
		return 0;
	}
	/*
	 Returns the count of required temporary members.

	 @returns the count
	*/
	std::size_t temp_member_count() const
	{
		return 0;
	}

private:
	const void* b;
	const void* e;
};

} // namespace compiler
} // namespace bia