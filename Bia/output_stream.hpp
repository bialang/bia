#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>


namespace bia
{
namespace stream
{

class BiaOutputStreamBuffer;

class output_stream
{
public:
	typedef long long cursor_type;

	virtual ~output_stream() = default;
	/**
	 * Writes all the passed arguments to the stream.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	p_args	Defines the parameters.
	*/
	template<typename... _Args>
	void write_all(_Args&&... args)
	{
		//Prepare underlying implementation
		reserve(size<_Args...>());

		write(std::forward<_Args>(args)...);
	}
	virtual void write_stream(const stream::BiaOutputStreamBuffer & p_stream) = 0;
	/**
	 * Sets the position of the cursor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	_position	Defines the new aboslute position.
	 *
	 * @throws	std::domain_error	Thrown when the position is out of the domain.
	 * @throws	
	 *
	 * @see	output_stream::get_cursor_domain().
	*/
	virtual void set_position(cursor_type _position) = 0;
	/**
	 * Moves the source to the destination cursor.
	 *
	 * @param	p_llDestination	Defines the destination cursor.
	 * @param	p_llSource	Defines the source cursor.
	 * @param	p_llSize	Defines the size of the source cursor.
	*/
	virtual void Move(long long p_llDestination, long long p_llSource, long long p_llSize) = 0;
	/**
	 * Returns the position of the cursor.
	 *
	 * @return	The position of the cursor.
	*/
	virtual cursor_type get_position() const = 0;
	/**
	 * Returns a memory buffer with its size.
	 * 
	 * @remarks	This buffer is only valid until the destruction of this object.
	 * 
	 * @return	The buffer.
	 */
	virtual std::pair<const uint8_t*, size_t> GetBuffer() const = 0;
	virtual std::pair<cursor_type, cursor_type> get_cursor_domain() const noexcept = 0;

protected:
	virtual void reserve(size_t size) = 0;
	virtual void write(uint32_t value) = 0;
	virtual void write(uint64_t value) = 0;
	virtual void write(uint16_t value) = 0;
	virtual void write(uint8_t value) = 0;

private:
	template<typename _Ty, typename... _Args>
	void write(_Ty&& value, _Args&&... args)
	{
		write(std::forward<_Ty>(value));

		write(std::forward<_Args>(args)...);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @return	The total size in bytes.
	*/
	template<typename _Ty>
	constexpr static size_t size() noexcept
	{
		return sizeof(_Ty);
	}
	/**
	 * Returns the size of the arguments at compile time.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @return	The total size in bytes.
	*/
	template<typename _Ty, typename... _Args>
	constexpr static size_t size() noexcept
	{
		return sizeof(_Ty) + size<_Args...>();
	}
};

}
}