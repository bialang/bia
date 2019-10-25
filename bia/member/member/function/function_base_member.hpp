#pragma once

#include <member/member.hpp>

namespace bia {
namespace member {
namespace function {

class function_base_member : public member
{
public:
protected:
	virtual bool int64_data(std::int64_t& data) const override
	{
		return false;
	}
	virtual bool double_data(double& data) const override
	{
		return false;
	}
};

} // namespace function
} // namespace member
} // namespace bia