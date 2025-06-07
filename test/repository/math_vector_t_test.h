#pragma once

#include "math_vector_t.h"  // Include the header containing vec_impl_t

#include "gtest/gtest.h"

using namespace PRJ_NAME;

// Dimension-specific tests
TEST(Vector2DTest, ComponentConstructor) {
    vec_impl_t<int, 2> v(10, 20);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

TEST(Vector3DTest, ComponentConstructor) {
    vec_impl_t<float, 3> v(1.1f, 2.2f, 3.3f);
    EXPECT_FLOAT_EQ(v[0], 1.1f);
    EXPECT_FLOAT_EQ(v[1], 2.2f);
    EXPECT_FLOAT_EQ(v[2], 3.3f);
}

TEST(Vector4DTest, ComponentConstructor) {
    vec_impl_t<double, 4> v(0.1, 0.2, 0.3, 0.4);
    EXPECT_DOUBLE_EQ(v[0], 0.1);
    EXPECT_DOUBLE_EQ(v[1], 0.2);
    EXPECT_DOUBLE_EQ(v[2], 0.3);
    EXPECT_DOUBLE_EQ(v[3], 0.4);
}

TEST(Vector2DTest, ComponentShortcuts) {
    vec_impl_t<int, 2> v;
    v.x() = 10;
    v.y() = 20;
    
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v.x(), 10);
    EXPECT_EQ(v.y(), 20);
    
    v.r() = 100;
    v.g() = 200;
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(v.r(), 100);
    EXPECT_EQ(v.g(), 200);
}

TEST(Vector3DTest, ComponentShortcuts) {
    vec_impl_t<float, 3> v;
    v.x() = 1.0f;
    v.y() = 2.0f;
    v.z() = 3.0f;
    
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    
    v.r() = 0.1f;
    v.g() = 0.2f;
    v.b() = 0.3f;
    EXPECT_FLOAT_EQ(v[0], 0.1f);
    EXPECT_FLOAT_EQ(v[1], 0.2f);
    EXPECT_FLOAT_EQ(v[2], 0.3f);
}

TEST(Vector4DTest, ComponentShortcuts) {
    vec_impl_t<double, 4> v;
    v.x() = 0.1;
    v.y() = 0.2;
    v.z() = 0.3;
    v.w() = 0.4;
    
    EXPECT_DOUBLE_EQ(v[0], 0.1);
    EXPECT_DOUBLE_EQ(v[1], 0.2);
    EXPECT_DOUBLE_EQ(v[2], 0.3);
    EXPECT_DOUBLE_EQ(v[3], 0.4);
    
    v.r() = 1.0;
    v.g() = 2.0;
    v.b() = 3.0;
    v.a() = 4.0;
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(Vector3DTest, FromVector2D) {
    vec_impl_t<int, 2> v2(10, 20);
    vec_impl_t<int, 3> v3(v2, 30);
    
    EXPECT_EQ(v3[0], 10);
    EXPECT_EQ(v3[1], 20);
    EXPECT_EQ(v3[2], 30);
}

TEST(Vector4DTest, FromVector3D) {
    vec_impl_t<float, 3> v3(1.1f, 2.2f, 3.3f);
    vec_impl_t<float, 4> v4(v3, 4.4f);
    
    EXPECT_FLOAT_EQ(v4[0], 1.1f);
    EXPECT_FLOAT_EQ(v4[1], 2.2f);
    EXPECT_FLOAT_EQ(v4[2], 3.3f);
    EXPECT_FLOAT_EQ(v4[3], 4.4f);
}

TEST(Vector3DTest, SwizzleXY) {
    vec_impl_t<int, 3> v(10, 20, 30);
    auto xy = v.xy();
    
    EXPECT_EQ(xy[0], 10);
    EXPECT_EQ(xy[1], 20);
    static_assert(std::is_same<decltype(xy), vec_impl_t<int, 2>>::value, 
                  "Should return vec_impl_t<int, 2>");
}

TEST(Vector4DTest, SwizzleXYZ) {
    vec_impl_t<double, 4> v(0.1, 0.2, 0.3, 0.4);
    auto xyz = v.xyz();
    
    EXPECT_DOUBLE_EQ(xyz[0], 0.1);
    EXPECT_DOUBLE_EQ(xyz[1], 0.2);
    EXPECT_DOUBLE_EQ(xyz[2], 0.3);
    static_assert(std::is_same<decltype(xyz), vec_impl_t<double, 3>>::value,
                  "Should return vec_impl_t<double, 3>");
}

TEST(VectorTest, ToString) {
    vec_impl_t<int, 2> v2{10, 20};
    EXPECT_EQ(v2.to_string(), "{10, 20}");
    
    vec_impl_t<float, 3> v3{1.1f, 2.2f, 3.3f};
    std::string result = v3.to_string();
    EXPECT_TRUE(result.find("1.1") != std::string::npos);
    EXPECT_TRUE(result.find("2.2") != std::string::npos);
    EXPECT_TRUE(result.find("3.3") != std::string::npos);
    
    vec_impl_t<double, 4> v4{0.1, 0.2, 0.3, 0.4};
    EXPECT_EQ(v4.to_string(), "{0.1, 0.2, 0.3, 0.4}");
}

TEST(VectorTest, EqualityOperator) {
    vec_impl_t<int, 3> v1{1, 2, 3};
    vec_impl_t<int, 3> v2{1, 2, 3};
    vec_impl_t<int, 3> v3{1, 2, 4};
    
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    
    vec_impl_t<float, 2> f1{1.0f, 2.0f};
    vec_impl_t<float, 2> f2{1.0f, 2.0f};
    vec_impl_t<float, 2> f3{1.1f, 2.0f};
    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
}

TEST(VectorEdgeCases, ZeroSizeVector) {
    // Shouldn't compile - verify compilation failure in separate test
    // vec_impl_t<int, 0> v;
}

TEST(VectorEdgeCases, LargeVector) {
    vec_impl_t<int, 100> v;
    v[99] = 100;
    EXPECT_EQ(v[99], 100);
    for (unsigned i = 0; i < 99; ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorComponentShortcuts, SFINAECheck) {
    // 2D vector shouldn't have z() or w()
    vec_impl_t<int, 2> v2;
    v2.x() = 1;  // Should compile
    v2.y() = 2;  // Should compile
    // v2.z() = 3; // Should not compile
    
    // 3D vector shouldn't have w()
    vec_impl_t<int, 3> v3;
    v3.z() = 3;  // Should compile
    // v3.w() = 4; // Should not compile
    
    // 4D vector should have all
    vec_impl_t<int, 4> v4;
    v4.w() = 4;  // Should compile
}

TEST(VectorConversion, FromLowerDimension) {
    vec_impl_t<int, 2> v2(10, 20);
    vec_impl_t<int, 3> v3(v2, 30);
    EXPECT_EQ(v3[0], 10);
    EXPECT_EQ(v3[1], 20);
    EXPECT_EQ(v3[2], 30);
    
    vec_impl_t<float, 3> v3f(1.1f, 2.2f, 3.3f);
    vec_impl_t<float, 4> v4f(v3f, 4.4f);
    EXPECT_FLOAT_EQ(v4f[0], 1.1f);
    EXPECT_FLOAT_EQ(v4f[1], 2.2f);
    EXPECT_FLOAT_EQ(v4f[2], 3.3f);
    EXPECT_FLOAT_EQ(v4f[3], 4.4f);
}
