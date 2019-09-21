#pragma once

#include <cstdint>
#include <gc/memory_allocator.hpp>
#include <gc/std_memory_allocator.hpp>
#include <map>
#include <ostream>
#include <utility>

namespace bia {
namespace bvm {

class code
{
public:
	code(const code& copy) = delete;
	/*
	 Serializes this code object to the given output stream.

	 @param[out] output is the output; this stream should not further format the given data
	*/
	void serialize(std::ostream& output) const;
	/*
	 Tests whether this code object contains JIT optimizations.

	 @returns whether this code contains optimizations
	*/
	bool has_jit_code() const;
	/*
	 Deserializes a code object from an input stream.

	 @param[in] input is the input; the stream will not be reset to its original position
	 @returns the deserialized code
	*/
	static code deserialize(std::istream& input);
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

private:
	friend class bvm;

	/* the memory allocator used to allocate the space for the byte code */
	gc::memory_allocator* allocator;
	/* the byte code that can be executed by the bvm */
	std::pair<int8_t*, std::size_t> byte_code;
};

} // namespace bvm
} // namespace bia