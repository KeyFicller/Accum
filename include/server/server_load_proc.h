#pragma once

#include "server_save_load.h"

#include <set>
#include <map>

namespace PRJ_NAME
{
    class load_proc_impl;

    enum class load_proc_flow
    {
        k_begin_seq,
        k_end_seq,
        k_out_key,
        k_out_value
    };

    // TODO: @zhangyuhui Review this solution.
    extern load_proc_flow shd_begin_seq;
    extern load_proc_flow shd_end_seq;
    extern load_proc_flow shd_out_key;
    extern load_proc_flow shd_out_value;
    
    
    class SERVER_EXPORT load_proc : public save_load_proc
    {
        IMPL_DERIVED(load_proc);

    public:
        load_proc(const std::string &_file);
        ~load_proc() override = default;

    public:
        bool begin() override;
        bool end() override;
        void begin_sequence();
        void end_sequence();
        void out_key();
        void out_value();
        void out(std::string &_value);
        void out(const std::string &_value);
        void out(int &_value);
        void out(float &_value);
        void out(bool &_value);

        bool has_value() const;
        bool has_key(const std::string& _value) const;
    };

    template <typename t>
    inline load_proc &operator>>(load_proc &_proc, t &_value)
    {
        _proc.out(_value);
        return _proc;
    }

    template <unsigned n>
    inline load_proc &operator>>(load_proc &_proc, const char(&_value)[n])
    {
        const std::string str(_value);
        _proc.out(str);
        return _proc;
    }

    template <>
    inline load_proc &operator >> (load_proc &_proc, load_proc_flow& _value)
    {
        switch (_value)
        {
        case load_proc_flow::k_begin_seq:
            _proc.begin_sequence();
            break;
        case load_proc_flow::k_end_seq:
            _proc.end_sequence();
            break;
        case load_proc_flow::k_out_key:
            _proc.out_key();
            break;
        case load_proc_flow::k_out_value:
            _proc.out_value();
            break;
        }
        return _proc;
    }

    template <typename t>
    inline load_proc &operator>>(load_proc &_proc, std::vector<t> &_value)
    {
        _proc >> shd_begin_seq;
        _value.clear();
        while (_proc.has_value())
        {
            _value.push_back({});
            _proc >> _value.back();
        }
        _proc >> shd_end_seq;
        return _proc;
    }

    template <typename t>
    inline load_proc &operator>>(load_proc &_proc, std::set<t> &_value)
    {
        _proc >> shd_begin_seq;
        _value.clear();
        while (_proc.has_value())
        {
            t temp;
            _proc >> temp;
            _value.insert(temp);
        }
        _proc >> shd_end_seq;
        return _proc;
    }

    template <typename t1, typename t2>
    inline load_proc &operator>>(load_proc &_proc, std::map<t1, t2> &_value)
    {
        _proc >> shd_begin_seq;

        _value.clear();
        while (_proc.has_value())
        {
            t1 key;
            t2 value;
            _proc >> shd_out_key >> _SAVE_LOAD_PROC_INTERNAL_1 >> shd_out_value >> key >> shd_out_key >> _SAVE_LOAD_PROC_INTERNAL_2 >> shd_out_value >> value;
            _value[key] = value;
        }

        _proc >> shd_end_seq;
        return _proc;
    }

}