#pragma once

#include "basic_bitflags.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

// Test fixture for bit_flags
class BitFlagsTest : public testing::Test {
protected:
    using Flags = bit_flags<int>;
    
    void SetUp() override {
        // Common setup if needed
    }
};

TEST_F(BitFlagsTest, Initialization) {
    Flags f1(0);
    EXPECT_EQ(f1.bits(), 0);
    
    Flags f2(0b1010);
    EXPECT_EQ(f2.bits(), 0b1010);
}

TEST_F(BitFlagsTest, HasBit) {
    Flags f(0b1101);
    
    EXPECT_TRUE(f.has_bit(0b0001));
    EXPECT_TRUE(f.has_bit(0b0100));
    EXPECT_TRUE(f.has_bit(0b1000));
    EXPECT_FALSE(f.has_bit(0b0010));
    EXPECT_FALSE(f.has_bit(0b10000));
}

TEST_F(BitFlagsTest, SetBit) {
    Flags f(0b1001);
    
    // Set existing bit (should remain set)
    f.set_bit(0b1000);
    EXPECT_EQ(f.bits(), 0b1001);
    
    // Set new bit
    f.set_bit(0b0100);
    EXPECT_EQ(f.bits(), 0b1101);
    
    // Clear bit
    f.set_bit(0b0001, false);
    EXPECT_EQ(f.bits(), 0b1100);
    
    // Set multiple bits
    f.set_bit(0b0011);
    EXPECT_EQ(f.bits(), 0b1111);
}

TEST_F(BitFlagsTest, Clear) {
    Flags f(0b1111);
    f.clear();
    EXPECT_EQ(f.bits(), 0);
    
    // Should remain cleared
    f.set_bit(0b1000);
    f.clear();
    EXPECT_EQ(f.bits(), 0);
}

TEST_F(BitFlagsTest, ConversionOperator) {
    Flags f(0b10101);
    int value = f;
    EXPECT_EQ(value, 0b10101);
    
    // Test in expression
    int sum = f + 0b1010;
    EXPECT_EQ(sum, 0b10101 + 0b1010);
}

TEST_F(BitFlagsTest, EqualityOperator) {
    Flags f1(0b1100);
    Flags f2(0b1100);
    Flags f3(0b0011);
    
    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
    
    f2.set_bit(0b0001);
    EXPECT_FALSE(f1 == f2);
    
    // Self-equality
    EXPECT_TRUE(f1 == f1);
}

TEST_F(BitFlagsTest, Chaining) {
    Flags f(0);
    
    // Method chaining
    f.set_bit(0b0001).set_bit(0b1000).set_bit(0b0100, false);
    EXPECT_EQ(f.bits(), 0b1001);
    
    f.clear().set_bit(0b0100);
    EXPECT_EQ(f.bits(), 0b0100);
}

TEST_F(BitFlagsTest, EdgeCases) {
    // Zero value
    Flags f0(0);
    EXPECT_FALSE(f0.has_bit(0));
    EXPECT_FALSE(f0.has_bit(1));
    
    // All bits set
    const int all_bits = ~0;
    Flags f_all(all_bits);
    EXPECT_TRUE(f_all.has_bit(1));
    EXPECT_TRUE(f_all.has_bit(0b10000000));
    EXPECT_TRUE(f_all.has_bit(all_bits));
    
    // Single bit manipulation
    Flags f(0);
    f.set_bit(0b10000000);
    EXPECT_TRUE(f.has_bit(0b10000000));
    EXPECT_FALSE(f.has_bit(0b01000000));
    
    f.set_bit(0b10000000, false);
    EXPECT_FALSE(f.has_bit(0b10000000));
}

// Test with different underlying types
TEST(BitFlagsTypeTest, UnsignedCharType) {
    bit_flags<unsigned char> f(0b10101010);
    EXPECT_EQ(f.bits(), 0xAA);
    
    f.set_bit(0x80);
    EXPECT_EQ(f.bits(), 0xAA);  // Already set
    
    f.set_bit(0x01);
    EXPECT_EQ(f.bits(), 0xAB);
}

TEST(BitFlagsTypeTest, LongType) {
    long large_bit = 1L << 40;
    bit_flags<long> f(0);
    
    f.set_bit(large_bit);
    EXPECT_TRUE(f.has_bit(large_bit));
    EXPECT_FALSE(f.has_bit(1L << 41));
    
    f.set_bit(large_bit, false);
    EXPECT_FALSE(f.has_bit(large_bit));
}