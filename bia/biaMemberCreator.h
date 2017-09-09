#pragma once

#include <type_traits>
#include <utility>

#include "biaMemberHolder.h"
#include "biaClassRaw.h"
#include "biaDouble.h"
#include "biaDoubleRef.h"
#include "biaFloat.h"
#include "biaFloatRef.h"
#include "biaLong.h"
#include "biaLongRef.h"
#include "biaString.h"
#include "biaStringRef.h"
#include "biaConstChar.h"
#include "biaStaticFunction.h"
#include "biaType.h"


namespace bia
{
namespace api
{
namespace framework
{

template<typename T>
inline void MemberCreator(void * p_pDestination, T && p_value)
{
	using _TYPE = std::remove_reference<T>::type;

	//Const char
	if (std::is_same<T, const char*>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<const char*>>(std::forward<T>(p_value));
	//Double object
	else if (std::is_same<T, double>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<double>>(std::forward<T>(p_value));
	//Float object
	else if (std::is_same<T, float>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<float>>(std::forward<T>(p_value));
	//Integral object
	else if (std::is_integral<T>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<long long>>(std::forward<T>(p_value));
	//Create string object
	else if (std::is_same<std::remove_cv<T>::type, std::string>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<std::string>>(std::forward<T>(p_value));
	//Native reference
	else if (utility::BiaRefConverter<T>::CONVERTIBLE)
		(new(p_pDestination) BiaMemberHolder())->Initialize<native::BiaNativeVariable<utility::BiaRefConverter<T>::type>>(std::forward<T>(p_value));
	else if (utility::BiaFunctionTraits<T>::IS_FUNCTION && !utility::BiaFunctionTraits<T>::IS_MEMBER_FUNCTION)
		(new(p_pDestination) BiaMemberHolder())->Initialize<executable::BiaStaticFunction<T>>(std::forward<T>(p_value));
	else if (std::is_class<T>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<BiaClassRaw<_TYPE>>(new _TYPE(std::forward<T>(p_value)));
	else if (std::is_class<std::remove_pointer<_TYPE>::type>::value)
		(new(p_pDestination) BiaMemberHolder())->Initialize<BiaClassRawRef<std::remove_pointer<_TYPE>::type>>(std::forward<T>(p_value));
	else
		throw exception::UnknownException("Can't create member for specified type.");
}

}
}
}