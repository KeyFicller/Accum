#include "server_save_proc.h"

#include "server_save_proc_impl.h"

namespace PRJ_NAME {
save_proc::save_proc(const std::string& _file)
  : save_load_proc(*new save_proc_impl(*this, _file))
{
}

bool
save_proc::begin()
{
    return IMPL(save_proc)->begin();
}

bool
save_proc::end()
{
    return IMPL(save_proc)->end();
}

void
save_proc::begin_map()
{
    return IMPL(save_proc)->begin_map();
}

void
save_proc::end_map()
{
    return IMPL(save_proc)->end_map();
}

void
save_proc::begin_sequence(bool _flow)
{
    return IMPL(save_proc)->begin_sequence(_flow);
}

void
save_proc::end_sequence()
{
    return IMPL(save_proc)->end_sequence();
}

void
save_proc::in_key()
{
    return IMPL(save_proc)->in_key();
}

void
save_proc::in_value()
{
    return IMPL(save_proc)->in_value();
}

void
save_proc::in(const std::string& _value)
{
    (*IMPL(save_proc)->emitter()) << _value;
}

void
save_proc::in(int _value)
{
    (*IMPL(save_proc)->emitter()) << _value;
}

void
save_proc::in(float _value)
{
    (*IMPL(save_proc)->emitter()) << _value;
}

void
save_proc::in(bool _value)
{
    (*IMPL(save_proc)->emitter()) << _value;
}
}