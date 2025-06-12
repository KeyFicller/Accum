#include "db_object_impl.h"

#include "db_database_impl.h"

#include <map>

namespace PRJ_NAME
{
    db_object_impl::db_object_impl(db_object &_facade)
        : implement_t<db_object>(_facade)
    {
        set_open_status(db_open_status::k_new_created);
    }

    db_object_impl::~db_object_impl()
    {
    }

    bool db_object_impl::open(db_access_mode _mode)
    {
        if (open_status() != db_open_status::k_closed || !id().is_valid())
            return false;
        static std::map<db_access_mode, db_open_status> status_map = {
            {db_access_mode::k_read, db_open_status::k_read_opened},
            {db_access_mode::k_write, db_open_status::k_write_opened},
            {db_access_mode::k_xn, db_open_status::k_xn_opened}};
        set_open_status(status_map.at(_mode));
        return true;
    }

    bool db_object_impl::close()
    {
        if (!id().is_valid())
            return false;
        if (open_status() != db_open_status::k_closed)
        {

            set_open_status(db_open_status::k_closed);
        }
        return true;
    }

    filer &db_object_impl::xn_filer()
    {
        return m_xn_filer;
    }

    database *db_object_impl::owner() const
    {
        if (!id().is_valid())
            return nullptr;
        auto &_helper = database_impl::helper();
        auto iter = _helper.owner_map().find(id().handle());
        if (iter == _helper.owner_map().end())
            return nullptr;
        database *result = iter->second;
        if (!_helper.alive_databases().count(result))
            return nullptr;
        return result;
    }
}