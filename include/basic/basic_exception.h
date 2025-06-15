#pragma once

#include "basic_printer.h"

namespace PRJ_NAME {
enum exception_type : long long
{
    // categories
    k_unkown = 0
    //
};

/// @brief This class defines exceptions.
class BASIC_EXPORT exception : public std::exception
{
    MEMBER_DECLARE(exception, exception_type, type);

  public:
    /// @brief Constructor.
    /// @tparam ...args Type of arguments for constructing exception message.
    /// @param _type Type of exception.
    /// @param ..._args Arguments for constructing exception message.
    template<typename... args>
    exception(exception_type _type, args&&... _args)
      : m_type(_type)
      , std::exception(format_print(std::forward<args>(_args)...))
    {
    }

    /// @brief Destructor.
    ~exception() override = default;
};
}

#define THROW(_TYPE, ...) throw ::PRJ_NAME::exception(_TYPE, __VA_ARGS__)