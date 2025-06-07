#pragma once

#include "basic_macro.h"

namespace PRJ_NAME
{
    template <typename t = int>
    class bit_flags
    {
        MEMBER_DECLARE(bit_flags, t, bits);

    public:
        explicit bit_flags(const t &_bits) : m_bits(_bits) {}

    public:
        bool has_bit(const t &_bit) const
        {
            return m_bits & _bit;
        }

        bit_flags &set_bit(const t &_bit, int _on = true)
        {
            if (_on)
                bits() |= _bit;
            else
                bits() &= (~_bit);
            return *this;
        }

        bit_flags &clear()
        {
            bits() = 0;
            return *this;
        }

        operator t() const
        {
            return bits();
        }
    };

    template <typename t>
    bool operator==(const bit_flags<t> &_lhs, const bit_flags<t> &_rhs)
    {
        return _lhs.bits() == _rhs.bits();
    }
}