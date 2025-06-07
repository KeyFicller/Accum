#pragma once

#include "basic_export.h"
#include "basic_implment.h"

#include <string>

namespace PRJ_NAME
{
    class log_impl;

    template <typename... args>
    std::string cstyle_format_print(const char *_format, args &&..._args)
    {
        char buffer[PRINTER_BUFFER_SIZE];
        snprintf(buffer, PRINTER_BUFFER_SIZE, _format, std::forward<args>(_args)...);
        return buffer;
    }

    class BASIC_EXPORT log
    {
        INSTANCE(log, "logger");
        IMPL_BASE(log);

    public:
        log(const std::string &_name);
        virtual ~log();

    public:
        /// @brief 
        /// @param _level 
        void set_level(int _level);

        /// @brief 
        /// @return 
        int level() const;

        /// @brief 
        /// @param _message 
        void trace(const std::string &_message);

        /// @brief 
        /// @param _message 
        void info(const std::string &_message);

        /// @brief 
        /// @param _message 
        void warn(const std::string &_message);

        /// @brief 
        /// @param _message 
        void error(const std::string &_message);

        /// @brief 
        /// @param _message 
        void critical(const std::string &_message);

        template <typename ...args>
        void trace(const std::string& _format, args&&... _args)
        {
            return trace(cstyle_format_print(_format.c_str(), std::forward<args>(_args)...));
        }

        template <typename ...args>
        void error(const std::string& _format, args&&... _args)
        {
            return error(cstyle_format_print(_format.c_str(), std::forward<args>(_args)...));
        }
    };
    
}

#define TRACE(...)  ::PRJ_NAME::log::instance().trace(__VA_ARGS__)
#define INFO(...)  ::PRJ_NAME::log::instance().info(__VA_ARGS__)
#define WARN(...)  ::PRJ_NAME::log::instance().warn(__VA_ARGS__)
#define ERROR(...)  ::PRJ_NAME::log::instance().error(__VA_ARGS__)
#define CRITICAL(...)  ::PRJ_NAME::log::instance().critical(__VA_ARGS__)