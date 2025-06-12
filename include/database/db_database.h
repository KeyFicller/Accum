#pragma once

#include "db_object.h"

namespace PRJ_NAME
{
    class database_impl;

    class DB_EXPORT database
    {
        IMPL_BASE(database);
        DISABLE_COPY(database);
    public:
        database();
        virtual ~database();

    public:
        bool add_object(db_object* _object, db_object_id& _id);
        bool remove_object(const db_object_id& _id);
    };
}