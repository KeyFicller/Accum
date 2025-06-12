#include "db_database_impl.h"

#include "db_object_impl.h"

namespace PRJ_NAME
{
    database_impl::database_impl(database &_facade)
        : implement_t(_facade)
    {
        helper().alive_databases().insert(facade());
    }

    database_impl::~database_impl()
    {
        helper().alive_databases().erase(facade());
    }

    global_handle_helper &database_impl::helper()
    {
        static global_handle_helper helper_inst;
        return helper_inst;
    }
    bool database_impl::add_object(db_object *_object, db_object_id &_id)
    {
        bool ret = true;
        auto handle = helper().allocator().next_handle();
        helper().allocator().insert_handle(handle);
        map_db_obj().insert({handle, shared<db_object>(_object)});
        helper().owner_map().insert({handle, facade()});
        IMPL_GET(db_object, _object)->set_id(handle);
        ASSERT(_object->close());
        _id = db_object_id(handle);
        return ret;
    }
    bool database_impl::remove_object(const db_object_id &_id)
    {
        bool ret = true;
        auto iter = map_db_obj().find(_id);
        if (iter == map_db_obj().end())
            return ret = false;
        map_db_obj().erase(iter);
        helper().owner_map().erase(_id);
        return ret;
    }
    db_object *database_impl::get_object(db_handle _handle) const
    {
        return map_db_obj().at(_handle).get();
    }
}