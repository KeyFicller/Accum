#include "db_database.h"
#include "db_database_impl.h"

namespace PRJ_NAME
{
    database::database()
    {
        IMPL_INITIALIZE(database);
    }

    database::~database()
    {
        IMPL_TERMINATE();
    }

    bool database::add_object(db_object *_object, db_object_id &_id)
    {
        return IMPL(database)->add_object(_object, _id);
    }

    bool database::remove_object(const db_object_id &_id)
    {
        return IMPL(database)->remove_object(_id);
    }
}