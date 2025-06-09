#include "db_object.h"

namespace PRJ_NAME
{
    enum class db_open_status
    {
        k_closed,
        k_new_created,
        k_read_opened,
        k_write_opened,
        k_xn_opened
    };

    class db_object_impl : public implement_t<db_object>
    {
        MEMBER_DECLARE(db_object_impl, db_open_status, open_status);
        MEMBER_DECLARE(db_object_impl, db_object_id, id, db_object_id::k_null);
        friend class db_object;
        IMPL_EXPOSE(db_object);

    public:
        db_object_impl(db_object &_facade);
        ~db_object_impl() override;

    public:
        bool open(db_access_mode _mode);
        bool close();
        filer &xn_filer();
        database* owner() const;

    protected:
        filer m_xn_filer;
    };
}