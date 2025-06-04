#pragma once

#define PRJ_NAME Accum

#ifdef _WIN32
#define _DLL_EXPORT __declspec(dllexport)
#else
#define _DLL_EXPORT __attribute__((visibility("default")))
#endif

#ifdef _WIN32
#define _DLL_IMPORT __declspec(dllimport)
#else
#define _DLL_IMPORT __attribute__((visibility("default")))
#endif

#define _DLL_C_EXPORT extern "C"
#define _DLL_C_IMPORT extern "C"

#define EXPAND(_STATEMENT) _STATEMENT
#define STRINGFY(_STATEMENT) #_STATEMENT

#define _ARGS_AUGUMENTOR(...) unused, __VA_ARGS__

#define SAFE_DELETE(_POINTER)   \
    do                          \
    {                           \
        if (_POINTER)           \
        {                       \
            delete _POINTER;    \
            _POINTER = nullptr; \
        }                       \
    } while (0)
#define SAFE_ARRAY_DELETE(_POINTER) \
    do                              \
    {                               \
        if                          \
        {                           \
            _POINTER                \
        }                           \
        {                           \
            delete[] _POINTER;      \
            _POINTER = nullptr;     \
        }                           \
    } while (0)

#define INSTANCE(_CLASS, ...)                         \
public:                                               \
    static _CLASS &instance()                         \
    {                                                 \
        static _CLASS *ins = new _CLASS(__VA_ARGS__); \
        return *ins;                                  \
    }
#define GET_INSTNACE(_CLASS) _CLASS::instance()

#define _AUTO_NAME_IMPL2(_PREFIX, _LINE) _PREFIX##_LINE
#define _AUTO_NAME_IMPL1(_PREFIX, _LINE) _AUTO_NAME_IMPL2(_PREFIX, _LINE)
#define AUTO_NAME(_PREFIX) _AUTO_NAME_IMPL1(_PREFIX, __LINE__)

#define MEMBER_DECLARE(_CLASS, _TYPE, _NAME, ...)    \
public:                                              \
    _CLASS &set_##_NAME(const _TYPE &_NAME)          \
    {                                                \
        m_##_NAME = _NAME;                           \
        return *this;                                \
    };                                               \
    const _TYPE &_NAME() const { return m_##_NAME; } \
    _TYPE &_NAME() { return m_##_NAME; }             \
                                                     \
protected:                                           \
    _TYPE m_##_NAME = {__VA_ARGS__}

#define REFERENCE_MEMBER_DECLARE(_CLASS, _TYPE, _NAME) \
public:                                                \
    _CLASS &set_##_NAME(const _TYPE &_NAME)            \
    {                                                  \
        m_##_NAME = _NAME;                             \
        return *this;                                  \
    };                                                 \
    const _TYPE &_NAME() const { return m_##_NAME; }   \
    _TYPE &_NAME() { return m_##_NAME; }               \
                                                       \
protected:                                             \
    _TYPE &m_##_NAME

#define DISABLE_COPY(_CLASS)               \
private:                                   \
    _CLASS(const _CLASS &_other) = delete; \
    _CLASS &operator=(const _CLASS &_other) = delete
