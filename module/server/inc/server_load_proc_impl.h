#pragma once

#include "server_load_proc.h"

#include "server_save_load_impl.h"

#include "yaml-cpp/yaml.h"

#include <stack>

namespace PRJ_NAME {
struct pipeline_node
{
    bool is_anchor = false;
    YAML::Node node;

    static pipeline_node k_anchor;
};

class load_proc_impl : public save_load_proc_impl
{
    friend class load_proc;
    MEMBER_DECLARE(load_proc_impl, shared<YAML::Parser>, parser);
    MEMBER_DECLARE(load_proc_impl, bool, wait_for_key);

  public:
    load_proc_impl(load_proc& _facade, const std::string& _file);
    ~load_proc_impl() override = default;

  public:
    bool begin();
    bool end();
    void begin_map();
    void end_map();
    void begin_sequence();
    void end_sequence();
    void out_key();
    void out_value();
    void out(std::string& _value);
    void out(const std::string& _value);
    void out(int& _value);
    void out(float& _value);
    void out(bool& _value);
    bool has_value() const;
    bool has_key(const std::string& _value) const;

  protected:
    std::stack<pipeline_node> m_pipeline;
};
}