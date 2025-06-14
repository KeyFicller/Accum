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
        proc << save_proc_flow::k_in_key << "Int" << save_proc_flow::k_in_value << save_i;
        proc << save_proc_flow::k_in_key << "Float" << save_proc_flow::k_in_value << save_f;
        proc << save_proc_flow::k_in_key << "String" << save_proc_flow::k_in_value << save_str;
        proc << save_proc_flow::k_in_key << "Vector" << save_proc_flow::k_in_value << save_veci;
        proc << save_proc_flow::k_in_key << "Map" << save_proc_flow::k_in_value << save_map;
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
        proc >> shd_out_key >> "Int" >> shd_out_value >> load_i;
        proc >> shd_out_key >> "Float" >> shd_out_value >> load_f;
        proc >> shd_out_key >> "String" >> shd_out_value >> load_str;
        proc >> shd_out_key >> "Vector" >> shd_out_value >> load_veci;
        proc >> shd_out_key >> "Map" >> shd_out_value >> load_map;
        proc.end();
    }

    EXPECT_EQ(save_i, load_i);
    EXPECT_EQ(save_f, load_f);
    EXPECT_EQ(save_str, load_str);
    EXPECT_EQ(save_veci, load_veci);
    EXPECT_EQ(save_map, load_map);
}