#pragma once

#include <cstddef>

namespace bia {
namespace compiler {

class code
{
public:
	code(const code& copy) = delete;
	const void* begin() const noexcept;
	const void* end() const noexcept;
	/*
	 Returns the count of required local members.

	 @returns the count
	*/
	std::size_t local_member_count() const;
	/*
	 Returns the count of required temporary members.

	 @returns the count
	*/
	std::size_t temp_member_count() const;

};

} // namespace compiler
} // namespace bia