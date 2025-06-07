#pragma once


#ifdef _MSC_VER
#pragma message("Compiling with MSVC")
#define COMILER_STRING "MSVC"
#define COMPILE_MSCV
#elif defined(__GUNC__)
#pragma message("Compiling with GCC")
#define COMPILE_STRING “GCC”
#define COMPILE_GCC
#elif defined(__clang__)
#pragma message("Compiling with clange")
#define COMPILE_STRING "clange"
#define COMPILE_CLANG
#else
#pragma message("Unknown compiler")
#define COMPILE_STRING "Unknown"
#endif
