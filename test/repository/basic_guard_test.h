#pragma once

#include "basic_guard.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

// Test fixture for guard class
class GuardTest : public testing::Test {
protected:
    int enterCount = 0;
    int leaveCount = 0;
    
    void SetUp() override {
        enterCount = 0;
        leaveCount = 0;
    }
    
    callback_t<void> makeEnterFunc() { 
        return [this] { enterCount++; }; 
    }
    
    callback_t<void> makeLeaveFunc() { 
        return [this] { leaveCount++; }; 
    }
};

TEST_F(GuardTest, CallsBothFunctions) {
    {
        guard g(makeEnterFunc(), makeLeaveFunc());
        EXPECT_EQ(enterCount, 1);
        EXPECT_EQ(leaveCount, 0);
    }
    EXPECT_EQ(enterCount, 1);
    EXPECT_EQ(leaveCount, 1);
}

TEST_F(GuardTest, CallsOnlyLeaveFunction) {
    {
        guard g(makeLeaveFunc());
        EXPECT_EQ(enterCount, 0);
        EXPECT_EQ(leaveCount, 0);
    }
    EXPECT_EQ(enterCount, 0);
    EXPECT_EQ(leaveCount, 1);
}

TEST_F(GuardTest, DismissPreventsLeaveCall) {
    {
        guard g(makeEnterFunc(), makeLeaveFunc());
        g.dismiss();
        EXPECT_EQ(enterCount, 1);
        EXPECT_EQ(leaveCount, 0);
    }
    EXPECT_EQ(enterCount, 1);  // Leave should not be called
    EXPECT_EQ(leaveCount, 0);
}

// Test fixture for value_reverter
class ValueReverterTest : public testing::Test {
protected:
    int testValue = 0;
};

TEST_F(ValueReverterTest, RevertsOriginalValue) {
    testValue = 42;
    {
        value_reverter<int> vr(testValue);
        testValue = 100;
        EXPECT_EQ(testValue, 100);
    }
    EXPECT_EQ(testValue, 42);  // Should revert to original
}

TEST_F(ValueReverterTest, SetsInitialValueAndReverts) {
    testValue = 42;
    {
        value_reverter<int> vr(testValue, 99);
        EXPECT_EQ(testValue, 99);  // Initial value set
        testValue = 100;
    }
    EXPECT_EQ(testValue, 42);  // Reverts to original, not initial
}

TEST_F(ValueReverterTest, DismissPreventsRevert) {
    testValue = 42;
    {
        value_reverter<int> vr(testValue);
        testValue = 100;
        vr.dismiss();  // Should prevent revert
    }
    EXPECT_EQ(testValue, 100);  // Value not reverted
}

// Test macro functionality
TEST(GuardMacroTest, CreatesGuardWithEnterLeave) {
    int counter = 0;
    {
        GUARD([&]{ counter += 1; },  // Enter function
              [&]{ counter += 2; }); // Leave function
        EXPECT_EQ(counter, 1);
    }
    EXPECT_EQ(counter, 3);  // 1 (enter) + 2 (leave)
}

TEST(GuardMacroTest, CreatesGuardWithLeaveOnly) {
    int counter = 0;
    {
        GUARD([&]{ counter = 5; });  // Leave only
        EXPECT_EQ(counter, 0);
    }
    EXPECT_EQ(counter, 5);
}

TEST(ValueReverterMacroTest, CreatesValueReverter) {
    int value = 10;
    {
        VALUE_REVERTER(value);
        value = 20;
        EXPECT_EQ(value, 20);
    }
    EXPECT_EQ(value, 10);
}

TEST(ValueReverterMacroTest, CreatesWithInitialValue) {
    int value = 10;
    {
        VALUE_REVERTER(value, 30);
        EXPECT_EQ(value, 30);  // Initial value set
        value = 20;
    }
    EXPECT_EQ(value, 10);  // Reverts to original
}