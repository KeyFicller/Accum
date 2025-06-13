#pragma once

#include "basic_macro.h"

#ifdef server_MODULE
#define SERVER_EXPORT _DLL_EXPORT
#define SERVER_C_EXPORT _DLL_C_EXPORT
#else
#define SERVER_EXPORT _DLL_IMPORT
#define SERVER_C_EXPORT _DLL_C_IMPORT
#endif