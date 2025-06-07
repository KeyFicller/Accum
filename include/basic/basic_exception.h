#pragma once

#include "basic_log.h"

namespace PRJ_NAME
{
    enum exception_type : long long
    {
        // categories
        k_unkown = 0
        //
    };

    class exception : public std::exception
    {
        MEMBER_DECLARE(exception, exception_type, type);

    public:
        template <typename... args>
        exception(exception_type _type, args &&..._args)
            : m_type(_type), std::exception(cstyle_format_print(std::forward<args>(_args)...))
        {
        }
        ~exception() override = default;
    };
}

#define THROW(_TYPE, ...) throw ::PRJ_NAME::exception(_TYPE, __VA_ARGS__)