#pragma once

#include "basic_alias.h"
#include "basic_log.h"

#include "spdlog/spdlog.h"

namespace PRJ_NAME {
class log_impl : public implement_t<log>
{
    MEMBER_DECLARE(log_impl, std::string, name);
    MEMBER_DECLARE(log_impl, int, level);

  public:
    log_impl(log& _facade, const std::string& _name);
    ~log_impl() override = default;

  public:
#define LOGGER_FUNCIONS(_LEVEL)                                                                                        \
    void _LEVEL(const char* _message) { m_raw_logger->_LEVEL(_message); }

    LOGGER_FUNCIONS(trace)
    LOGGER_FUNCIONS(info)
    LOGGER_FUNCIONS(warn)
    LOGGER_FUNCIONS(error)
    LOGGER_FUNCIONS(critical)

#undef LOGGER_FUNCTIONS

  protected:
    shared<spdlog::logger> m_raw_logger;
};
}