#pragma once

#include "basic_log.h"

#include <string>
#include <filesystem>

#define _BREAK_IN_ASSERT 1

#if _BREAK_IN_ASSERT
#define _ASSERT_BREAK __builtin_trap()
#else
#define _ASSERT_BREAK
#endif

#define _ASSERT_INTERNAL(_CONDITION, ...) \
    do                                    \
    {                                     \
        if (!(_CONDITION))                \
        {                                 \
            ERROR(__VA_ARGS__);           \
            _ASSERT_BREAK;                \
        }                                 \
    } while (0)

#define _ASSERT_WITH_MESSAGE(_CONDITION, _FORMAT, ...) _ASSERT_INTERNAL(_CONDITION, std::string("Assertion failed: ") + std::string(_FORMAT), __VA_ARGS__)
#define _ASSERT_WITHOUT_MESSAGE(_CONDITION) _ASSERT_INTERNAL(_CONDITION, "Assertion failed: '%s' at file(%s): line(%d).", #_CONDITION, std::filesystem::path(__FILE__).filename().string().c_str(), __LINE__)

#define _ASSERT_GET_MACRO_NAME(_ARG1, _ARG2, _ARG3, _ARG4, _ARG5, _ARG6, _ARG7, _ARG8, _ARG9, _ARG10, _MACRO, ...) _MACRO
#define _ASSERT_GET_MACRO(...) EXPAND(_ASSERT_GET_MACRO_NAME(__VA_ARGS__,          \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITH_MESSAGE, \
                                                             _ASSERT_WITHOUT_MESSAGE,                                          \))
#define ASSERT(...) EXPAND(_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))