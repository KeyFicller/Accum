#include "server_save_load_impl.h"

namespace PRJ_NAME
{
    save_load_proc_impl::save_load_proc_impl(save_load_proc &_facade, const std::string &_file)
        : implement_t<save_load_proc>(_facade), m_file(_file)
    {
    }
}