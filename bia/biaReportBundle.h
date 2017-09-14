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
	size_t iDepth;
	uint64_t ullCustomParameter;
};

class BiaReportBundle
{
public:
	inline void AddReport(Report p_report)
	{
		m_vReports.push_back(std::move(p_report));
	}
	inline void Clear()
	{
		m_vReports.clear();
	}
	inline const Report * Begin() const
	{
		return m_vReports.begin()._Ptr;
	}
	inline const Report * End() const
	{
		return m_vReports.end()._Ptr;
	}
private:
	std::vector<Report> m_vReports;
};

class BiaReportReceiver
{
public:
	virtual ~BiaReportReceiver() = default;
	virtual void Report(const BiaReportBundle & p_bundle) = 0;
};

}
}
}