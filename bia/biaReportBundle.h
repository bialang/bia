#pragma once

#include <vector>
#include <stdint.h>


namespace bia
{
namespace api
{
namespace grammar
{

struct Report;

typedef struct
{
	const Report * pBegin;
	const Report * pEnd;
} report_range;

struct Report
{
	enum TYPE : uint8_t
	{
		T_TOKEN,
		T_BEGIN,
		T_END,
		T_EMPTY_CHILD
	};

	TYPE type;
	union
	{
		struct
		{
			const char * pcString;
			size_t iSize;
		} token;
		report_range children;
	} content;
	uint32_t unRuleId;
	uint32_t unTokenId;
	uint64_t ullCustomParameter;
};

class BiaReportBundle
{
public:
	/**
	 * Constructor.
	*/
	inline BiaReportBundle()
	{
		m_unSize = 0;
	}
	/**
	 * Adds a report to the bundle.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_report	Defines the report.
	*/
	inline void AddReport(Report p_report)
	{
		switch (p_report.type)
		{
		case Report::T_TOKEN:
			fwrite(p_report.content.token.pcString, 1, p_report.content.token.iSize, stdout);
			puts("");
		}

		if (m_unSize < SIZE)
		{
			m_aReports[m_unSize++] = std::move(p_report);

			return;
		}
		else if (m_unSize == SIZE)
			m_vReports.assign(m_aReports, m_aReports + m_unSize++);

		m_vReports.push_back(std::move(p_report));
	}
	/**
	 * Clears the bundle completly.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	*/
	inline void Clear()
	{
		m_unSize = 0;
		m_vReports.clear();
	}
	/**
	 * Resets the bundle to a previous state.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_unOldState	Defines the previous state.
	*/
	inline void Reset(uint32_t p_unOldState)
	{
		if (m_unSize > SIZE)
			m_vReports.erase(m_vReports.begin() + p_unOldState, m_vReports.end());
		else
			m_unSize = p_unOldState;
	}
	/**
	 * Returns the current size of the bundle.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	The current size.
	*/
	inline uint32_t Size() const
	{
		return m_unSize > SIZE ? m_vReports.size() : m_unSize;
	}
	/**
	 * Returns a pointer to the beginning.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	A pointer to the beginning.
	*/
	inline Report * Begin()
	{
		return m_unSize > SIZE ? m_vReports.begin()._Ptr : m_aReports;
	}
	/**
	 * Returns a pointer to the end.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	A pointer to the end.
	*/
	inline Report * End()
	{
		return m_unSize > SIZE ? m_vReports.end()._Ptr : m_aReports + m_unSize;
	}

private:
	constexpr static uint32_t SIZE = 64;
	uint32_t m_unSize;

	Report m_aReports[SIZE];

	std::vector<Report> m_vReports;	/**	Stores the report when the array is full.	*/
};

class BiaReportReceiver
{
public:
	virtual ~BiaReportReceiver() = default;
	virtual void Report(const Report * p_pBegin, const Report * p_pEnd) = 0;
};

}
}
}