#pragma once

#include <type_traits>
#include <utility>

#include "biaParameter.h"
#include "biaException.h"
#include "biaMemberCreator.h"



namespace bia
{
namespace force
{

template<typename _CLASS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	p_pFunction(p_pInstance);

	return 0;
}

template<typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_CLASS*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _CLASS * p_pInstance)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(p_pInstance, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)())
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	p_pFunction();

	return 0;
}

template<typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0))
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	p_pFunction(std::forward<_0>(*p0));

	return 0;
}

template<typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1))
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2))
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3))
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4))
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5))
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6))
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7))
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8))
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9))
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10))
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11))
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12))
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13))
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14))
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16))
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17))
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18))
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, void(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19))
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)())
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction());

	return 1;
}

template<typename _RETURN, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0))
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1))
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2))
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3))
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4))
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5))
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6))
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7))
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8))
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9))
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10))
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11))
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12))
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13))
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14))
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16))
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17))
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18))
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const void*, _RETURN(*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19))
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat);

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat);

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat);

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS, typename _THAT>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _THAT, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_THAT*, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, _THAT * p_pThat)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(p_pThat, std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)() const)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)();

	return 0;
}

template<typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0) const)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1) const)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2) const)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3) const)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4) const)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5) const)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6) const)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7) const)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)() const)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0) const)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1) const)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2) const)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3) const)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4) const)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5) const)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6) const)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7) const)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, const _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)())
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)();

	return 0;
}

template<typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0))
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1))
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2))
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3))
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4))
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5))
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6))
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7))
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8))
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9))
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10))
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11))
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12))
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13))
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14))
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16))
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17))
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18))
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19))
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)())
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0))
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1))
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2))
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3))
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4))
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5))
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6))
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7))
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8))
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9))
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10))
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11))
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12))
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13))
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14))
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16))
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17))
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18))
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19))
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)() const)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	(p_pInstance->*p_pFunction)();

	return 0;
}

template<typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0) const)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0));

	return 0;
}

template<typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1) const)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2) const)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3) const)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4) const)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5) const)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6) const)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7) const)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));

	return 0;
}

template<typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void*, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, void(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	(p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));

	return 0;
}

template<typename _RETURN, typename _CLASS>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)() const)
{
	if (p_pEnd - p_pBegin != 0)
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0) const)
{
	if (p_pEnd - p_pBegin != 1)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1) const)
{
	if (p_pEnd - p_pBegin != 2)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2) const)
{
	if (p_pEnd - p_pBegin != 3)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3) const)
{
	if (p_pEnd - p_pBegin != 4)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4) const)
{
	if (p_pEnd - p_pBegin != 5)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5) const)
{
	if (p_pEnd - p_pBegin != 6)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6) const)
{
	if (p_pEnd - p_pBegin != 7)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7) const)
{
	if (p_pEnd - p_pBegin != 8)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const)
{
	if (p_pEnd - p_pBegin != 9)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const)
{
	if (p_pEnd - p_pBegin != 10)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const)
{
	if (p_pEnd - p_pBegin != 11)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const)
{
	if (p_pEnd - p_pBegin != 12)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const)
{
	if (p_pEnd - p_pBegin != 13)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const)
{
	if (p_pEnd - p_pBegin != 14)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const)
{
	if (p_pEnd - p_pBegin != 15)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const)
{
	if (p_pEnd - p_pBegin != 16)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const)
{
	if (p_pEnd - p_pBegin != 17)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const)
{
	if (p_pEnd - p_pBegin != 18)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const)
{
	if (p_pEnd - p_pBegin != 19)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18)));

	return 1;
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline int ExecuteDisguisedBia(void * p_pDestination, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, _CLASS * p_pInstance, _RETURN(_CLASS::*p_pFunction)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const)
{
	if (p_pEnd - p_pBegin != 20)
		return -1;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return -1;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return -1;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return -1;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return -1;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return -1;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return -1;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return -1;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return -1;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return -1;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return -1;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return -1;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return -1;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return -1;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return -1;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return -1;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return -1;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return -1;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return -1;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return -1;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return -1;

	api::framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19)));

	return 1;
}

template<typename _CLASS, typename _RETURN, typename... _ARGS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter*, const api::BiaParameter*, const _CLASS*, _RETURN(_CLASS::*)(_ARGS...))
{
	throw exception::AccessViolationException("A const class cannot call non-const members.");
}

template<typename _CLASS, typename _RETURN, typename... _ARGS>
inline int ExecuteDisguisedBia(void*, api::BiaParameter*, const api::BiaParameter*, const _CLASS*, _RETURN(_CLASS::*)(_ARGS...), const void*)
{
	throw exception::AccessViolationException("A const class cannot call non-const members.");
}

template<typename T>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 0)
		return nullptr;

	return new T();
}

