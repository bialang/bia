#pragma once

#include <string>

#include "allocator.hpp"
#include "string_stream.hpp"
#include "local_object.hpp"
#include "max.hpp"


namespace bia
{
namespace machine
{

class string_resource_base
{
public:
	virtual ~string_resource_base() = default;
	virtual stream::string_stream::length_t length() const noexcept = 0;
	virtual stream::string_stream::size_t size() const noexcept = 0;
	template<typename Char_type>
	const Char_type * string() const noexcept
	{
		return reinterpret_cast<const Char_type*>(buffer());
	}
protected:
	virtual const void * buffer() const noexcept = 0;
};

class dstring_resource : public string_resource_base
{
public:
	dstring_resource(memory::universal_allocation _string, memory::allocator * _allocator) noexcept : _string(_string)
	{
		this->_allocator = _allocator;
	}
	dstring_resource(const dstring_resource & _copy) = delete;
	dstring_resource(dstring_resource && _move) noexcept = default;
	~dstring_resource()
	{
		_allocator->deallocate(_string);
	}
	virtual stream::string_stream::length_t length() const noexcept override
	{
		return stream::string_stream::length(_string.first);
	}
	virtual stream::string_stream::size_t size() const noexcept override
	{
		return stream::string_stream::size(_string.first);
	}

protected:
	virtual const void * buffer() const noexcept override
	{
		return stream::string_stream::string<void>(_string.first);
	}

private:
	memory::universal_allocation _string;
	memory::allocator * _allocator;
};

class cstring_resource : public string_resource_base
{
public:
	template<typename Char_type>
	cstring_resource(const Char_type * _string) noexcept
	{
		this->_string = _string;
		_length = std::char_traits<Char_type>::length(_string);
		_size = _length * sizeof(Char_type);
	}
	virtual stream::string_stream::length_t length() const noexcept override
	{
		return _length;
	}
	virtual stream::string_stream::size_t size() const noexcept override
	{
		return _size;
	}

protected:
	const void * buffer() const noexcept override
	{
		return _string;
	}

private:
	const void * _string;
	stream::string_stream::length_t _length;
	stream::string_stream::size_t _size;
};

typedef utility::local_object<string_resource_base, utility::max_sizeof<dstring_resource, cstring_resource>(), utility::max_alignof<dstring_resource, cstring_resource>()> string_resource_t;

}
}