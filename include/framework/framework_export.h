#include "basic_macro.h"

#ifdef framework_MODULE
#define FMW_EXPORT _DLL_EXPORT
#define FMW_C_EXPORT _DLL_C_EXPORT
#else
#define FMW_EXPORT _DLL_IMPORT
#define FMW_C_EXPORT _DLL_C_IMPORT
#endif