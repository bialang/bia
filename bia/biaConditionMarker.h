#pragma once

#include <vector>

#include "biaStream.h"


namespace bia
{
namespace api
{
namespace compiler
{

//class BiaConditionMaker
//{
//public:
//	enum LOCATION
//	{
//		L_END,
//		L_BEGIN,
//		L_NEXT
//	};
//
//	/**
//	 * Constructor.
//	 *
//	 * @param	[in,out]	p_code	Defines the stream.
//	*/
//	inline BiaConditionMaker(stream::BiaStream & p_code) : m_code(p_code), m_allMarkLocation{}
//	{
//		m_llNextPlaceholder = 0;
//	}
//	inline ~BiaConditionMaker() = default;
//
//	/**
//	 * Replaces all placeholder positions with the destinations and clears the this object.
//	 *
//	 * @since	1.6.17.107
//	 * @date	20-Apr-17
//	*/
//	inline void ReplaceAll()
//	{
//		auto llStart = m_code.TellWrite();
//
//		for (auto i = 0; i < 2; ++i)
//		{
//			for (auto j = m_avllPlaceholder[i].begin()._Ptr, jcond = m_avllPlaceholder[i].end()._Ptr; j < jcond; ++j)
//			{
//				auto llOffset = m_allMarkLocation[i] - *j - 8;
//
//				m_code.SeekWrite(*j);
//				m_code.Write(&llOffset, sizeof(long long));
//			}
//		}
//
//		m_code.SeekWrite(llStart);
//
//		//Clear
//		m_allMarkLocation[0] = 0ll;
//		m_allMarkLocation[1] = 0ll;
//		m_llNextPlaceholder = 0;
//		m_avllPlaceholder[L_BEGIN].clear();
//		m_avllPlaceholder[L_END].clear();
//	}
//	/**
//	 * Marks the last 8 bytes as placeholder.
//	 *
//	 * @since	1.6.17.107
//	 * @date	20-Apr-17
//	 *
//	 * @param   p_group	Defines the group of the placeholder.
//	 * @param	p_nOffset	(Optional)	Defines an additional offset.
//	*/
//	inline void MarkPlaceholder(LOCATION p_group)
//	{
//		m_avllPlaceholder[p_group].push_back(m_code.TellWrite() - 8);
//	}
//	/**
//	 * Marks the location of a group.
//	 *
//	 * @since	1.6.17.107
//	 * @date	20-Apr-17
//	 *
//	 * @param   p_group	Defines the group.
//	*/
//	inline void MarkLocation(LOCATION p_group)
//	{
//		auto llMark = m_code.TellWrite();
//
//		if (p_group == L_NEXT)
//		{
//			auto llOffset = llMark - m_llNextPlaceholder - 8;
//
//			for (auto i = m_avllPlaceholder[L_NEXT].begin()._Ptr, cond = m_avllPlaceholder[L_NEXT].end()._Ptr; i < cond; ++i)
//			{
//				auto llOffset = llMark - *i - 8;
//
//				m_code.SeekWrite(*i);
//				m_code.Write(&llOffset, sizeof(long long));
//			}
//
//			m_code.SeekWrite(llMark);
//			m_avllPlaceholder[L_NEXT].clear();
//		}
//		else
//			m_allMarkLocation[p_group] = llMark;
//	}
//
//private:
//	stream::BiaStream & m_code;
//
//	std::vector<long long> m_avllPlaceholder[3];
//
//	long long m_llNextPlaceholder;
//	long long m_allMarkLocation[2];
//};

class BiaConditionMakerSimple
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in,out]	p_code	Defines the stream.
	*/
	inline BiaConditionMakerSimple(stream::BiaStream & p_code) : m_code(p_code)
	{
		m_llPlaceholder = 0;
	}
	inline ~BiaConditionMakerSimple() = default;
	/**
	 * Marks the last 8 bytes as placeholder.
	 *
	 * @since	2.41.93.550
	 * @date	08-Oct-17
	*/
	inline void MarkPlaceholder()
	{
		m_llPlaceholder = m_code.TellWrite() - 8;
	}
	/**
	 * Marks the location of a group.
	 *
	 * @since	2.41.93.550
	 * @date	08-Oct-17
	 *
	 * @param   p_group	Defines the group.
	*/
	inline void MarkLocation()
	{
		auto llMark = m_code.TellWrite();
		auto llOffset = llMark - m_llPlaceholder - 8;

		m_code.SeekWrite(m_llPlaceholder);
		m_code.Write(&llOffset, sizeof(long long));
		m_code.SeekWrite(llMark);
	}

private:
	stream::BiaStream & m_code;

	long long m_llPlaceholder;
};

class BiaConditionMakerDouble
{
public:
	enum LOCATION
	{
		L_NEXT_0,
		L_NEXT_1
	};

	/**
	 * Constructor.
	 *
	 * @param	[in,out]	p_code	Defines the stream.
	*/
	inline BiaConditionMakerDouble(stream::BiaStream & p_code) : m_code(p_code) {}
	inline ~BiaConditionMakerDouble() = default;
	/**
	 * Marks the last 8 bytes as placeholder.
	 *
	 * @since	2.41.93.550
	 * @date	08-Oct-17
	 *
	 * @param   p_group	Defines the group of the placeholder.
	 * @param	p_nOffset	(Optional)	Defines an additional offset.
	*/
	inline void MarkPlaceholder(LOCATION p_group)
	{
		m_avllPlaceholder[p_group].push_back(m_code.TellWrite() - 8);
	}
	/**
	 * Marks the location of a group.
	 *
	 * @since	2.41.93.550
	 * @date	08-Oct-17
	 *
	 * @param   p_group	Defines the group.
	*/
	inline void MarkLocation(LOCATION p_group)
	{
		auto llMark = m_code.TellWrite();

		for (auto i = m_avllPlaceholder[p_group].begin()._Ptr, cond = m_avllPlaceholder[p_group].end()._Ptr; i < cond; ++i)
		{
			auto llOffset = llMark - *i - 8;

			m_code.SeekWrite(*i);
			m_code.Write(&llOffset, sizeof(long long));
		}

		m_code.SeekWrite(llMark);
		m_avllPlaceholder[p_group].clear();
	}

private:
	stream::BiaStream & m_code;

	std::vector<long long> m_avllPlaceholder[2];
};



}
}
}