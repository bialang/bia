#pragma once

#include <utility>


namespace bia
{
namespace stream
{

class input_stream
{
public:
	typedef long long cursor_type;

	virtual ~input_stream() = default;
	virtual void reset(cursor_type _mark) = 0;
	virtual void skip(cursor_type _length) = 0;
	virtual cursor_type mark() = 0;
	virtual cursor_type size() = 0;
	virtual std::pair<const void*, cursor_type> get_buffer() = 0;
};

}
}