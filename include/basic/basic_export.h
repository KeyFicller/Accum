#pragma once

#include "basic_macro.h"

#ifdef basic_MODULE
#define BASIC_EXPORT _DLL_EXPORT
#define BASIC_C_EXPORT _DLL_C_EXPORT
#else
#define BASIC_EXPORT _DLL_IMPORT
#define BASIC_C_EXPORT _DLL_C_IMPORT
#endif