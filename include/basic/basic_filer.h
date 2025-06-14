#pragma once

#include "basic_export.h"
#include "basic_implment.h"

#include <string>

namespace PRJ_NAME {
class filer_impl;

class BASIC_EXPORT filer
{
    IMPL_BASE(filer);
    DISABLE_COPY(filer);

  public:
    filer();
    virtual ~filer();

  public:
    /// @brief
    /// @param _value
    /// @param _bytes
    /// @return
    filer& write_bytes(const void* _value, int _bytes);

    /// @brief
    /// @param _value
    /// @param _bytes
    /// @return
    filer& read_bytes(void* _value, int _bytes);

    void flush_in(filer& _other, int _bytes);
    void flush_out(filer& _other, int _bytes);
    bool seek(int _position);
    int position() const;
    filer& clear();
};

template<typename t>
struct filer_serializer
{
    static_assert(std::is_pod<t>(), "Non pod type can't use default serializer logic.");

    static void dump(filer& _filer, const t& _value) { _filer.write_bytes(&_value, sizeof(t)); }

    static void load(filer& _filer, t& _value) { _filer.read_bytes(&_value, sizeof(t)); }
};

template<typename t>
filer&
operator<<(filer& _filer, const t& _value)
{
    filer_serializer<t>::dump(_filer, _value);
    return _filer;
}

template<typename t>
filer&
operator>>(filer& _filer, t& _value)
{
    filer_serializer<t>::load(_filer, _value);
    return _filer;
}

template<>
struct filer_serializer<std::string>
{
    static void dump(filer& _filer, const std::string& _value)
    {
        _filer << (int)(_value.size());
        if (_value.size())
            _filer.write_bytes(&_value.at(0), _value.size());
    }

    static void load(filer& _filer, std::string& _value)
    {
        int length = 0;
        _filer >> length;
        _value.resize(length);
        if (length)
            _filer.read_bytes(&_value.at(0), length);
    }
};

template<>
struct filer_serializer<char*>
{
    static void dump(filer& _filer, const char* _value) { return filer_serializer<std::string>::dump(_filer, _value); }
};

template<unsigned n>
struct filer_serializer<char[n]>
{
    static void dump(filer& _filer, const char (&_value)[n])
    {
        return filer_serializer<std::string>::dump(_filer, _value);
    }
};
}