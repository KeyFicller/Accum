#pragma once

#include "basic_macro.h"

#include <functional>

namespace PRJ_NAME {
/// @brief Template declaration for callback function.
/// @tparam ret Type of return value.
/// @tparam ...args Types of arguments.
template<typename ret, typename... args>
using callback_t = std::function<ret(args...)>;

/// @brief Template declaration for scoped pointer.
/// @tparam t Type of pointer.
template<typename t>
using scoped = std::unique_ptr<t>;

/// @brief Template declaration for shared pointer.
/// @tparam t Type of pointer.
template<typename t>
using shared = std::shared_ptr<t>;

/// @brief Template declaration for creating a scoped pointer.
/// @tparam t Type of pointer
/// @tparam ...args Type of arguments.
/// @param ..._args Arguments.
/// @return
template<typename t, typename... args>
scoped<t>
make_scoped(args&&... _args)
{
    return std::make_unique<t>(std::forward<args&&>(_args)...);
}

/// @brief Template declaration for creating a shared pointer.
/// @tparam t Type of pointer.
/// @tparam ...args Type of arguments.
/// @param ..._args Arguments.
/// @return
template<typename t, typename... args>
shared<t>
make_shared(args&&... _args)
{
    return std::make_shared<t>(std::forward<args&&>(_args)...);
}
}