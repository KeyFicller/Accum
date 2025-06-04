#pragma once

#include "basic_export.h"
#include "basic_implment.h"
#include "basic_printer.h"

#include <string>

namespace PRJ_NAME
{
    class log_impl;

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
            return trace(c_style_print(_format.c_str(), std::forward<args>(_args)...));
        }
    };
    
}