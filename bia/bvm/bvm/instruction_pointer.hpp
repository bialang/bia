#pragma once

#include <cstddef>
#include <bytecode/op_code.hpp>
#include <util/endian.hpp>

namespace bia {
namespace bvm {

class instruction_pointer
{
public:
    typedef const std::int8_t* buffer_type;

    instruction_pointer(const void* start, const void* end) noexcept
    {
        this->start = static_cast<buffer_type>(start);
        this->end = static_cast<buffer_type>(end);
        cursor = this->start;
    }
    /*
     Reads the given type from the current position. This method does not perform bounds checking.

     @return the value
    */
    template<typename T>
    T read() noexcept
    {
        auto tmp = util::from_little_endian<T>(cursor);

        cursor += sizeof(T);

        return tmp;
    }
    /*
     Reads the next op code. This method does not perform bounds checking.

     @return the op code
    */
    bytecode::op_code_type next_op_code() noexcept
    {
        auto op_code = util::from_little_endian<bytecode::op_code_type>(cursor);
        
        cursor += sizeof(bytecode::op_code_type);

        return op_code;
    }
    instruction_pointer& operator+=(std::size_t offset)
    {
        cursor += offset;

        // bounds checking
        if (cursor < start || cursor > end) {
            throw;
        }
    }
    operator bool() const noexcept
    {
        return cursor + bytecode::max_instruction_size < end;
    }

private:
    buffer_type start;
    buffer_type end;
    buffer_type cursor;
};

}
}