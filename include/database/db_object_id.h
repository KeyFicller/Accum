#pragma once

#include "db_export.h"
#include "db_handle.h"

#include "basic_implment.h"

namespace PRJ_NAME {
class database;
class db_object;
class db_object_id_impl;

enum class db_access_mode
{
    k_read,
    k_write,
    k_xn
};

class DB_EXPORT db_object_id
{
    IMPL_BASE(db_object_id);

  public:
    db_object_id();
    db_object_id(db_handle _handle);
    db_object_id(const db_object_id& _other);
    virtual ~db_object_id();

  public:
    static db_object_id k_null;

  public:
    bool is_valid() const;
    operator bool() const;
    bool operator==(const db_object_id& _other) const;
    db_object_id& operator=(const db_object_id& _other);
    db_handle handle() const;

    template<typename t>
    t* open(db_access_mode _mode)
    {
        return dynamic_cast<t*>(open_impl(_mode));
    }

  private:
    db_object* open_impl(db_access_mode _mode);
};
};