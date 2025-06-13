#pragma once

#include "server_save_proc.h"

#include "server_save_load_impl.h"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace PRJ_NAME
{
    class save_proc_impl : public save_load_proc_impl
    {
        friend class save_proc;
        MEMBER_DECLARE(save_proc_impl, shared<YAML::Emitter>, emitter);
    public:
        save_proc_impl(save_proc& _facade, const std::string& _file);
        ~save_proc_impl() override = default;

    public:
        bool begin();
        bool end();
        void begin_map();
        void end_map();
        void begin_sequence(bool _flow = false);
        void end_sequence();
        void in_key();
        void in_value();
    };
}