#pragma once

#include "db_object_id.h"

namespace PRJ_NAME
{
    class db_object_id_impl : public implement_t<db_object_id>
    {
        MEMBER_DECLARE(db_object_id_impl, db_handle, handle, -1);
        friend class db_object_id;
    public:
        db_object_id_impl(db_object_id &_facade);
        db_object_id_impl(db_object_id &_facade, db_handle _handle);
        ~db_object_id_impl() override;

    public:
        bool is_valid() const;
        operator bool() const;
        bool operator==(const db_object_id &_other) const;
        db_object *open_impl(db_access_mode _mode);

    private:
        void duplicate_from(const implement_t<db_object_id>* _other_impl) override;
    };
}