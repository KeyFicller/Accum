#pragma once

#include "basic_macro.h"
#include "basic_alias.h"

namespace PRJ_NAME
{
    class prefab_base
    {
    public:
        virtual ~prefab_base() = default;

    protected:
        prefab_base() = default;
    };

    template <typename t>
    class prefab : public prefab_base
    {
        MEMBER_DECLARE(prefab, shared<t>, self);

    public:
        ~prefab() override = default;

    public:
        prefab() : m_self(nullptr)
        {
        }

    public:
        template <typename... args>
        static prefab create(args &&..._args)
        {
            prefab result;
            result.set_self(make_shared<t>(std::forward<args &&>(_args)...));
            return result;
        }

    public:
        prefab(const prefab &_other)
        {
            self() = _other.self();
        }
        prefab &operator=(const prefab &_other)
        {
            self() = _other.self();
            return *this;
        }

        shared<t> operator->() const
        {
            return self();
        }
    };
}