#pragma once

#include "server_load_proc.h"
#include "server_save_proc.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

#define TEST_FILE "./save_load_test.txt"

class save_load_test : public testing::Test
{
  protected:
    void SetUp() override {}
};

TEST_F(save_load_test, GeneralTest)
{
    int save_i = 1;
    float save_f = 2.0;
    std::string save_str = "Hello";
    std::vector<int> save_veci = { 2, 4, 5 };
    std::map<std::string, int> save_map = { { "a", 2 }, { "b", 4 } };
    {

        save_proc proc(TEST_FILE);
        proc.begin();
        SAVE_PROC(proc, "Int", save_i);
        SAVE_PROC(proc, "Float", save_f);
        SAVE_PROC(proc, "String", save_str);
        SAVE_PROC(proc, "Vector", save_veci);
        SAVE_PROC(proc, "Map", save_map);
        proc.end();
    }

    int load_i;
    float load_f;
    std::string load_str;
    std::vector<int> load_veci;
    std::map<std::string, int> load_map;
    {

        load_proc proc(TEST_FILE);
        proc.begin();
        LOAD_PROC(proc, "Int", load_i);
        LOAD_PROC(proc, "Float", load_f);
        LOAD_PROC(proc, "String", load_str);
        LOAD_PROC(proc, "Vector", load_veci);
        LOAD_PROC(proc, "Map", load_map);
        proc.end();
    }

    EXPECT_EQ(save_i, load_i);
    EXPECT_EQ(save_f, load_f);
    EXPECT_EQ(save_str, load_str);
    EXPECT_EQ(save_veci, load_veci);
    EXPECT_EQ(save_map, load_map);
}