#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>


namespace bia
{
namespace stream
{

class BiaOutputStream
{
public:
	virtual ~BiaOutputStream() = default;

	template<typename... _ARGS>
	inline void WriteAll(_ARGS... p_args)
	{
		Prepare(Size(p_args...));

		Write(p_args...);
	}
	/**
	 * Sets the position of the cursor.
	 *
	 * @param	p_llPosition	Defines the new position of the cursor. Cannot move the cursor forward.
	*/
	virtual void SetPosition(long long p_llPosition) = 0;
	/**
	 * Returns the position of the cursor.
	 *
	 * @return	The position of the cursor.
	*/
	virtual long long GetPosition() const = 0;
	/**
	 * Returns a memory buffer with its size.
	 * 
	 * @remarks	This buffer is only valid until the destruction of this object.
	 * 
	 * @return	The buffer.
	 */
	virtual std::pair<const uint8_t*, size_t> GetBuffer() const = 0;

protected:
	virtual void Prepare(size_t p_iAdditonalSize) = 0;
	virtual void Write(uint64_t p_ullValue) = 0;
	virtual void Write(uint32_t p_unValue) = 0;
	virtual void Write(uint16_t p_usValue) = 0;
	virtual void Write(uint8_t p_ucValue) = 0;

private:
	template<typename T, typename... _ARGS>
	inline void Write(T p_value, _ARGS... p_args)
	{
		Write(p_value);

		Write(p_args...);
	}
	inline constexpr static size_t Size()
	{
		return 0;
	}
	template<typename T, typename... _ARGS>
	inline constexpr static size_t Size(T, _ARGS... p_args)
	{
		return sizeof(T) + Size(p_args...);
	}
};

}
}