#pragma once

#include <stdio.h>
#include <memory>
#include <unordered_map>

#ifdef BIA_BUILD_API
#define BIA_API __declspec(dllexport)
#elif BIA_DEVELOPER_MODE
#define BIA_API
#else
#define BIA_API __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib, "bia_debug.lib")
#else
#pragma comment(lib, "bia.lib")
#endif
#endif

#define BIA_MAX_IDENTIFIER_LENGTH 0xff


namespace bia
{

namespace machine
{

namespace scope
{

class BiaScopeElement;
class BiaScopeReference;

}

class BiaMachineHelper;
class BiaMachineContext;
class BiaKey;

}

namespace api
{

class BiaParameter;

namespace framework
{

namespace object
{

class BiaClassOperatorBase;

}

namespace executable
{

class BiaBiaFunction;

}

class BiaTemplateTable;
class BiaMember;

}

}

}