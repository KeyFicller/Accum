#include "basic_filer.h"
#include "basic_filer_impl.h"

#include "tracy/Tracy.hpp"

namespace PRJ_NAME
{
    filer::filer()
    {
        IMPL_INITIALIZE(filer);
    }

    filer::~filer()
    {
        IMPL_TERMINATE();
    }

    filer &filer::write_bytes(const void *_value, int _bytes)
    {
        return IMPL(filer)->write_bytes(_value, _bytes);
    }

    filer &filer::read_bytes(void *_value, int _bytes)
    {
        ZoneScoped;
        return IMPL(filer)->read_bytes(_value, _bytes);
    }

    void filer::flush_in(filer &_other, int _bytes)
    {
        IMPL(filer)->flush_in(_other, _bytes);
    }

    void filer::flush_out(filer &_other, int _bytes)
    {
        IMPL(filer)->flush_out(_other, _bytes);
    }

    bool filer::seek(int _position)
    {
        return IMPL(filer)->seek(_position);
    }

    int filer::position() const
    {
        return IMPL(filer)->position();
    }

    filer &filer::clear()
    {
        return IMPL(filer)->clear();
    }
}