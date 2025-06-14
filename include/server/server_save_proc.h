#pragma once

#include "server_save_load.h"

#include <type_traits>
#include <set>
#include <map>

namespace PRJ_NAME
{
    class save_proc_impl;

    enum class save_proc_flow
    {
        k_begin_map,
        k_end_map,
        k_begin_seq,
        k_begin_seq_flow,
        k_end_seq,
        k_in_key,
        k_in_value
    };

    class SERVER_EXPORT save_proc : public save_load_proc
    {
        IMPL_DERIVED(save_proc);

    public:
        save_proc(const std::string &_file);
        ~save_proc() override = default;

    public:
        bool begin() override;
        bool end() override;

        void begin_map();
        void end_map();
        void begin_sequence(bool _flow = false);
        void end_sequence();
        void in_key();
        void in_value();
        void in(const std::string &_value);
        void in(int _value);
        void in(float _value);
        void in(bool _value);
    };

    template <typename t>
    inline save_proc &operator<<(save_proc &_proc, const t &_value)
    {
        _proc.in(_value);
        return _proc;
    }

    template <unsigned n>
    inline save_proc &operator<<(save_proc &_proc, const char (&_value)[n])
    {
        _proc.in(std::string(_value));
        return _proc;
    }

    template <typename t>
    inline save_proc &operator<<(save_proc &_proc, const std::vector<t> &_value)
    {
        _proc << save_proc_flow::k_begin_seq;
        for (auto &elem : _value)
            _proc << elem;
        _proc << save_proc_flow::k_end_seq;
        return _proc;
    }

    template <typename t>
    inline save_proc &operator<<(save_proc &_proc, const std::set<t> &_value)
    {
        _proc << save_proc_flow::k_begin_seq;
        for (auto &elem : _value)
            _proc << elem;
        _proc << save_proc_flow::k_end_seq;
        return _proc;
    }

    template <typename t1, typename t2>
    inline save_proc &operator<<(save_proc &_proc, const std::map<t1, t2> &_value)
    {
        _proc << save_proc_flow::k_begin_seq;
        for (const auto &pair : _value)
        {
            _proc << save_proc_flow::k_begin_map << save_proc_flow::k_in_key << _SAVE_LOAD_PROC_INTERNAL_1
                  << save_proc_flow::k_in_value << pair.first << save_proc_flow::k_in_key << _SAVE_LOAD_PROC_INTERNAL_2
                  << save_proc_flow::k_in_value << pair.second << save_proc_flow::k_end_map;
        }

        _proc << save_proc_flow::k_end_seq;
        return _proc;
    }

    template <>
    inline save_proc &operator<<(save_proc &_proc, const save_proc_flow &_value)
    {
        switch (_value)
        {
        case save_proc_flow::k_begin_map:
            _proc.begin_map();
            break;
        case save_proc_flow::k_end_map:
            _proc.end_map();
            break;
        case save_proc_flow::k_begin_seq:
            _proc.begin_sequence(false);
            break;
        case save_proc_flow::k_begin_seq_flow:
            _proc.begin_sequence(true);
            break;
        case save_proc_flow::k_end_seq:
            _proc.end_sequence();
            break;
        case save_proc_flow::k_in_key:
            _proc.in_key();
            break;
        case save_proc_flow::k_in_value:
            _proc.in_value();
            break;
        }
        return _proc;
    }
}