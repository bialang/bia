#pragma once

#ifdef _WIN32

#else
#define BIA_INSTRUCTION_CALLING_CONVETION __attribute__ ((cdecl))
#endif

#if defined(_MSC_VER)

#define BIA_INSTRUCTION_CALLING_CONVETION(x, y) x __cdecl y

#if defined(_M_IX86)
#define BIA_ARCHITECTURE_MG32 1
#elif defined(_M_X64)

#endif

#endif