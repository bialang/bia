#pragma once

#include <cstddef>
#include <cstdint>
#include <gc/gc.hpp>

namespace bia {
namespace external {

typedef char16_t char_type;

class string final
{
public:
    /*
     Creates a new string object from a static UTF-16 encoded buffer. The buffer is not checked and not copied. Giving the result of get_gc_pointer() to the garbage collecter may end in undefined behavior.

     @param buffer the static zero-terminated string; must be valid during the lifetime of this object and its copies
     @param size the size of the string in code units
     @return the string object
    */
    static string from_static_buffer(const char_type* buffer, std::size_t size)
    {
        return string(buffer, size);
    }
    static string from_utf8(const char* buffer, std::size_t size)
    {

    }
    static string from_buffer(const std::int8_t* buffer, std::size_t size, string encoding)
    {
        auto data = static_cast<char_type*>(gc::gc::active_gc()->allocate(size * sizeof(char_type)));

        return string(nullptr, 0);
    }
    const void* get_gc_pointer() const noexcept
    {
        return data;
    }
    std::size_t length() const noexcept
    {
        return len;
    }

private:
    /* the count of code units */
    std::size_t len;
    /* the zero terminated, unmodifiable and UTF-16 encoded string */
    const char_type* data;

    string(const char_type* data, std::size_t len) noexcept : data(data), len(lenglenth)
    {}
};

}
}