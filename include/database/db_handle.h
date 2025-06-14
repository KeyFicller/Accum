#pragma once

#include "db_export.h"

#include "basic_include.h"

#include <concepts>
#include <set>
#include <type_traits>

namespace PRJ_NAME {
template<typename t>
struct handle_deduction
{};

template<typename t>
concept next_deduction = requires(const t& _handle) { handle_deduction<t>::next(_handle); };

template<typename t>
concept overall_deduction = requires(const std::set<t>& _handles) { handle_deduction<t>::next(_handles); };

template<typename t>
class handle_allocator
{
    MEMBER_DECLARE(handle_allocator, std::set<t>, used_handles);

  public:
    bool is_valid_handle(const t& _handle) const { return !m_used_handles.count(_handle); }

    void insert_handle(const t& _handle)
    {
        if (is_valid_handle(_handle))
            m_used_handles.insert(_handle);
    }

    void erase_handle(const t& _handle)
    {
        if (!is_valid_handle(_handle))
            m_used_handles.erase(_handle);
    }

    [[nodiscard]] t next_handle(const t& _handle) const
        requires next_deduction<t>
    {
        return handle_deduction<t>::next(_handle);
    }

    [[nodiscard]] t next_handle() const
        requires overall_deduction<t>
    {
        return handle_deduction<t>::next(used_handles());
    }
};

using db_handle = int;

template<>
struct handle_deduction<int>
{
    static int next(int _handle) { return _handle + 1; }

    static int next(const std::set<int>& _handles)
    {
        if (_handles.empty())
            return 1;

        return (*std::max_element(_handles.begin(), _handles.end()) + 1);
    }
};
}