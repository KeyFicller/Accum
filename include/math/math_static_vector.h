#pragma once

#include "basic_assert.h"

#include <initializer_list>
#include <sstream>
#include <type_traits>

namespace PRJ_NAME
{
    template <typename t, unsigned n>
    struct vec_impl_t
    {
        t data[n];

        vec_impl_t()
        {
            memset(data, 0, sizeof(vec_impl_t));
        }

        vec_impl_t(const std::initializer_list<t> &_elements)
            : vec_impl_t()
        {
            ASSERT(_elements.size() <= n);
            int i = 0;
            for (const auto &elemnt : _elements)
                data[i++] = elemnt;
        }
#ifdef COMPILE_CLANG
        template <unsigned m = n, typename = std::enable_if_t<m == 2>>
#else
        template <typename = std::enable_if_t<n == 2>>
#endif
        vec_impl_t(const t &_x, const t &_y)
            : vec_impl_t({_x, _y})
        {
        }

#ifdef COMPILE_CLANG
        template <unsigned m = n, typename = std::enable_if_t<m == 3>>
#else
        template <typename = std::enable_if_t<n == 3>>
#endif
        vec_impl_t(const t &_x, const t &_y, const t &_z)
            : vec_impl_t({_x, _y, _z})
        {
        }

#ifdef COMPILE_CLANG
        template <unsigned m = n, typename = std::enable_if_t<m == 4>>
#else
        template <typename = std::enable_if_t<n == 4>>
#endif
        vec_impl_t(const t &_x, const t &_y, const t &_z, const t &_w)
            : vec_impl_t({_x, _y, _z, _w})
        {
        }

        t &operator[](unsigned _index)
        {
            ASSERT(_index < n);
            return data[_index];
        }

        t operator[](unsigned _index) const
        {
            ASSERT(_index < n);
            return data[_index];
        }

#ifdef COMPILE_CLANG
#define _VECTOR_COMPONENT_SHORT_CUT(_SHORT_CUT, _INDEX)                 \
    template <unsigned m = n, typename = std::enable_if_t<m >= _INDEX>> \
    t &_SHORT_CUT()                                                     \
    {                                                                   \
        return data[_INDEX - 1];                                        \
    }                                                                   \
    template <unsigned m = n, typename = std::enable_if_t<m >= _INDEX>> \
    const t &_SHORT_CUT() const                                         \
    {                                                                   \
        return data[_INDEX - 1];                                        \
    }
#else

#define _VECTOR_COMPONENT_SHORT_CUT(_SHORT_CUT, _INDEX) \
    template <typename = std::enable_if_t<n >= _INDEX>> \
    t &_SHORT_CUT()                                     \
    {                                                   \
        return data[_INDEX - 1];                        \
    }                                                   \
    template <typename = std::enable_if_t<n >= _INDEX>> \
    const t &_SHORT_CUT() const                         \
    {                                                   \
        return data[_INDEX - 1];                        \
    }
#endif

        _VECTOR_COMPONENT_SHORT_CUT(x, 1);
        _VECTOR_COMPONENT_SHORT_CUT(y, 2);
        _VECTOR_COMPONENT_SHORT_CUT(z, 3);
        _VECTOR_COMPONENT_SHORT_CUT(w, 4);
        _VECTOR_COMPONENT_SHORT_CUT(r, 1);
        _VECTOR_COMPONENT_SHORT_CUT(g, 2);
        _VECTOR_COMPONENT_SHORT_CUT(b, 3);
        _VECTOR_COMPONENT_SHORT_CUT(a, 4);

#undef _VECTOR_COMPONENT_SHORT_CUT

        explicit vec_impl_t(const vec_impl_t<t, n - 1> &_origin, const t &_appended = {})
        {
            memcpy(data, _origin.data, sizeof(vec_impl_t<t, n - 1>));
            data[n - 1] = _appended;
        }

#ifdef COMPILE_CLANG
        template <unsigned m = n, typename = std::enable_if_t<m == 3 || m == 4>>
#else
        template <typename = std::enable_if_t<n == 3 || n == 4>>
#endif
        vec_impl_t<t, 2> xy() const
        {
            return vec_impl_t<t, 2>(data[0], data[1]);
        }

#ifdef COMPILE_CLANG
        template <unsigned m = n, typename = std::enable_if_t<m == 4>>
#else
        template <typename = std::enable_if_t<n == 4>>
#endif
        vec_impl_t<t, 3> xyz() const
        {
            return vec_impl_t<t, 3>(data[0], data[1], data[2]);
        }
        std::string to_string() const
        {
            std::stringstream ss;
            ss << "{";
            for (unsigned i = 0; i < n; i++)
            {
                ss << data[i];
                if (i != n - 1)
                    ss << ", ";
            }
            ss << "}";
            return ss.str();
        }
    };

    template <typename t, unsigned n>
    bool operator==(const vec_impl_t<t, n> &_lhs, const vec_impl_t<t, n> &_rhs)
    {
        return !memcmp(_lhs.data, _rhs.data, sizeof(vec_impl_t<t, n>));
    }

    template <typename t>
    using vec2_t = vec_impl_t<t, 2>;

    template <typename t>
    using vec3_t = vec_impl_t<t, 3>;

    template <typename t>
    using vec4_t = vec_impl_t<t, 4>;

#define _VECTOR_TYPE_SHORT_CUT(_SHORTCUT, _T) \
    using vec2_##_SHORTCUT = vec2_t<_T>;      \
    using vec3_##_SHORTCUT = vec3_t<_T>;      \
    using vec4_##_SHORTCUT = vec4_t<_T>

    _VECTOR_TYPE_SHORT_CUT(i, int);
    _VECTOR_TYPE_SHORT_CUT(ui, unsigned int);
    _VECTOR_TYPE_SHORT_CUT(f, float);
    _VECTOR_TYPE_SHORT_CUT(d, double);

#undef _VECTOR_TYPE_SHORT_CUT
}
