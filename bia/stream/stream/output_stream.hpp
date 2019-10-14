#pragma once

#include <cstddef>
#include <util/type_traits/size_of.hpp>
#include <utility>

namespace bia {
namespace stream {

class output_stream
{
public:
	virtual ~output_stream() = default;

	virtual void write(const void* buffer, std::size_t size) = 0;
	template<typename... T>
	typename std::enable_if<(sizeof...(T) > 0), std::size_t>::type write_all(T&&... args)
	{
		auto size = util::type_traits::size_of<T...>::value;

		// prepare stream
		reserve(size);

		// write all
		write_forward(std::forward<T>(args)...);

		return size;
	}
	virtual void reserve(std::size_t additional_size) = 0;

private:
	void write_forward()
	{}
	template<typename T, typename... Other>
	void write_forward(T&& value, Other&&... other)
	{
		write(&value, sizeof(T));
		write_forward(std::forward<Other>(other)...);
	}
};

} // namespace stream
} // namespace bia