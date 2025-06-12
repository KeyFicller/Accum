#pragma once

#include "db_object_id.h"
#include "db_database.h"
#include "db_object.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

class DBObjectIDTest : public testing::Test {
protected:
    void SetUp() override {
        db = new database();
        obj = new db_object();
        id = db_object_id(123); // 有效句柄
    }
    
    void TearDown() override {
        if (!obj->id().is_valid())
            delete obj;
        delete db;
    }
    
    database* db;
    db_object* obj;
    db_object_id id;
};

TEST_F(DBObjectIDTest, DefaultConstructor) {
    db_object_id null_id;
    EXPECT_FALSE(null_id.is_valid());
    EXPECT_FALSE(static_cast<bool>(null_id));
    EXPECT_EQ(null_id, db_object_id::k_null);
}

TEST_F(DBObjectIDTest, HandleConstructor) {
    EXPECT_FALSE(id.is_valid());
    EXPECT_FALSE(static_cast<bool>(id));
    EXPECT_EQ(id.handle(), 123);
}

TEST_F(DBObjectIDTest, CopyConstructor) {
    db_object_id copy(id);
    EXPECT_FALSE(copy.is_valid());
    EXPECT_EQ(copy.handle(), 123);
    EXPECT_EQ(id, copy);
}

TEST_F(DBObjectIDTest, ValidityChecks) {
    // 无效ID
    db_object_id invalid_id(999);
    EXPECT_FALSE(invalid_id.is_valid());
    
    // 空ID
    EXPECT_FALSE(db_object_id::k_null.is_valid());
}

TEST_F(DBObjectIDTest, EqualityOperator) {
    db_object_id same_id(123);
    db_object_id different_id(456);
    
    EXPECT_EQ(id, same_id);
    EXPECT_NE(id, different_id);
    EXPECT_NE(id, db_object_id::k_null);
}

TEST_F(DBObjectIDTest, OpenObject) {
    // 需要在database中添加对象才能打开
    db_object_id obj_id;
    db->add_object(obj, obj_id);
    
    // 测试打开对象
    db_object* opened = obj_id.open<db_object>(db_access_mode::k_read);
    EXPECT_NE(opened, nullptr);
    EXPECT_EQ(opened->id(), obj_id);
}