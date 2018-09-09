#pragma once

#include "static_passer.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

class member_passer : public static_passer
{
public:
	member_passer(passer & _passer) noexcept : static_passer(_passer)
	{
	}
};

}
}
}