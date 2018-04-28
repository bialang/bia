#pragma once

#include "config.hpp"


// Microsoft Compiler
#if defined(BIA_COMPILER_MSVC)
// 32 bit
#if defined(BIA_ARCHITECTURE_X86)
// Level 0
#define BIA_PO_0_1_1(a) a
#define BIA_PO_0_1_2(a, b) a, b
#define BIA_PO_0_1_3(a, b, c) a, b, c
#define BIA_PO_0_2_2(a, b) a, b
#define BIA_PO_0_2_3(a, b, c) a, b, c

// Level 1
#define BIA_PO_1_1_2(a, b) b, a
#endif

#endif