#pragma once

#include "basic_macro.h"

namespace PRJ_NAME {
/// @brief This class provides the ability to store boolean values with bit status.
/// @tparam t Type of the storage.
template<typename t = int>
class bit_flags
{
    MEMBER_DECLARE(bit_flags, t, bits);

  public:
    /// @brief Constructor.
    /// @param _bits Bits value.
    explicit bit_flags(const t& _bits)
      : m_bits(_bits)
    {
    }

  public:
    /// @brief Check whether bits value is on.
    /// @param _bit Bits value to be checked.
    /// @return True for on, else false.
    bool has_bit(const t& _bit) const { return m_bits & _bit; }

    /// @brief Set bits status.
    /// @param _bit Bits value.
    /// @param _on Whether to turn on those bits.
    /// @return Self reference.
    bit_flags& set_bit(const t& _bit, int _on = true)
    {
        if (_on)
            bits() |= _bit;
        else
            bits() &= (~_bit);
        return *this;
    }

    /// @brief Clear bits value.
    /// @return Self reference.
    bit_flags& clear()
    {
        bits() = 0;
        return *this;
    }

    /// @brief Implicit cast to storage value.
    operator t() const { return bits(); }
};

/// @brief Check whether two bitflags are equal.
/// @tparam t Type of the storage.
/// @param _lhs The first bitflags.
/// @param _rhs The second bitflags.
/// @return True if equal, else false.
template<typename t>
bool
operator==(const bit_flags<t>& _lhs, const bit_flags<t>& _rhs)
{
    return _lhs.bits() == _rhs.bits();
}
}