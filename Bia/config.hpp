#pragma once

// Compiler macro
#if defined(_MSC_VER)
#define BIA_COMPILER_MSVC 1
#elif defined(__GNUC__) || defined(__GNUG__)
#define BIA_COMPILER_GNU 1
//#elif defined(__clang__)
//#elif defined(__ICC) || defined(__INTEL_COMPILER)
//#elif defined(__IBMC__) || defined(__IBMCPP__)
//#elif defined(__SUNPRO_C)  || defined(__SUNPRO_CC)
#else
#error "Unsupported compiler."
#endif

//Operating System
#if defined(_WIN32)
#define BIA_OS_WINDOWS 1
#elif defined(__linux__)
#define BIA_OS_LINUX 1
#else
#error "Unsupported operating system."
#endif

// Architecture
#if defined(__i386) || defined(_M_IX86)
#define BIA_ARCHITECTURE_X86
//#elif defined(__x86_64__) || defined(_M_X64)
//#define BIA_ARCHITECTURE_X86_64
#else
#error "Unsupported architecture."
#endif

// Microsoft
#if defined(BIA_COMPILER_MSVC)

// Calling conventions
#define BIA_STATIC_CALLING_CONVETION __fastcall

template<typename _Return, typename... _Args>
using static_function_signature = _Return(BIA_STATIC_CALLING_CONVETION *)(_Args...);

template<typename _Class, typename _Return, typename... _Args>
using member_function_signature = _Return(__thiscall _Class::*)(_Args...);

template<typename _Class, typename _Return, typename... _Args>
using const_member_function_signature = _Return(__thiscall _Class::*)(_Args...) const;

template<typename _Class, typename _Return, typename... _Args>
using varg_member_function_signature = _Return(__cdecl _Class::*)(_Args..., ...);

// Export
#if defined(BIA_IMPORT)
#define BIA_EXPORT __declspec(dllimport)
#elif defined(BIA_BUILD_SHARED)
#define BIA_EXPORT __declspec(dllexport)
#else
#define BIA_EXPORT
#endif

// GNU
#elif defined(BIA_COMPILER_GNU)

// Calling conventions
#define BIA_STATIC_CALLING_CONVETION(_return, _signature) __attribute__((cdecl)) _return _signature

template<typename _Return, typename... _Args>
using static_function_signature = __attribute__((cdecl)) _Return(*)(_Args...);

template<typename _Class, typename _Return, typename... _Args>
using member_function_signature = _Return(_Class::*)(_Args...);

template<typename _Class, typename _Return, typename... _Args>
using const_member_function_signature = _Return(_Class::*)(_Args...) const;

template<typename _Class, typename _Return, typename... _Args>
using varg_member_function_signature = __attribute__((cdecl)) _Return(_Class::*)(_Args..., ...);

// Export
#define BIA_EXPORT

#endif

// Universal macros
#define BIA_MAX_KEYWORD_LENGTH 16
#define BIA_MAX_OPERATOR_LENGTH 4
/** The minimum buffer size of stream::input_stream::get_buffer(). */
#define BIA_MIN_INPUT_BUFFER_SIZE 1024
/** The maximum identifier length. Can be at most as high as @ref BIA_MIN_INPUT_BUFFER / 4. */
#define BIA_MAX_IDENTIFIER_LENGTH (BIA_MIN_INPUT_BUFFER_SIZE / 4)
