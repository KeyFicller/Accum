#pragma once

#include "basic_filer.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

class FilerTest : public testing::Test
{
  protected:
    filer f;

    void SetUp() override
    {
        f.clear(); // Ensure clean state before each test
    }
};

TEST_F(FilerTest, WriteReadPODTypes)
{
    // Test basic POD types
    int out_int = 42;
    double out_double = 3.14159;
    char out_char = 'A';

    f << out_int << out_double << out_char;
    f.seek(0); // Rewind to beginning

    int in_int;
    double in_double;
    char in_char;

    f >> in_int >> in_double >> in_char;

    EXPECT_EQ(in_int, 42);
    EXPECT_DOUBLE_EQ(in_double, 3.14159);
    EXPECT_EQ(in_char, 'A');
}

TEST_F(FilerTest, StringSerialization)
{
    std::string out_str = "Hello World!";
    f << out_str;
    f.seek(0);

    std::string in_str;
    f >> in_str;

    EXPECT_EQ(in_str, "Hello World!");
}

TEST_F(FilerTest, PositionAndSeek)
{
    // Write some data
    int value = 100;
    f << value;

    // Verify position tracking
    EXPECT_EQ(f.position(), sizeof(int));

    // Seek operations
    EXPECT_TRUE(f.seek(0));
    EXPECT_EQ(f.position(), 0);

    EXPECT_TRUE(f.seek(sizeof(int)));
    EXPECT_EQ(f.position(), sizeof(int));

    // Invalid seek positions
    EXPECT_FALSE(f.seek(-1));
    EXPECT_FALSE(f.seek(1000));
}

TEST_F(FilerTest, ReadWriteBytes)
{
    const char buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    const int size = sizeof(buffer);

    // Write raw bytes
    f.write_bytes(buffer, size);
    EXPECT_EQ(f.position(), size);

    // Read back
    char in_buffer[size] = {};
    f.seek(0);
    f.read_bytes(in_buffer, size);

    for (int i = 0; i < size; i++) {
        EXPECT_EQ(in_buffer[i], buffer[i]);
    }
}

TEST_F(FilerTest, FlushOperations)
{
    // Create two filers
    filer source;
    filer dest;

    // Write to source
    int value = 12345;
    source << value;

    // Flush from source to dest
    source.seek(0);
    source.flush_out(dest, sizeof(value));

    // Verify dest received data
    dest.seek(0);
    int result;
    dest >> result;

    EXPECT_EQ(result, 12345);
}

TEST_F(FilerTest, ClearOperation)
{
    // Write some data
    f << 42 << 3.14;
    EXPECT_GT(f.position(), 0);

    // Clear and verify
    f.clear();
    EXPECT_EQ(f.position(), 0);

    // Should be empty
    f.seek(0);
    int value;
    EXPECT_THROW(f >> value, std::exception);
}
struct Point
{
    float x, y;
};
// Register serializer for custom type
template<>
struct filer_serializer<Point>
{
    static void dump(filer& f, const Point& p) { f << p.x << p.y; }

    static void load(filer& f, Point& p) { f >> p.x >> p.y; }
};

TEST_F(FilerTest, ComplexDataTypes)
{
    Point out_point{ 1.5f, 2.5f };
    f << out_point;

    f.seek(0);
    Point in_point;
    f >> in_point;

    EXPECT_FLOAT_EQ(in_point.x, 1.5f);
    EXPECT_FLOAT_EQ(in_point.y, 2.5f);
}

TEST_F(FilerTest, BoundaryConditions)
{
    // Test writing at boundaries
    char large_buffer[1024];
    memset(large_buffer, 0xAA, sizeof(large_buffer));

    f.write_bytes(large_buffer, sizeof(large_buffer));
    EXPECT_EQ(f.position(), sizeof(large_buffer));

    // Test reading partial data
    f.seek(500);
    char partial[100];
    f.read_bytes(partial, sizeof(partial));
    EXPECT_EQ(partial[0], (char)0xAA);
}

TEST_F(FilerTest, MixedOperations)
{
    // Mixed POD and string operations
    f << 10 << "Test" << 20.5;

    f.seek(0);
    int i1, i2;
    std::string s;
    double d;

    f >> i1 >> s >> d;

    EXPECT_EQ(i1, 10);
    EXPECT_EQ(s, "Test");
    EXPECT_DOUBLE_EQ(d, 20.5);
}

TEST_F(FilerTest, ErrorHandling)
{
    // Test reading beyond available data
    f << 42;
    f.seek(0);
    int value;
    f >> value; // First read should succeed
    EXPECT_EQ(value, 42);

    // Second read should fail
    EXPECT_THROW(f >> value, std::exception);

    // Test reading invalid size
    char buffer[10];
    EXPECT_THROW(f.read_bytes(buffer, 20), std::exception);
}

TEST_F(FilerTest, MultipleFlushOperations)
{
    filer source;
    filer dest;

    source << "Hello" << "World";
    int end = source.position();
    // Flush in chunks
    source.seek(0);
    source.flush_out(dest, 3); // Partial flush

    EXPECT_EQ(dest.position(), 3);
    EXPECT_EQ(source.position(), 3);

    source.flush_out(dest, end - 3); // Remaining

    // Verify complete data
    dest.seek(0);
    std::string s1, s2;
    dest >> s1 >> s2;

    EXPECT_EQ(s1, "Hello");
    EXPECT_EQ(s2, "World");
}

TEST_F(FilerTest, PositionAfterOperations)
{
    EXPECT_EQ(f.position(), 0);

    f << 1 << 2.0 << "Three";
    int pos_after_write = f.position();

    f.seek(0);
    EXPECT_EQ(f.position(), 0);

    int i;
    double d;
    std::string s;
    f >> i >> d >> s;

    EXPECT_EQ(f.position(), pos_after_write);
}