#pragma once

#ifdef _MSC_VER
#pragma message("Compiling with MSVC")
#define COMILER_STRING "msvc"
#define COMPILE_MSCV
#elif defined(__GUNC__)
#pragma message("Compiling with GCC")
#define COMPILE_STRING "gcc"
#define COMPILE_GCC
#elif defined(__clang__)
#pragma message("Compiling with clang")
#define COMPILE_STRING "clang"
#define COMPILE_CLANG
#else
#pragma message("Unknown compiler")
#define COMPILE_STRING "unknown"
#endif
