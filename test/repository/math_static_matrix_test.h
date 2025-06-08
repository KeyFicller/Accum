#pragma once

#include "math_static_matrix.h"

#include "gtest/gtest.h"

using namespace PRJ_NAME;

// Test fixture template for different matrix sizes
template <typename T, unsigned N>
class MatrixTest : public testing::Test {
protected:
    using Vec = vec_impl_t<T, N>;
    using Mat = mat_impl_t<T, N>;
    
    void SetUp() override {
        // Initialize identity matrix
        identity = Mat::identity();
    }
    
    Mat identity;
};

// Additional tests for specific matrix operations
TEST(Matrix2x2Test, SpecificOperations) {
    using Vec = vec_impl_t<float, 2>;
    using Mat = mat_impl_t<float, 2>;
    
    Vec col1(1, 2);
    Vec col2(3, 4);
    Mat m(col1, col2);
    
    EXPECT_EQ(m[0], col1);
    EXPECT_EQ(m[1], col2);
    
    Mat transposed = m.transposed();
    EXPECT_EQ(transposed[0][0], 1);
    EXPECT_EQ(transposed[0][1], 3);
    EXPECT_EQ(transposed[1][0], 2);
    EXPECT_EQ(transposed[1][1], 4);
}

TEST(Matrix3x3Test, SpecificOperations) {
    using Vec = vec_impl_t<double, 3>;
    using Mat = mat_impl_t<double, 3>;
    
    Vec col1(1, 2, 3);
    Vec col2(4, 5, 6);
    Vec col3(7, 8, 9);
    Mat m(col1, col2, col3);
    
    EXPECT_EQ(m[0], col1);
    EXPECT_EQ(m[1], col2);
    EXPECT_EQ(m[2], col3);
    
    Mat transposed = m.transposed();
    EXPECT_EQ(transposed[0][0], 1);
    EXPECT_EQ(transposed[0][1], 4);
    EXPECT_EQ(transposed[0][2], 7);
    EXPECT_EQ(transposed[1][0], 2);
    EXPECT_EQ(transposed[1][1], 5);
    EXPECT_EQ(transposed[1][2], 8);
    EXPECT_EQ(transposed[2][0], 3);
    EXPECT_EQ(transposed[2][1], 6);
    EXPECT_EQ(transposed[2][2], 9);
}

TEST(Matrix4x4Test, SpecificOperations) {
    using Vec = vec_impl_t<int, 4>;
    using Mat = mat_impl_t<int, 4>;
    
    Vec col1(1, 2, 3, 4);
    Vec col2(5, 6, 7, 8);
    Vec col3(9, 10, 11, 12);
    Vec col4(13, 14, 15, 16);
    Mat m(col1, col2, col3, col4);
    
    EXPECT_EQ(m[0], col1);
    EXPECT_EQ(m[1], col2);
    EXPECT_EQ(m[2], col3);
    EXPECT_EQ(m[3], col4);
    
    Mat transposed = m.transposed();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(transposed[i][j], m[j][i]);
        }
    }
}

TEST(MatrixEdgeCases, IdentitySingleton) {
    // Should work even for n=1 (though not explicitly supported)
    using Mat = mat_impl_t<float, 1>;
    Mat m;
    m[0][0] = 5;
    
    Mat identity = Mat::identity();
    EXPECT_EQ(identity[0][0], 1);
    
    Mat transposed = m.transposed();
    EXPECT_EQ(transposed[0][0], 5);
}

TEST(MatrixEdgeCases, TransposeInPlace) {
    using Mat = mat_impl_t<float, 3>;
    Mat m;
    
    // Fill matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m[i][j] = i * 3 + j;
        }
    }
    
    // Transpose in-place
    m.transpose();
    
    // Verify transposed values
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(m[i][j], j * 3 + i);
        }
    }
}

TEST(MatrixToString, FormatVerification) {
    using Vec = vec_impl_t<float, 2>;
    using Mat = mat_impl_t<float, 2>;
    
    Vec col1(1.5f, 2.5f);
    Vec col2(3.5f, 4.5f);
    Mat m(col1, col2);
    
    std::string str = m.to_string();
    
    // Expected format: "{ {1.5, 2.5}, {3.5, 4.5} }"
    EXPECT_NE(str.find("{1.5, 2.5}"), std::string::npos);
    EXPECT_NE(str.find("{3.5, 4.5}"), std::string::npos);
    EXPECT_NE(str.find("}, "), std::string::npos);
}

TEST(MatrixEquality, ComparisonOperator) {
    using Mat = mat_impl_t<double, 2>;
    Mat m1 = Mat::identity();
    Mat m2 = Mat::identity();
    Mat m3;
    m3[0][0] = 2;
    
    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);
    
    // Modify one element
    m2[1][1] = 0.5;
    EXPECT_NE(m1, m2);
}