template<typename T, typename _0>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 1)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	return new T(std::forward<_0>(*p0));
}

template<typename T, typename _0, typename _1>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 2)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1));
}

template<typename T, typename _0, typename _1, typename _2>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 3)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2));
}

template<typename T, typename _0, typename _1, typename _2, typename _3>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 4)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 5)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 6)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 7)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 8)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 9)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 10)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 11)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 12)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 13)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 14)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 15)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 16)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 17)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return nullptr;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 18)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return nullptr;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return nullptr;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 19)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return nullptr;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return nullptr;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return nullptr;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18));
}

template<typename T, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline T * InitializeDisguisedBia(api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd)
{
	if (p_pEnd - p_pBegin != 20)
		return nullptr;

	std::remove_reference<_0>::type * p0;

	if (!p_pBegin[0].GetMember()->Cast<std::remove_reference<_0>::type>(p0))
		return nullptr;

	std::remove_reference<_1>::type * p1;

	if (!p_pBegin[1].GetMember()->Cast<std::remove_reference<_1>::type>(p1))
		return nullptr;

	std::remove_reference<_2>::type * p2;

	if (!p_pBegin[2].GetMember()->Cast<std::remove_reference<_2>::type>(p2))
		return nullptr;

	std::remove_reference<_3>::type * p3;

	if (!p_pBegin[3].GetMember()->Cast<std::remove_reference<_3>::type>(p3))
		return nullptr;

	std::remove_reference<_4>::type * p4;

	if (!p_pBegin[4].GetMember()->Cast<std::remove_reference<_4>::type>(p4))
		return nullptr;

	std::remove_reference<_5>::type * p5;

	if (!p_pBegin[5].GetMember()->Cast<std::remove_reference<_5>::type>(p5))
		return nullptr;

	std::remove_reference<_6>::type * p6;

	if (!p_pBegin[6].GetMember()->Cast<std::remove_reference<_6>::type>(p6))
		return nullptr;

	std::remove_reference<_7>::type * p7;

	if (!p_pBegin[7].GetMember()->Cast<std::remove_reference<_7>::type>(p7))
		return nullptr;

	std::remove_reference<_8>::type * p8;

	if (!p_pBegin[8].GetMember()->Cast<std::remove_reference<_8>::type>(p8))
		return nullptr;

	std::remove_reference<_9>::type * p9;

	if (!p_pBegin[9].GetMember()->Cast<std::remove_reference<_9>::type>(p9))
		return nullptr;

	std::remove_reference<_10>::type * p10;

	if (!p_pBegin[10].GetMember()->Cast<std::remove_reference<_10>::type>(p10))
		return nullptr;

	std::remove_reference<_11>::type * p11;

	if (!p_pBegin[11].GetMember()->Cast<std::remove_reference<_11>::type>(p11))
		return nullptr;

	std::remove_reference<_12>::type * p12;

	if (!p_pBegin[12].GetMember()->Cast<std::remove_reference<_12>::type>(p12))
		return nullptr;

	std::remove_reference<_13>::type * p13;

	if (!p_pBegin[13].GetMember()->Cast<std::remove_reference<_13>::type>(p13))
		return nullptr;

	std::remove_reference<_14>::type * p14;

	if (!p_pBegin[14].GetMember()->Cast<std::remove_reference<_14>::type>(p14))
		return nullptr;

	std::remove_reference<_15>::type * p15;

	if (!p_pBegin[15].GetMember()->Cast<std::remove_reference<_15>::type>(p15))
		return nullptr;

	std::remove_reference<_16>::type * p16;

	if (!p_pBegin[16].GetMember()->Cast<std::remove_reference<_16>::type>(p16))
		return nullptr;

	std::remove_reference<_17>::type * p17;

	if (!p_pBegin[17].GetMember()->Cast<std::remove_reference<_17>::type>(p17))
		return nullptr;

	std::remove_reference<_18>::type * p18;

	if (!p_pBegin[18].GetMember()->Cast<std::remove_reference<_18>::type>(p18))
		return nullptr;

	std::remove_reference<_19>::type * p19;

	if (!p_pBegin[19].GetMember()->Cast<std::remove_reference<_19>::type>(p19))
		return nullptr;

	return new T(std::forward<_0>(*p0), std::forward<_1>(*p1), std::forward<_2>(*p2), std::forward<_3>(*p3), std::forward<_4>(*p4), std::forward<_5>(*p5), std::forward<_6>(*p6), std::forward<_7>(*p7), std::forward<_8>(*p8), std::forward<_9>(*p9), std::forward<_10>(*p10), std::forward<_11>(*p11), std::forward<_12>(*p12), std::forward<_13>(*p13), std::forward<_14>(*p14), std::forward<_15>(*p15), std::forward<_16>(*p16), std::forward<_17>(*p17), std::forward<_18>(*p18), std::forward<_19>(*p19));
}

}
}