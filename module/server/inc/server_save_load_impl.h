#pragma once

#include "server_save_load.h"

namespace PRJ_NAME
{
    class save_load_proc_impl : public implement_t<save_load_proc>
    {
        MEMBER_DECLARE(save_load_proc_impl, std::string, file);
        friend class save_load_proc;
    public:
        save_load_proc_impl(save_load_proc& _facade, const std::string& _file);
        ~save_load_proc_impl() override = default;
    };
}