#pragma once

#include "basic_alias.h"
#include "basic_macro.h"

namespace PRJ_NAME {
/// @brief This class defines common base for all prefabs.
class prefab_base
{
  public:
    /// @brief Destructor.
    virtual ~prefab_base() = default;

  protected:
    /// @brief Constructor.
    prefab_base() = default;
};

/// @brief This class provides the ability to make some prefabs.
/// @tparam t Type of prefab to make.
template<typename t>
class prefab : public prefab_base
{
    MEMBER_DECLARE(prefab, shared<t>, self);

  public:
    /// @brief Destructor.
    ~prefab() override = default;

  public:
    /// @brief Constructor.
    prefab()
      : m_self(nullptr)
    {
    }

  public:
    /// @brief Create a prefab of given type and arguments.
    /// @tparam ...args Type of arguments.
    /// @param ..._args Arguments.
    /// @return The created prefab.
    template<typename... args>
    static prefab create(args&&... _args)
    {
        prefab result;
        result.set_self(make_shared<t>(std::forward<args&&>(_args)...));
        return result;
    }

  public:
    /// @brief Copy constructor.
    /// @param _other Another prefab.
    prefab(const prefab& _other) { self() = _other.self(); }

    /// @brief Check if two prefab equals.
    /// @param _other Another prefab.
    /// @return True if equal, else false.
    prefab& operator=(const prefab& _other)
    {
        self() = _other.self();
        return *this;
    }

    /// @brief Get the pointer to the data been prefabed.
    /// @return The pointer.
    shared<t> operator->() const { return self(); }
};
}