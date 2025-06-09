#include "db_object_id.h"
#include "db_object_id_impl.h"

namespace PRJ_NAME
{
    db_object_id::db_object_id()
    {
        IMPL_INITIALIZE(db_object_id);
    }

    db_object_id::db_object_id(db_handle _handle)
    {
        IMPL_INITIALIZE(db_object_id, _handle);
    }

    db_object_id::db_object_id(const db_object_id &_other)
    {
        auto cpy_impl = _other.m_impl->duplicate();
        if (cpy_impl == m_impl)
            ASSERT(false);

        auto cpy_facade = this;
        cpy_impl->set_facade(cpy_facade);
    }

    db_object_id::~db_object_id()
    {
        IMPL_TERMINATE();
    }

    db_object_id db_object_id::k_null = db_object_id(-1);

    bool db_object_id::is_valid() const
    {
        return IMPL(db_object_id)->is_valid();
    }

    db_object_id::operator bool() const
    {
        return IMPL(db_object_id)->operator bool();
    }

    bool db_object_id::operator==(const db_object_id &_other) const
    {
        return IMPL(db_object_id)->operator==(_other);
    }

    db_handle db_object_id::handle() const
    {
        return IMPL(db_object_id)->handle();
    }
}