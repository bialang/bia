#pragma once

#include <cstddef>
#include <cstdint>

namespace bia {
namespace string {

namespace encoding {

class encoder;

}

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
    /*
     Returns the pointer allocated by the garbage collector. If this string was created from from_static_buffer(), the return value is invalid.

     @return the gc collectable pointer
    */
    const void* get_gc_pointer() const noexcept
    {
        return data;
    }
    /*
     The length of the string. This method returns the amount of code units and code points.

     @return the length without the trailing zero character
    */
    std::size_t length() const noexcept
    {
        return len;
    }

private:
    friend class encoding::encoder;

    /* the count of code units */
    std::size_t len;
    /* the zero terminated, unmodifiable and UTF-16 encoded string */
    const char_type* data;

    string(const char_type* data, std::size_t len) noexcept : data(data), len(len)
    {}
};

}
}