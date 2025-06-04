#pragma once

#include "basic_macro.h"

#include <type_traits>

namespace PRJ_NAME
{
    template <typename t_facade>
    class implement_t
    {
        MEMBER_DECLARE(implement_t, t_facade *, facade);

    public:
        implement_t(t_facade &_facade) : m_facade(&_facade) {}
        virtual ~implement_t() = default;

    public:
        template <typename t>
        const t *self_t() const
            requires std::is_base_of_v<implement_t, t>
        {
            return static_cast<const t *>(this);
        }

        template <typename t>
        t *self_t()
            requires std::is_base_of_v<implement_t, t>
        {
            return static_cast<t *>(this);
        }

        template <typename t>
        const t *facade_t() const
            requires std::is_base_of_v<t_facade, t>
        {
            return static_cast<const t *>(facade());
        }

        template <typename t>
        t *facade_t()
            requires std::is_base_of_v<t_facade, t>
        {
            return static_cast<t *>(facade());
        }
    };
}

#define IMPL_CLASS(_CLASS) _CLASS##_impl

#define IMPL_BASE(_CLASS)                                           \
    friend class IMPL_CLASS(_CLASS);                                \
                                                                    \
protected:                                                          \
    explicit _CLASS(IMPL_CLASS(_CLASS) & _impl) : m_impl(&_impl) {} \
    IMPL_CLASS(_CLASS) *m_impl = nullptr

#define IMPL_DERIVED(_CLASS)         \
    friend class IMPL_CLASS(_CLASS); \
                                     \
protected:                           \
    explicit _CLASS(IMPL_CLASS(_CLASS) & _impl)

#define IMPL_INITIALIZE(_CLASS, ...) m_impl = new IMPL_CLASS(_CLASS)(*this, ##__VA_ARGS__)
#define IMPL_TERMINATE() SAFE_DELETE(m_impl)

#define _IMPL_BASE() m_impl
#define _IMPL_DERIVED(_CLASS) m_impl->self_t<IMPL_CLASS(_CLASS)>()
#define _IMPL_GET_MACRO_NAME(_ARG1, _ARG2, _MACRO, ...) _MACRO
#define _IMPL_GET_MACRO(...) EXPAND(_IMPL_GET_MACRO_NAME(__VA_ARGS__, _IMPL_DERIVED, _IMPL_BASE))
#define IMPL(...) EXPAND(_IMPL_GET_MACRO(_ARGS_AUGUMENTOR(__VA_ARGS__))(__VA_ARGS__))

#define _FACADE_BASE() facade()
#define _FACADE_DERIVED(_CLASS) facade_t<_CLASS>()
#define _FACADE_GET_MACRO_NAME(_ARG1, _ARG2, _MACRO, ...) _MACRO
#define _FACADE_GET_MACRO(...) EXPAND(_FACADE_GET_MACRO_NAME(__VA_ARGS__, _FACADE_DERIVED, _FACADE_BASE))
#define FACADE(...) EXPAND(_FACADE_GET_MACRO(_ARGS_AUGUMENTOR(__VA_ARGS__))(__VA_ARGS__))

#define IMPL_EXPOSE(_CLASS)                                                           \
public:                                                                               \
    static IMPL_CLASS(_CLASS) * get_impl(_CLASS *_facade) { return _facade->m_impl; } \
    static const IMPL_CLASS(_CLASS) * get_impl(const _CLASS *_facade) { return _facade->m_impl; }

#define IMPL_GET(_CLASS, _FACADE) IMPL_CLASS(_CLASS)::get_impl(_FACADE)