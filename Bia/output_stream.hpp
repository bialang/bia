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
	 * Writes all the passed arguments to the stream.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _args Defines the parameters.
	*/
	template<typename... _Args>
	void write_all(_Args &&... _args)
	{
		// Prepare underlying implementation
		prepare(size<_Args...>());

		write_forward(std::forward<_Args>(_args)...);
	}
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
	 * Returns the position of the cursor.
	 *
	 * @since 3.64.127.716
	 * @date 7-May-18
	 *
	 * @throws
	 *
	 * @return The cursor position.
	*/
	virtual cursor_type get_position() const = 0;

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
	virtual void write(int8_t _value) = 0;
	virtual void write(int16_t _value) = 0;
	virtual void write(int32_t _value) = 0;
	virtual void write(int64_t _value) = 0;

private:
	void write_forward() noexcept
	{
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<sizeof(_Ty) == 1>::type write_forward(_Ty && _value, _Args &&... _args)
	{
		write(*reinterpret_cast<const int8_t*>(&_value));

		write_forward(std::forward<_Args>(_args)...);
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<sizeof(_Ty) == 2>::type write_forward(_Ty && _value, _Args &&... _args)
	{
		write(*reinterpret_cast<const int16_t*>(&_value));

		write_forward(std::forward<_Args>(_args)...);
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<sizeof(_Ty) == 4>::type write_forward(_Ty && _value, _Args &&... _args)
	{
		write(*reinterpret_cast<const int32_t*>(&_value));

		write_forward(std::forward<_Args>(_args)...);
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<sizeof(_Ty) == 8>::type write_forward(_Ty && _value, _Args &&... _args)
	{
		write(*reinterpret_cast<const int64_t*>(&_value));

		write_forward(std::forward<_Args>(_args)...);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The total size in bytes.
	*/
	template<typename _Ty>
	constexpr static size_t size() noexcept
	{
		return sizeof(_Ty);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The total size in bytes.
	*/
	template<typename _Ty, typename... _Args>
	constexpr static typename std::enable_if<(sizeof...(_Args) > 0), size_t>::type size() noexcept
	{
		return sizeof(_Ty) + size<_Args...>();
	}
};

}
}