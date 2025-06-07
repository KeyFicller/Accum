#include "basic_filer_impl.h"
#include "basic_assert.h"

namespace PRJ_NAME
{
    filer_impl::filer_impl(filer &_facade)
        : implement_t<filer>(_facade)
    {
        data().resize(10);
    }

    filer &filer_impl::write_bytes(const void *_value, int _bytes)
    {
        const size_t capacity = index() + size_t(_bytes);
        if (capacity > data().size())
            data().resize(2 * capacity);
        memcpy(data().data() + index(), _value, _bytes);
        index() += _bytes;
        last_index() = std::max(last_index(), index());
        return *facade();
    }

    filer &filer_impl::read_bytes(void *_value, int _bytes)
    {
        ASSERT(index() + _bytes <= last_index());
        memcpy(_value, data().data() + index(), _bytes);
        index() += _bytes;
        return *facade();
    }

    void filer_impl::flush_in(filer &_other, int _bytes)
    {
        ASSERT(_other.m_impl->index() + _bytes <= _other.m_impl->last_index());
        write_bytes(_other.m_impl->ptr(), _bytes);
        _other.m_impl->index() += _bytes;
    }

    void filer_impl::flush_out(filer &_other, int _bytes)
    {
        ASSERT(index() + _bytes <= last_index());
        _other.write_bytes(ptr(), _bytes);
        index() += _bytes;
    }

    bool filer_impl::seek(int _position)
    {
        if (_position < 0 || _position > last_index())
            return false;
        index() = _position;
        return true;
    }

    int filer_impl::position() const
    {
        return (int)index();
    }

    filer &filer_impl::clear()
    {
        data().clear();
        index() = 0;
        last_index() = 0;
        return *facade();
    }

    void *filer_impl::ptr()
    {
        return data().data() + index();
    }
}