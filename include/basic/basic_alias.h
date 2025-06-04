#pragma once

#include "basic_macro.h"

#include <functional>

namespace PRJ_NAME
{
    template <typename ret, typename... args>
    using callback_t = std::function<ret(args...)>;

    template <typename t>
    using scoped = std::unique_ptr<t>;

    template <typename t>
    using shared = std::shared_ptr<t>;
}