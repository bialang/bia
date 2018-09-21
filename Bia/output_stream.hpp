#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>


namespace bia
{
namespace stream
{

class output_stream
{
public:
	typedef long long cursor_type;

	virtual ~output_stream() noexcept = default;
	/**
	 * Sets the position of the cursor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _position Defines the new aboslute position.
	 *
	 * @throws
	 *
	 * @see output_stream::get_cursor_domain()
	*/
	virtual void set_position(cursor_type _position) = 0;
	/**
	 * Sets the beginning of the stream.
	 *
	 * @since 3.65.132.736
	 * @date 30-Jul-18
	 *
	 * @param _position The new beginning.
	 *
	 * @throws
	*/
	virtual void set_beginning(cursor_type _position) = 0;
	/**
	 * Appends the streams to this one.
	 *
	 * @remarks This function is only required to work with @ref buffer_output_stream.
	 *
	 * @since 3.64.132.731
	 * @date 28-Jun-18
	 *
	 * @param [in] _stream The stream. This stream may be in an unspecified state after completion.
	 *
	 * @throws exception::argument_error If the stream type is not supported.
	*/
	virtual void append_stream(output_stream & _stream) = 0;
	/**
	 * Writes the buffer to the stream.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _buffer The buffer.
	 * @param _size The size of the buffer.
	 *
	 * @throws
	*/
	virtual void write(const void * _buffer, size_t _size) = 0;
	/**
	 * Writes all the passed arguments to the stream.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @tparam Arguments The types of the values.
	 *
	 * @param _arguments Defines the parameters.
	 *
	 * @return The amount of bytes written.
	*/
	template<typename... Arguments>
	size_t write_all(Arguments &&... _arguments)
	{
		// Prepare underlying implementation
		auto _size = size<Arguments...>();

		prepare(_size);

		write_forward(std::forward<Arguments>(_arguments)...);

		return _size;
	}
	/**
	 * Returns the position of the cursor.
	 *
	 * @since 3.64.127.716
	 * @date 7-May-18
	 *
	 * @throws
	 *
	 * @return The cursor position.
	*/
	virtual cursor_type position() const = 0;

protected:
	/**
	 * Prepares the output to write @a _size bytes.
	 *
	 * @since 3.64.127.716
	 * @date 7-May-18
	 *
	 * @param _size The amount of bytes that are about to be written.
	 *
	 * @throws
	*/
	virtual void prepare(size_t _size) = 0;

private:
	void write_forward() noexcept
	{
	}
	template<typename Type, typename... Arguments>
	void write_forward(Type && _value, Arguments &&... _arguments)
	{
		write(&_value, sizeof(Type));

		write_forward(std::forward<Arguments>(_arguments)...);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @tparam Type The type.
	 *
	 * @return The total size in bytes.
	*/
	template<typename Type>
	constexpr static size_t size() noexcept
	{
		return sizeof(Type);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @tparam Type The type.
	 * @tparam Arguments The types of the values.
	 *
	 * @return The total size in bytes.
	*/
	template<typename Type, typename... Arguments>
	constexpr static typename std::enable_if<(sizeof...(Arguments) > 0), size_t>::type size() noexcept
	{
		return sizeof(Type) + size<Arguments...>();
	}
};

}
}
