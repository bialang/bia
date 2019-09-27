#pragma once

#include "../encoder.hpp"

#include <exception/char_encoding_exception.hpp>

namespace bia {
namespace external {
namespace encoding {
namespace standard {

/*
 The standard encoder for ASCII without any state. This class is safe to use between threads.
*/
class ascii : public encoder
{


protected:
    virtual std::size_t min_size(std::size_t count) const noexcept override
    {
        return count;
    }
    virtual std::size_t max_size(std::size_t count) const noexcept override
    {
        return count;
    }
    virtual std::size_t min_code_points(std::size_t size) const noexcept override
    {
        return size;
    }
    virtual std::size_t max_code_points(std::size_t size) const noexcept override
    {
        return size;
    }
    virtual std::int8_t* encode(const code_point* input, std::size_t input_len, std::int8_t* output) override
    {
        const auto end = input + input_len;

        while (input < end) {
            // check character
            if (*input & ~0x7f) {
                throw exception::char_encoding_exception(u"invalid ascii character");
            }

            *output++ = static_cast<std::int8_t>(*input++);
        }

        return output;
    }
    virtual code_point* decode(const std::int8_t* input, std::size_t input_len, code_point* output) override
    {
        const auto end = input + input_len;

        while (input < end) {
            // check character
            if (*input & ~0x7f) {
                throw exception::char_encoding_exception(u"invalid ascii character");
            }

            *output++ = *input++;
        }

        return output;
    }
};

}
}
}
}