#pragma once

#include "basic_export.h"
#include "basic_implement.h"

#include <string>

namespace PRJ_NAME {
class filer_impl;

/// @brief This class provides the ability to serialize data to byte stream.
class BASIC_EXPORT filer
{
    IMPL_BASE(filer);
    DISABLE_COPY(filer);

  public:
    /// @brief Constructor.
    filer();

    /// @brief Destructor.
    virtual ~filer();

  public:
    /// @brief Write in bytes data.
    /// @param _value Input bytes data.
    /// @param _bytes Size of data.
    /// @return Self reference.
    filer& write_bytes(const void* _value, int _bytes);

    /// @brief Read out bytes data.
    /// @param _value Output bytes data.
    /// @param _bytes Size of data.
    /// @return Self reference.
    filer& read_bytes(void* _value, int _bytes);

    /// @brief Flush byte stream from another filer.
    /// @param _other Filer that byte stream come from.
    /// @param _bytes Size of data.
    void flush_in(filer& _other, int _bytes);

    /// @brief Flush byte stream to another filer.
    /// @param _other Filer that byte stream goes to.
    /// @param _bytes Size of data.
    void flush_out(filer& _other, int _bytes);

    /// @brief Seek to a given position of byte stream.
    /// @param _position The position.
    /// @return True if success, else false.
    bool seek(int _position);

    /// @brief Get current position in byte stream.
    /// @return Current position in byte stream.
    int position() const;

    /// @brief Clear byte stream data.
    /// @return Self reference.
    filer& clear();
};

/// @brief This class defines the main template on how a type of data got serialized.
/// @tparam t Type to be serialized.
template<typename t>
struct filer_serializer
{
    static_assert(std::is_pod<t>(), "Non pod type can't use default serializer logic.");

    /// @brief Serialize a value of this type of data to byte stream.
    /// @param _filer The byte stream wrapper.
    /// @param _value The data.
    static void dump(filer& _filer, const t& _value) { _filer.write_bytes(&_value, sizeof(t)); }

    /// @brief Deserialize a value of this type of data from byte stream.
    /// @param _filer The byte stream wrapper.
    /// @param _value The data.
    static void load(filer& _filer, t& _value) { _filer.read_bytes(&_value, sizeof(t)); }
};

/// @brief Main template for serializing a type of data into byte stream.
/// @tparam t Type of data.
/// @param _filer The byte stream wrapper.
/// @param _value The data.
/// @return Self reference.
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