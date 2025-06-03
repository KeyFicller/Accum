#pragma once

#include "basic_macro.h"

#include <functional>

namespace PRJ_NAME
{
    template <typename ret, typename... args>
    using callback_t = std::function<ret(args...)>;
}