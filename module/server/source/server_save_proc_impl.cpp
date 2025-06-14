#include "server_save_proc_impl.h"

namespace PRJ_NAME {
save_proc_impl::save_proc_impl(save_proc& _facade, const std::string& _file)
  : save_load_proc_impl(_facade, _file)
{
}

bool
save_proc_impl::begin()
{
    if (emitter())
        return false;

    emitter() = make_shared<YAML::Emitter>();
    begin_map();
    return true;
}

bool
save_proc_impl::end()
{
    if (!emitter())
        return false;
    ;

    end_map();
    std::ofstream fout(file());
    if (!fout.good())
        return false;
    ;

    fout << emitter()->c_str();
    fout.close();
    emitter().reset();
    return true;
}
void
save_proc_impl::begin_map()
{
    (*emitter()) << YAML::BeginMap;
}
void
save_proc_impl::end_map()
{
    (*emitter()) << YAML::EndMap;
}
void
save_proc_impl::begin_sequence(bool _flow)
{
    if (_flow)
        (*emitter()) << YAML::Flow;
    (*emitter()) << YAML::BeginSeq;
}
void
save_proc_impl::end_sequence()
{
    (*emitter()) << YAML::EndSeq;
}
void
save_proc_impl::in_key()
{
    (*emitter()) << YAML::Key;
}
void
save_proc_impl::in_value()
{
    (*emitter()) << YAML::Value;
}
}