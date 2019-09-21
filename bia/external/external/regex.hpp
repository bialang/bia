#pragma once

#include <cstddef>

namespace bia {
namespace external {

class regex
{
public:
	/*
	 Creates a regex from the given pattern.

	 @param pattern is the UTF-16 encoded pattern
	 @param size is the amount of code units of the pattern
	*/
	regex(const char16_t* pattern, std::size_t size);
	~regex();

	/*
	 Matches this pattern against a string.

	 @param string is the UTF-16 encoded string
	 @param size is the length of the string
	 @returns `true` if the string matches the pattern, otherwise `false`
	*/
	bool matches(const char16_t* string, std::size_t size);
	/*
	 Searches the string for this pattern.

	 @param string is the UTF-16 encoded string
	 @param size is the length of the string
	 @returns `true` if this pattern was found in the string, otherwise `false`
	*/
	bool search(const char16_t* string, std::size_t size);

private:
};

} // namespace external
} // namespace bia