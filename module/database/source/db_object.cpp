#include "db_object.h"

#include "db_object_impl.h"

namespace PRJ_NAME
{
    db_object::db_object()
    {
        IMPL_INITIALIZE(db_object);
    }

    db_object::~db_object()
    {
        IMPL_TERMINATE();
    }

    bool db_object::open(db_access_mode _mode)
    {
        return IMPL(db_object)->open(_mode);
    }

    bool db_object::close()
    {
        return IMPL(db_object)->close();
    }

    filer &db_object::xn_filer()
    {
        return IMPL(db_object)->xn_filer();
    }

    database *db_object::owner() const
    {
        return IMPL(db_object)->owner();
    }

    db_object_id db_object::id() const
    {
        return IMPL(db_object)->id();
    }
}