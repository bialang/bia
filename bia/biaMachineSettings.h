#pragma once

#include "biaGlobal.h"
#include "biaParameter.h"


namespace bia
{
namespace machine
{

struct BiaMachineSettings
{
	unsigned int unStackSize = sizeof(bia::api::BiaParameter) * 50;
	unsigned int unMaxElementsPerCell = 64;
};

}
}