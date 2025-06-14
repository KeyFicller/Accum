#pragma once

#include "basic_printer.h"

#include "gtest/gtest.h"

// Mock prompt function for testing
namespace PRJ_NAME {
std::string
prompt(prompt_id id)
{
    switch (id) {
        case prompt_id::k_undefined_print_behavior:
            return "UNDEFINED";
        default:
            return "MOCK_PROMPT";
    }
}
}

TEST(PrinterTest, CstyleFormatPrint_BasicTypes)
{
    // Integer formatting
    EXPECT_EQ(PRJ_NAME::cstyle_format_print("%d", 42), "42");
    EXPECT_EQ(PRJ_NAME::cstyle_format_print("%04d", 7), "0007");

    // Floating point
    EXPECT_EQ(PRJ_NAME::cstyle_format_print("%.1f", 3.14159), "3.1");

    // String formatting
    EXPECT_EQ(PRJ_NAME::cstyle_format_print("Hello %s", "World"), "Hello World");

    // Multiple arguments
    EXPECT_EQ(PRJ_NAME::cstyle_format_print("%d %s %.2f", 10, "apples", 2.5), "10 apples 2.50");
}

TEST(PrinterTest, CstyleFormatPrint_BufferLimits)
{
    // Test boundary conditions
    std::string long_str(PRINTER_BUFFER_SIZE * 2, 'A');
    std::string result = PRJ_NAME::cstyle_format_print("%s", long_str.c_str());

    // Should truncate to buffer size
    EXPECT_EQ(result.size(), PRINTER_BUFFER_SIZE - 1);
    EXPECT_EQ(result.substr(0, 10), "AAAAAAAAAA");
}

TEST(PrinterTest, Print_StringTypes)
{
    // std::string
    EXPECT_EQ(PRJ_NAME::print(std::string("test")), "test");

    // Char array
    char char_array[] = "char_array";
    EXPECT_EQ(PRJ_NAME::print(char_array), "char_array");

    // String literal
    EXPECT_EQ(PRJ_NAME::print("literal"), "literal");

    // Const char*
    const char* cstr = "cstring";
    EXPECT_EQ(PRJ_NAME::print(cstr), "cstring");
}

TEST(PrinterTest, Print_ArithmeticTypes)
{
    // Integers
    EXPECT_EQ(PRJ_NAME::print(42), "42");
    EXPECT_EQ(PRJ_NAME::print(-10), "-10");

    // Floating point
    EXPECT_NE(PRJ_NAME::print(3.14159).find("3.14159"), std::string::npos);
    EXPECT_NE(PRJ_NAME::print(2.5f).find("2.5"), std::string::npos);

    // Boolean
    EXPECT_EQ(PRJ_NAME::print(true), "1"); // std::to_string converts true to 1
    EXPECT_EQ(PRJ_NAME::print(false), "0");
}

TEST(PrinterTest, Print_Pointers)
{
    int value = 10;
    int* ptr = &value;

    std::string result = PRJ_NAME::print(ptr);

    // Should contain hex prefix and address
    EXPECT_TRUE(result.find("0x") == 0);
    EXPECT_GT(result.size(), 4);

    // Null pointer
    EXPECT_EQ(PRJ_NAME::print(nullptr), "0x0");
}

TEST(PrinterTest, Print_CustomTypeWithToString)
{
    // Custom type with to_string method
    struct CustomType
    {
        std::string to_string() const { return "CUSTOM_123"; }
    };

    CustomType obj;
    EXPECT_EQ(PRJ_NAME::print(obj), "CUSTOM_123");
}

TEST(PrinterTest, Print_UndefinedBehavior)
{
    // Type without any print specialization
    struct Unprintable
    {};

    Unprintable obj;
    EXPECT_EQ(PRJ_NAME::print(obj), "Undefined print behavior");
}

TEST(PrinterTest, Print_PromptIdSpecialization)
{
    // Test prompt_id specialization
    PRJ_NAME::prompt_id pid = PRJ_NAME::prompt_id::k_undefined_print_behavior;
    EXPECT_EQ(PRJ_NAME::print(pid), "Undefined print behavior");

    // Test with unknown prompt id
    // pid = static_cast<PRJ_NAME::prompt_id>(100);
    // EXPECT_EQ(PRJ_NAME::print(pid), "MOCK_PROMPT");
}

TEST(PrinterTest, Print_EdgeCases)
{
    // Empty string
    EXPECT_EQ(PRJ_NAME::print(""), "");

    // Max integer
    EXPECT_EQ(PRJ_NAME::print(INT_MAX), std::to_string(INT_MAX));

    // Min integer
    EXPECT_EQ(PRJ_NAME::print(INT_MIN), std::to_string(INT_MIN));

    // Double limits
    // std::string dbl_max = PRJ_NAME::print(DBL_MAX);
    // EXPECT_TRUE(dbl_max.find("e+") != std::string::npos);
}

TEST(PrinterTest, Print_CharTypes)
{
    // Single char
    EXPECT_EQ(PRJ_NAME::print('A'), "65"); // std::to_string converts char to int

    // Signed char
    signed char sc = -128;
    EXPECT_EQ(PRJ_NAME::print(sc), "-128");

    // Unsigned char
    unsigned char uc = 255;
    EXPECT_EQ(PRJ_NAME::print(uc), "255");
}

TEST(PrinterTest, Print_StringEdgeCases)
{
    // Long string
    std::string long_str(1000, 'X');
    EXPECT_EQ(PRJ_NAME::print(long_str), long_str);

    // String with null characters
    std::string null_str("a\0b\0c", 5);
    EXPECT_EQ(PRJ_NAME::print(null_str).size(), 5);
}

TEST(PrinterTest, Print_ZeroSizeArray)
{
    // Zero-sized array
    const char empty_array[1] = { 0 };
    EXPECT_EQ(PRJ_NAME::print(empty_array), "");
}