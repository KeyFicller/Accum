#pragma once

#include "math_static_vector.h"

namespace PRJ_NAME {
template<typename t, unsigned n>
struct mat_impl_t
{
    using vec = vec_impl_t<t, n>;

    vec data[n];

    mat_impl_t() { memset(data, 0, sizeof(mat_impl_t)); }

    mat_impl_t(const std::initializer_list<vec>& _elements)
      : mat_impl_t()
    {
        ASSERT(_elements.size() <= n);
        int i = 0;
        for (const auto& element : _elements)
            data[i++] = element;
    }

#ifdef COMPILE_CLANG
    template<unsigned m = n, typename = std::enable_if_t<m == 2>>
#else
    template<typename = std::enable_if_t<n == 2>>
#endif
    mat_impl_t(const vec& _col1, const vec& _col2)
      : mat_impl_t({ _col1, _col2 })
    {
    }

#ifdef COMPILE_CLANG
    template<unsigned m = n, typename = std::enable_if_t<m == 3>>
#else
    template<typename = std::enable_if_t<n == 3>>
#endif
    mat_impl_t(const vec& _col1, const vec& _col2, const vec& _col3)
      : mat_impl_t({ _col1, _col2, _col3 })
    {
    }

#ifdef COMPILE_CLANG
    template<unsigned m = n, typename = std::enable_if_t<m == 4>>
#else
    template<typename = std::enable_if_t<n == 4>>
#endif
    mat_impl_t(const vec& _col1, const vec& _col2, const vec& _col3, const vec& _col4)
      : mat_impl_t({ _col1, _col2, _col3, _col4 })
    {
    }

    vec& operator[](unsigned _index)
    {
        ASSERT(_index < n);
        return data[_index];
    }

    const vec& operator[](unsigned _index) const
    {
        ASSERT(_index < n);
        return data[_index];
    }

    static const mat_impl_t& identity()
    {
        static mat_impl_t result;
        static bool init = false;
        if (!init) {
            for (int i = 0; i < n; i++)
                result[i][i] = static_cast<t>(1);
        }
        return result;
    }

    mat_impl_t transposed() const
    {
        mat_impl_t result;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                result[i][j] = data[j][i];
        }
        return result;
    }

    mat_impl_t& transpose()
    {
        *this = transposed();
        return *this;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "{";
        for (unsigned i = 0; i < n; i++) {
            ss << data[i].to_string();
            if (i != n - 1)
                ss << ", ";
        }
        ss << "}";
        return ss.str();
    }
};

template<typename t, unsigned n>
bool
operator==(const mat_impl_t<t, n>& _lhs, const mat_impl_t<t, n>& _rhs)
{
    for (int i = 0; i < n; i++) {
        if (_lhs[i] != _rhs[i])
            return false;
    }
    return true;
}

template<typename t>
using mat2_t = mat_impl_t<t, 2>;

template<typename t>
using mat3_t = mat_impl_t<t, 3>;

template<typename t>
using mat4_t = mat_impl_t<t, 4>;

using mat2_f = mat2_t<float>;
using mat3_f = mat3_t<float>;
using mat4_f = mat4_t<float>;
}