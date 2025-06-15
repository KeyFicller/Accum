#pragma once

#include "basic_alias.h"
#include "basic_export.h"

namespace PRJ_NAME {
/// @brief This class provides the ability to do something when exiting current scope.
class guard
{
    MEMBER_DECLARE(guard, callback_t<void>, enter_func);
    MEMBER_DECLARE(guard, callback_t<void>, leave_func);

  public:
    /// @brief Construtor.
    /// @param _enter_fn Function been executed initializing the guard.
    /// @param _leave_fn Function been executed leaving current scope.
    explicit guard(const callback_t<void>& _enter_fn, const callback_t<void>& _leave_fn)
      : m_enter_func(_enter_fn)
      , m_leave_func(_leave_fn)
    {
        enter();
    }

    /// @brief Constructor.
    /// @param _leave_fn Function been executed leaving current scope.
    explicit guard(const callback_t<void>& _leave_fn)
      : guard(nullptr, _leave_fn)
    {
    }

    /// @brief Destructor.
    virtual ~guard() { leave(); }

  public:
    /// @brief Tell the guard not to execute leave function anymore.
    void dismiss() { set_leave_func(nullptr); }

  private:
    /// @brief Entering a scope.
    void enter()
    {
        if (enter_func())
            enter_func()();
    }

    /// @brief Leaving a scope.
    void leave()
    {
        if (leave_func())
            leave_func()();
    }
};

/// @brief This class provides the ability to restore some data when exiting current scope.
/// @tparam t Type of data.
template<typename t>
class value_reverter : public guard
{
    REFERENCE_MEMBER_DECLARE(value_reverter, t, value);
    MEMBER_DECLARE(value_reverter, t, record);

  public:
    /// @brief Constructor.
    /// @param _value Data to be restored.
    explicit value_reverter(t& _value)
      : guard(std::bind(&value_reverter::revert, this))
      , m_value(_value)
      , m_record(_value)
    {
    }

    /// @brief Constructor.
    /// @param _value Data to be restored.
    /// @param _init Data to be initialized at present.
    explicit value_reverter(t& _value, const t& _init)
      : guard(std::bind(&value_reverter::revert, this))
      , m_value(_value)
      , m_record(_value)
    {
        value() = _init;
    }

  private:
    /// @brief Revert data.
    void revert() { value() = record(); }
};
}

#define _GUARD_WITH_ENTER(_ENTER, _LEAVE) ::PRJ_NAME::guard AUTO_NAME(guard)(_ENTER, _LEAVE)
#define _GUARD_WITHOUT_ENTER(_LEAVE) ::PRJ_NAME::guard AUTO_NAME(guard)(_LEAVE)

#define _GUARD_GET_MACRO_NAME(_ARG1, _ARG2, _MACRO, ...) _MACRO
#define _GUARD_GET_MACRO(...) EXPAND(_GUARD_GET_MACRO_NAME(__VA_ARGS__, _GUARD_WITH_ENTER, _GUARD_WITHOUT_ENTER))
#define GUARD(...) EXPAND(_GUARD_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))

#define _VALUE_REVERTER_WITH_INIT(_VALUE, _INIT)                                                                       \
    ::PRJ_NAME::value_reverter<decltype(_VALUE)> AUTO_NAME(value_reverter)(_VALUE, _INIT)
#define _VALUE_REVERTER_WITHOUT_INIT(_VALUE)                                                                           \
    ::PRJ_NAME::value_reverter<decltype(_VALUE)> AUTO_NAME(value_reverter)(_VALUE)

#define _VALUE_REVERTER_GET_MACRO_NAME(_ARG1, _ARG2, _MACRO, ...) _MACRO
#define _VALUE_REVERTER_GET_MACRO(...)                                                                                 \
    EXPAND(_VALUE_REVERTER_GET_MACRO_NAME(__VA_ARGS__, _VALUE_REVERTER_WITH_INIT, _VALUE_REVERTER_WITHOUT_INIT))
#define VALUE_REVERTER(...) EXPAND(_VALUE_REVERTER_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))