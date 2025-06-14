#pragma once

#include "db_database.h"
#include "db_object.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

class DBObjectTest : public testing::Test
{
  protected:
    void SetUp() override
    {
        db = new database();
        obj = new db_object();
        db->add_object(obj, obj_id);
    }

    void TearDown() override
    {
        if (!obj->id().is_valid())
            delete obj;
        delete db;
    }

    database* db;
    db_object* obj;
    db_object_id obj_id;
};

TEST_F(DBObjectTest, OpenCloseOperations)
{
#if 0
    // 初始状态应为关闭
    EXPECT_EQ(obj->open_status(), db_open_status::k_closed);
    
    // 测试打开
    EXPECT_TRUE(obj->open(db_access_mode::k_read));
    EXPECT_EQ(obj->open_status(), db_open_status::k_read_opened);
    
    // 测试重复打开
    EXPECT_FALSE(obj->open(db_access_mode::k_read));
    
    // 测试关闭
    EXPECT_TRUE(obj->close());
    EXPECT_EQ(obj->open_status(), db_open_status::k_closed);
    
    // 测试事务模式
    EXPECT_TRUE(obj->open(db_access_mode::k_xn));
    EXPECT_EQ(obj->open_status(), db_open_status::k_xn_opened);
    EXPECT_TRUE(obj->close());
#endif
}

TEST_F(DBObjectTest, OwnerAndID)
{
    EXPECT_EQ(obj->owner(), db);
    EXPECT_EQ(obj->id(), obj_id);

    // 测试无效ID
    db_object invalid_obj;
    EXPECT_EQ(invalid_obj.owner(), nullptr);
    EXPECT_FALSE(invalid_obj.id().is_valid());
}

TEST_F(DBObjectTest, TransactionFiler)
{
    obj->open(db_access_mode::k_xn);

    filer& f = obj->xn_filer();
    EXPECT_NE(&f, nullptr);

    // 测试filer基本操作
    int value = 42;
    f.write_bytes(&value, sizeof(value));

    int result = 0;
    f.seek(0);
    f.read_bytes(&result, sizeof(result));
    EXPECT_EQ(result, 42);

    obj->close();
}

TEST_F(DBObjectTest, InvalidOperations)
{
    // 无效对象操作
    db_object invalid_obj;

    EXPECT_FALSE(invalid_obj.open(db_access_mode::k_read));
    EXPECT_FALSE(invalid_obj.close());
    // EXPECT_THROW(invalid_obj.xn_filer(), std::exception);
}