#pragma once

#include "db_object_id.h"

#include "basic_include.h"

namespace PRJ_NAME {
class database;
class db_object_impl;

class DB_EXPORT db_object
{
    IMPL_BASE(db_object);

  public:
    db_object();
    virtual ~db_object();

  public:
    bool open(db_access_mode _mode);
    bool close();
    filer& xn_filer();
    database* owner() const;
    db_object_id id() const;
};
}