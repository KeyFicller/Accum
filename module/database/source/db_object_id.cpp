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
        : db_object_id()
    {
        IMPL(db_object_id)->duplicate_from(_other.m_impl);
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

    db_object_id &db_object_id::operator=(const db_object_id &_other)
    {
        IMPL(db_object_id)->duplicate_from(_other.m_impl);
        return *this;
    }

    db_handle db_object_id::handle() const
    {
        return IMPL(db_object_id)->handle();
    }

    db_object* db_object_id::open_impl(db_access_mode _mode)
    {
        return IMPL(db_object_id)->open_impl(_mode);
    }
}