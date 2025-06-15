#pragma once

#include "basic_macro.h"
#include "basic_prompts.h"

#include <concepts>
#include <sstream>
#include <string>
#include <type_traits>

namespace PRJ_NAME {
template<typename t>
std::string
print(const t& _value)
{
    if constexpr (std::is_same_v<t, std::string>)
        return _value;
    else if constexpr (std::is_arithmetic_v<t>)
        return std::to_string(_value);
    else if constexpr (std::is_pointer_v<t>) {
        std::stringstream ss;
        ss << "0x" << std::uppercase << std::hex << reinterpret_cast<intptr_t>(_value);
        return ss.str();
    } else if constexpr (requires { _value.to_string(); }) {
        return _value.to_string();
    }

    return print(prompt_id::k_undefined_print_behavior);
}

template<unsigned n>
inline std::string
print(const char (&_value)[n])
{
    return _value;
}

template<>
inline std::string
print<const char*>(const char* const& _value)
{
    return _value;
}

template<>
inline std::string
print<char*>(char* const& _value)
{
    return _value;
}

template<>
inline std::string
print<nullptr_t>(const nullptr_t& _value)
{
    return "0x0";
}

template<>
inline std::string
print<prompt_id>(const prompt_id& _value)
{
    return prompt(_value);
}

template<unsigned n>
inline void
format_print_impl(std::string& _buffer)
{
    return;
}

template<unsigned n, typename arg, typename... args>
inline void
format_print_impl(std::string& _buffer, arg&& _arg, args&&... _args)
{
    const std::string from = "[" + std::to_string(n) + "]";
    std::string to = print(_arg);

    size_t start_pos = 0;
    bool replaced = false;
    while ((start_pos = _buffer.find(from, start_pos)) != std::string::npos) {
        _buffer.replace(start_pos, from.size(), to);
        replaced = true;
        start_pos += to.length();
    }

    format_print_impl<n + 1>(_buffer, std::forward<args&&>(_args)...);
}

template<typename... args>
inline std::string
format_print(const std::string& _format, args&&... _args)
{
    std::string buffer = _format;
    format_print_impl<0>(buffer, std::forward<args&&>(_args)...);
    return buffer;
}

template<typename... args>
inline std::string
format_print(const prompt_id& _prompt_id, args&&... _args)
{
    std::string buffer = print(_prompt_id);
    format_print_impl<0>(buffer, std::forward<args&&>(_args)...);
    return buffer;
}

}
