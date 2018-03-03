#pragma once


#include "biaMember.hpp"
#include "biaMemberHolder.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

class BiaModuleHandler
{
public:
	BiaModuleHandler();

	bool ImportModule(framework::BiaMember * p_pDestination);

private:
	framework::BiaMemberHolder m_scripts;
};

}
}
}