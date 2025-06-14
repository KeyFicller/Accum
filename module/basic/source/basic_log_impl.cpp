#include "basic_log_impl.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace PRJ_NAME {
log_impl::log_impl(log& _facade, const std::string& _name)
  : implement_t<log>(_facade)
  , m_name(_name)
{
    m_raw_logger = spdlog::stdout_color_mt(name());
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_raw_logger->set_level(spdlog::level::trace);
}
}