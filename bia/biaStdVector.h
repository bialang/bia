#pragma once

#include <memory>
#include <vector>

#include "biaClassWrapper.h"


namespace bia
{
namespace standard
{

template<typename T>
inline std::shared_ptr<api::framework::object::BiaClassWrapper<std::vector<T>>> CreateStandardVector()
{
	using V = std::vector<T>;

	return std::shared_ptr<api::framework::object::BiaClassWrapper<V>>((new api::framework::object::BiaClassWrapper<V>())
		->AddConstructor()
		->SetFunction<void, const T&>("push_back", &V::push_back)
		->SetFunction("pop_back", &V::pop_back)
		->SetFunction<T&, size_t>("at", &V::at)
		->SetFunction<T&, size_t>("[]", &V::operator[])
		->SetFunction("size", &V::size)
		->SetFunction<void, size_t>("resize", &V::resize)
		->SetFunction("reserve", &V::reserve)
		->SetFunction("empty", &V::empty));
}

}
}