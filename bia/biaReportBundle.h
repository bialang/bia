#pragma once

#include <vector>


namespace bia
{
namespace api
{
namespace grammar
{

struct Report
{
	const char * pcString;
	size_t iSize;
	size_t iRuleId;
	size_t iTokenId;
	uint64_t ullCustomParameter;
	std::pair<const Report*, const Report*> children;
};

class BiaReportBundle
{
public:
	/**
	 * Constructor.
	*/
	inline BiaReportBundle()
	{
		m_iSize = 0;
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
		if (m_iSize < SIZE)
		{
			m_aReports[m_iSize++] = std::move(p_report);

			return;
		}
		else if (m_iSize == SIZE)
			m_vReports.assign(m_aReports, m_aReports + m_iSize++);

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
		m_iSize = 0;
		m_vReports.clear();
	}
	/**
	 * Resets the bundle to a previous state.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_iOldState	Defines the previous state.
	*/
	inline void Reset(size_t p_iOldState)
	{
		if (m_iSize > SIZE)
			m_vReports.erase(m_vReports.begin() + p_iOldState, m_vReports.end());
		else
			m_iSize = p_iOldState;
	}
	/**
	 * Returns the current size of the bundle.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	The current size.
	*/
	inline size_t Size() const
	{
		return m_iSize > SIZE ? m_vReports.size() : m_iSize;
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
		return m_iSize > SIZE ? m_vReports.begin()._Ptr : m_aReports;
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
		return m_iSize > SIZE ? m_vReports.end()._Ptr : m_aReports + m_iSize;
	}

private:
	constexpr static size_t SIZE = 64;
	size_t m_iSize;

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