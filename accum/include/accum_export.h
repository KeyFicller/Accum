#include "basic_macro.h"

#ifdef accum_MODULE
#define ACCUM_EXPORT _DLL_EXPORT
#define ACCUM_C_EXPORT _DLL_C_EXPORT
#else
#define ACCUM_EXPORT _DLL_IMPORT
#define ACCUM_C_EXPORT _DLL_C_IMPORT
#endif