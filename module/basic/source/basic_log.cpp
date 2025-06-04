#include "basic_log.h"
#include "basic_log_impl.h"

namespace PRJ_NAME
{
    log::log(const std::string &_name)
    {
        IMPL_INITIALIZE(log, _name);
    }

    log::~log()
    {
        IMPL_TERMINATE();
    }

    void log::set_level(int _level)
    {
        IMPL(log)->set_level(_level);
    }

    int log::level() const
    {
        return IMPL(log)->level();
    }

    void log::trace(const std::string &_message)
    {
        return IMPL(log)->trace(_message.c_str());
    }
    void log::info(const std::string &_message)
    {
        return IMPL(log)->info(_message.c_str());
    }
    void log::warn(const std::string &_message)
    {
        return IMPL(log)->warn(_message.c_str());
    }
    void log::error(const std::string &_message)
    {
        return IMPL(log)->error(_message.c_str());
    }
    void log::critical(const std::string &_message)
    {
        return IMPL(log)->critical(_message.c_str());
    }
}