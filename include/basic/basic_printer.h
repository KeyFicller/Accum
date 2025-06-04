#pragma once

#include "basic_macro.h"

#include <string>
#include <type_traits>

#define PRINTER_BUFFER_SIZE 256

// TODO: @KeyFciller  Copy from Project periscope
namespace PRJ_NAME
{

    template <typename ...args>
    std::string c_style_print(const char* _format, args&&... _args)
    {
        char buffer[PRINTER_BUFFER_SIZE];
        snprintf(buffer, PRINTER_BUFFER_SIZE, _format, std::forward<args>(_args)...);
        return buffer;
    }

    namespace printer
    {
    }
}