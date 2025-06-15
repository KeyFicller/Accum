#pragma once

#include "basic_macro.h"

#include <functional>

namespace PRJ_NAME {
template<typename ret, typename... args>
using callback_t = std::function<ret(args...)>;

template<typename t>
using scoped = std::unique_ptr<t>;

template<typename t>
using shared = std::shared_ptr<t>;

template<typename t, typename... args>
scoped<t>
make_scoped(args&&... _args)
{
    return std::make_unique<t>(std::forward<args&&>(_args)...);
}

template<typename t, typename... args>
shared<t>
make_shared(args&&... _args)
{
    return std::make_shared<t>(std::forward<args&&>(_args)...);
}
}