#pragma once

#include "gtest/gtest.h"
#include "basic_prefab.h"

using namespace PRJ_NAME;

// Mock class for testing
class TestComponent {
public:
    TestComponent(int a, double b, const std::string& c) 
        : int_val(a), double_val(b), str_val(c) {}
    
    int get_int() const { return int_val; }
    double get_double() const { return double_val; }
    std::string get_string() const { return str_val; }

    void set_int(int v) { int_val = v; }

private:
    int int_val;
    double double_val;
    std::string str_val;
};

// Test fixture for prefab
class PrefabTest : public testing::Test {
protected:
    void SetUp() override {
        // Create prefab instances with different parameters
        prefab1 = prefab<TestComponent>::create(10, 3.14, "test");
        prefab2 = prefab<TestComponent>::create(20, 6.28, "hello");
    }
    
    prefab<TestComponent> prefab1;
    prefab<TestComponent> prefab2;
};

TEST_F(PrefabTest, CreationAndAccess) {
    // Verify initial values
    EXPECT_EQ(prefab1->get_int(), 10);
    EXPECT_DOUBLE_EQ(prefab1->get_double(), 3.14);
    EXPECT_EQ(prefab1->get_string(), "test");
    
    EXPECT_EQ(prefab2->get_int(), 20);
    EXPECT_DOUBLE_EQ(prefab2->get_double(), 6.28);
    EXPECT_EQ(prefab2->get_string(), "hello");
}

TEST_F(PrefabTest, CopySemantics) {
    // Copy constructor
    prefab<TestComponent> copy1(prefab1);
    EXPECT_EQ(copy1->get_int(), 10);
    
    // Copy assignment
    prefab<TestComponent> copy2 = prefab2;
    EXPECT_EQ(copy2->get_string(), "hello");
    
    // Verify they share the same underlying object
    prefab1->set_int(100);
    EXPECT_EQ(copy1->get_int(), 100);
    
    // Original should remain unchanged
    EXPECT_EQ(prefab2->get_int(), 20);
}

TEST_F(PrefabTest, SharedOwnership) {
    auto shared1 = prefab1.self();
    auto shared2 = prefab2.self();
    
    // Verify reference counts
    EXPECT_EQ(shared1.use_count(), 2);  // prefab1 + shared1 reference
    EXPECT_EQ(shared2.use_count(), 2);  // prefab2 + shared2 reference
    
    {
        prefab<TestComponent> copy = prefab1;
        EXPECT_EQ(shared1.use_count(), 3);  // prefab1 + copy + shared1
    }
    
    // Should be back to 2 after copy goes out of scope
    EXPECT_EQ(shared1.use_count(), 2);
}

TEST_F(PrefabTest, SelfAccess) {
    auto self_ptr = prefab1.self();
    
    // Verify self pointer is valid
    EXPECT_NE(self_ptr, nullptr);
    EXPECT_EQ(self_ptr->get_int(), 10);
    
    // Modify through self pointer
    self_ptr->set_int(50);
    EXPECT_EQ(prefab1->get_int(), 50);
}

TEST_F(PrefabTest, DifferentComponentTypes) {
    // Test with different component type
    struct SimpleComponent {
        SimpleComponent(int v) : value(v) {}
        int value;
    };
    
    prefab<SimpleComponent> simple = prefab<SimpleComponent>::create(42);
    EXPECT_EQ(simple->value, 42);
    
    auto copy = simple;
    copy->value = 100;
    EXPECT_EQ(simple->value, 100);
}

TEST_F(PrefabTest, CreateAfterDestruction) {
    prefab<TestComponent> prefab_ins = prefab<TestComponent>::create(1, 2.0, "test");
    auto self = prefab_ins.self();
    
    // Destroy prefab wrapper
    prefab_ins = prefab<TestComponent>::create(2, 3.0, "test");
    
    // Underlying object should still exist
    EXPECT_EQ(self.use_count(), 1);
    EXPECT_EQ(self->get_int(), 1);
}

TEST_F(PrefabTest, AssignmentFromSelf) {
    prefab<TestComponent> copy = prefab1;
    prefab1 = copy;  // Self-assignment
    
    // Should still be valid
    EXPECT_EQ(prefab1->get_int(), 10);
    EXPECT_EQ(prefab1.self().use_count(), 2);  // prefab1 + copy + self reference
}