#pragma once

#include <cstddef>

namespace bia {
namespace stream {

class input_stream
{
public:
    typedef void* mark_type;

    virtual ~input_stream() = default;
    virtual void reset_to_mark(mark_type mark) = 0;
    virtual void drop_mark(mark_type mark) = 0;
    virtual mark_type mark() = 0;
    virtual std::size_t read(void* buffer, std::size_t size) = 0;
};

}
}