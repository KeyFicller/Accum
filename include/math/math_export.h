#pragma once

#include "basic_macro.h"

#ifdef math_MODULE
#define MATH_EXPORT _DLL_EXPORT
#define MATH_C_EXPORT _DLL_C_EXPORT
#else
#define MATH_EXPORT _DLL_IMPORT
#define MATH_C_EXPORT _DLL_C_IMPORT
#endif