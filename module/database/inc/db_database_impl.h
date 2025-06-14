#pragma once

#include "db_database.h"
#include "db_handle.h"

#include <map>

namespace PRJ_NAME {
class global_handle_helper
{
    using owner_db_map = std::map<db_handle, database*>;
    MEMBER_DECLARE(global_handle_helper, handle_allocator<db_handle>, allocator);
    MEMBER_DECLARE(global_handle_helper, global_handle_helper::owner_db_map, owner_map);
    MEMBER_DECLARE(global_handle_helper, std::set<database*>, alive_databases);

  public:
    global_handle_helper() = default;
    ~global_handle_helper() = default;
};

class database_impl : public implement_t<database>
{
    IMPL_EXPOSE(database);
    using map_obj = std::map<db_handle, shared<db_object>>;
    MEMBER_DECLARE(database_impl, map_obj, map_db_obj);
    friend class db_object_id_impl;
    friend class db_object_impl;
    friend class database;

  public:
    database_impl(database& _facade);
    ~database_impl() override;

  private:
    static global_handle_helper& helper();
    bool add_object(db_object* _object, db_object_id& _id);
    bool remove_object(const db_object_id& _id);
    db_object* get_object(db_handle _handle) const;
};
}