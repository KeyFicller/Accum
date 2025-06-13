#include "server_save_load.h"

#include "server_save_load_impl.h"

namespace PRJ_NAME
{
    save_load_proc::~save_load_proc()
    {
        IMPL_TERMINATE();
    }

    save_load_proc::save_load_proc(const std::string &_file)
    {
        IMPL_INITIALIZE(save_load_proc, _file);
    }
}