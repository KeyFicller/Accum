#include "basic_macro.h"


#ifdef database_MODULE
#define DB_EXPORT _DLL_EXPORT
#define DB_C_EXPORT _DLL_C_EXPORT
#else
#define DB_EXPORT _DLL_IMPORT
#define DB_C_EXPORT _DLL_C_IMPORT
#endif