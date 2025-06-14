#include "server_load_proc.h"

#include "server_load_proc_impl.h"

namespace PRJ_NAME
{
    load_proc_flow shd_begin_seq = load_proc_flow::k_begin_seq;
    load_proc_flow shd_end_seq = load_proc_flow::k_end_seq;
    load_proc_flow shd_out_key = load_proc_flow::k_out_key;
    load_proc_flow shd_out_value = load_proc_flow::k_out_value;

    load_proc::load_proc(const std::string &_file)
        : save_load_proc(*new load_proc_impl(*this, _file))
    {
    }

    bool load_proc::begin()
    {
        return IMPL(load_proc)->begin();
    }

    bool load_proc::end()
    {
        return IMPL(load_proc)->end();
    }

    void load_proc::begin_sequence()
    {
        return IMPL(load_proc)->begin_sequence();
    }

    void load_proc::end_sequence()
    {
        return IMPL(load_proc)->end_sequence();
    }

    void load_proc::out_key()
    {
        return IMPL(load_proc)->out_key();
    }

    void load_proc::out_value()
    {
        //return IMPL(load_proc)->out_value();
    }

    void load_proc::out(std::string &_value)
    {
        return IMPL(load_proc)->out(_value);
    }

    void load_proc::out(const std::string &_value)
    {
        return IMPL(load_proc)->out(_value);
    }

    void load_proc::out(int &_value)
    {
        return IMPL(load_proc)->out(_value);
    }

    void load_proc::out(float &_value)
    {
        return IMPL(load_proc)->out(_value);
    }

    void load_proc::out(bool &_value)
    {
        return IMPL(load_proc)->out(_value);
    }

    bool load_proc::has_value() const
    {
        return IMPL(load_proc)->has_value();
    }

    bool load_proc::has_key(const std::string &_value) const
    {
        return IMPL(load_proc)->has_key(_value);
    }
}