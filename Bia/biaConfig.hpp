#pragma once

#ifdef _WIN32
#define BIA_INSTRUCTION_CALLING_CONVETION __cdecl
#else
#define BIA_INSTRUCTION_CALLING_CONVETION __attribute__ ((cdecl))
#endif