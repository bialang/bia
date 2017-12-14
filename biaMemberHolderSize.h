#pragma once

#include <algorithm>

#include "biaDouble.h"
#include "biaDoubleRef.h"
#include "biaFloat.h"
#include "biaFloatRef.h"
#include "biaLong.h"
#include "biaLongRef.h"
#include "biaString.h"
#include "biaConstChar.h"
#include "biaStringRef.h"
#include "biaClass.h"
#include "biaClassRef.h"
#include "biaMemberFunction.h"
#include "biaStaticFunction.h"
#include "biaLambdaFunction.h"
#include "biaNamespace.h"
#include "biaClassWrapperMember.h"


#define BIA_MEMBER_HOLDER_SIZE_MIN (std::max({ \
	sizeof(bia::api::framework::native::BiaNativeVariable<double>), \
	sizeof(bia::api::framework::native::BiaNativeVariable<float>), \
	sizeof(bia::api::framework::native::BiaNativeVariable<long long>), \
	sizeof(bia::api::framework::native::BiaNativeVariable<std::string>), \
	sizeof(bia::api::framework::executable::BiaStaticFunction<void(*)()>), \
	sizeof(bia::api::framework::executable::BiaMemberFunction<void>), \
	sizeof(bia::api::framework::object::BiaClassWrapperMember), \
	sizeof(bia::api::framework::BiaNamespace), \
}))