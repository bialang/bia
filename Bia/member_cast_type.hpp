#pragma once

#include <type_traits>

#include "type_traits.hpp"


namespace bia
{
namespace framework
{

template<typename Type, typename Ptr_type>
inline typename std::enable_if<utility::pointer_rank<Type>::odd, Type>::type selected_convert(Ptr_type _ptr)
{
	return reinterpret_cast<Type>(_ptr);
}
template<typename Type, typename Ptr_type>
inline typename std::enable_if<!utility::pointer_rank<Type>::odd, Type>::type selected_convert(Ptr_type _ptr)
{
	return *reinterpret_cast<Type*>(_ptr);
}


template<typename Type>
struct base_convert
{
	constexpr static bool is_const = std::is_const<Type>::value;

	typedef Type request_type;
	typedef request_type* data_type;
	typedef typename std::conditional<is_const, const void*, void*>::type abstract_data_type;

	static const std::type_info & info()
	{
		return typeid(request_type);
	}
};

template<typename Type>
struct converter : base_convert<Type>
{
	using base = base_convert<Type>;
	typedef typename std::conditional<std::is_arithmetic<Type>::value, Type, Type&>::type type;

	static type convert(typename base::abstract_data_type _ptr)
	{
		return *selected_convert<typename base::data_type>(_ptr);
	}
};

template<typename Type>
struct converter<Type*> : base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>
{
	using base = base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>;
	typedef Type* type;

	static type convert(typename base::abstract_data_type _ptr)
	{
		return selected_convert<typename base::data_type>(_ptr);
	}
};

template<typename Type>
struct converter<Type&> : base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>
{
	using base = base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>;
	typedef Type& type;

	static type convert(typename base::abstract_data_type _ptr)
	{
		return *selected_convert<typename base::data_type>(_ptr);
	}
};

template<typename Type>
struct converter<Type&&> : base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>
{
	using base = base_convert<typename std::conditional<utility::pointer_rank<Type*>::odd, Type, Type*>::type>;
	typedef Type&& type;

	static type convert(typename base::abstract_data_type _ptr)
	{
		return std::move(*selected_convert<typename base::data_type>(_ptr));
	}
};

}
}