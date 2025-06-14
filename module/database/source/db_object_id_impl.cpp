#include "db_object_id_impl.h"

#include "db_database_impl.h"

namespace PRJ_NAME {
db_object_id_impl::db_object_id_impl(db_object_id& _facade)
  : implement_t<db_object_id>(_facade)
{
}

db_object_id_impl::db_object_id_impl(db_object_id& _facade, db_handle _handle)
  : implement_t<db_object_id>(_facade)
  , m_handle(_handle)
{
}

db_object_id_impl::~db_object_id_impl() {}

bool
db_object_id_impl::is_valid() const
{
    int ret = true;
    if (facade()->operator==(db_object_id::k_null))
        return ret = false;
    auto& helper = database_impl::helper();
    auto iter = helper.owner_map().find(handle());
    if (iter == helper.owner_map().end())
        return ret = false;
    if (!helper.alive_databases().count(iter->second))
        return ret = false;

    return true;
}

db_object_id_impl::
operator bool() const
{
    return is_valid();
}

bool
db_object_id_impl::operator==(const db_object_id& _other) const
{
    return handle() == _other.handle();
}

db_object*
db_object_id_impl::open_impl(db_access_mode _mode)
{
    if (facade()->operator==(db_object_id::k_null))
        return nullptr;
    auto& helper = database_impl::helper();
    auto iter = helper.owner_map().find(handle());
    if (iter == helper.owner_map().end())
        return nullptr;
    if (!helper.alive_databases().count(iter->second))
        return nullptr;

    return IMPL_GET(database, iter->second)->get_object(handle());
}

void
db_object_id_impl::duplicate_from(const implement_t<db_object_id>* _other_impl)
{
    handle() = _other_impl->self_t<db_object_id_impl>()->handle();
}
}