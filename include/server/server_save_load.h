#pragma once

#include "server_export.h"

#include "basic_include.h"

#define _SAVE_LOAD_PROC_INTERNAL_1 "___KEY"
#define _SAVE_LOAD_PROC_INTERNAL_2 "___VALUE"

namespace PRJ_NAME
{
    class save_proc;
    class load_proc;
    class SERVER_EXPORT save_load_server
    {
        friend class save_load_proc;

    protected:
        virtual void save(save_proc&_proc, const std::string &_key) = 0;
        virtual void load(load_proc&_proc, const std::string &_key) = 0;
    };

    class save_load_proc_impl;
    class SERVER_EXPORT save_load_proc
    {
        IMPL_BASE(save_load_proc);

    public:
        virtual ~save_load_proc();

    protected:
        save_load_proc(const std::string &_file);

    public:
        virtual bool begin() = 0;
        virtual bool end() = 0;
    };
}