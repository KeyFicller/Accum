#include "server_load_proc_impl.h"

#include <fstream>

namespace PRJ_NAME {
pipeline_node pipeline_node::k_anchor = { true };

load_proc_impl::load_proc_impl(load_proc& _facade, const std::string& _file)
  : save_load_proc_impl(_facade, _file)
{
}

bool
load_proc_impl::begin()
{
    std::ifstream fin(file());
    std::stringstream ss;
    ss << fin.rdbuf();
    fin.close();
    m_pipeline.push({ false, YAML::Load(ss.str()) });
}

bool
load_proc_impl::end()
{
    ASSERT(m_pipeline.size() == 1);
    m_pipeline.pop();
}

void
load_proc_impl::begin_sequence()
{
    auto node = m_pipeline.top().node;
    m_pipeline.pop();
    m_pipeline.push(pipeline_node::k_anchor);
    for (int i = (int)node.size() - 1; i >= 0; i--) {
        m_pipeline.push({ false, node[i] });
    }
}

void
load_proc_impl::end_sequence()
{
    ASSERT(!has_value());
    m_pipeline.pop();
}

void
load_proc_impl::begin_map()
{
}

void
load_proc_impl::end_map()
{
    m_pipeline.pop();
}

bool
load_proc_impl::has_value() const
{
    return !m_pipeline.top().is_anchor;
}

bool
load_proc_impl::has_key(const std::string& _value) const
{
    return has_value() && !m_pipeline.top().node[_value].IsNull();
}

void
load_proc_impl::out_key()
{
    wait_for_key() = true;
}

void
load_proc_impl::out(const std::string& _value)
{
    ASSERT(wait_for_key());
    wait_for_key() = false;

    ASSERT(has_key(_value));
    m_pipeline.push({ false, m_pipeline.top().node[_value] });
}

void
load_proc_impl::out(std::string& _value)
{
    _value = m_pipeline.top().node.as<std::string>();
    m_pipeline.pop();
}

void
load_proc_impl::out(int& _value)
{
    _value = m_pipeline.top().node.as<int>();
    m_pipeline.pop();
}

void
load_proc_impl::out(float& _value)
{
    _value = m_pipeline.top().node.as<float>();
    m_pipeline.pop();
}

void
load_proc_impl::out(bool& _value)
{
    _value = m_pipeline.top().node.as<bool>();
    m_pipeline.pop();
}
}