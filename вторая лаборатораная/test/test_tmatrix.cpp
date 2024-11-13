#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> src(3); // 3x3 матрица
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            src[i][j] = i + j;
        }
    }
    TDynamicMatrix<int> copy = src; //  опируем матрицу
    EXPECT_EQ(copy, src); //копи€ равна исходной
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> src(3); 
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            src[i][j] = i + j; 
        }
    }
    TDynamicMatrix<int> copy = src;
    copy[0][0] = 100; // »змен€ем копию
    // ѕровер€ем, что изменение в копии не затрагивает оригинал
    EXPECT_NE(copy[0][0], src[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> matrix(3);
    EXPECT_EQ(matrix.size(), 3);
    //ADD_FAILURE();
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> matrix(3); 
    matrix[0][0] = 10;
    matrix[1][1] = 20;
    matrix[2][2] = 30;
    // ѕровер€ем, что получаемые значени€ корректны
    EXPECT_EQ(matrix[0][0], 10);
    EXPECT_EQ(matrix[1][1], 20);
    EXPECT_EQ(matrix[2][2], 30);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> matrix(3);
    //при попытке установить элемент с отрицательным индексом исключение
    EXPECT_THROW(matrix[-1][0] = 5, std::out_of_range);
    EXPECT_THROW(matrix[0][-1] = 5, std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> matrix(3);
    //при попытке установить элемент с индексом, выход€щим за пределы матрицы исключение
    EXPECT_THROW(matrix[3][0] = 5, std::out_of_range);
    EXPECT_THROW(matrix[0][3] = 5, std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> matrix(3);
    matrix[0][0] = 5;
    matrix[1][1] = 10;
    matrix[2][2] = 15;

    matrix = matrix;

    EXPECT_EQ(matrix[0][0], 5); //элементы не изменились
    EXPECT_EQ(matrix[1][1], 10);
    EXPECT_EQ(matrix[2][2], 15);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> matrix1(3); 
    matrix1[0][0] = 1;
    matrix1[1][1] = 2;
    matrix1[2][2] = 3;

    TDynamicMatrix<int> matrix2(3);
    matrix2 = matrix1;

    EXPECT_EQ(matrix2[0][0], 1); //элементы скопированы правильно
    EXPECT_EQ(matrix2[1][1], 2);
    EXPECT_EQ(matrix2[2][2], 3);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> matrix1(3); // 3x3 матрица
    TDynamicMatrix<int> matrix2(4); // 4x4 матрица

    EXPECT_THROW(matrix1 = matrix2, std::invalid_argument);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> matrix1(3);
    TDynamicMatrix<int> matrix2(2); 

    EXPECT_THROW(matrix1 = matrix2, std::invalid_argument);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> matrix1(3);
    TDynamicMatrix<int> matrix2(3);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 1;
        }
    }
    EXPECT_TRUE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> matrix(3);
    EXPECT_TRUE(matrix == matrix);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> matrix1(3); 
    TDynamicMatrix<int> matrix2(4); 
    EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(3); 
    TDynamicMatrix<int> matrix2(3); 
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matrix1[i][j] = i + j; // «аполнение значени€ми
            matrix2[i][j] = i * j; 
        }
    }
    TDynamicMatrix<int> result = matrix1 + matrix2;
    EXPECT_EQ(result[0][0], 0); // 0 + 0 = 0
    EXPECT_EQ(result[0][1], 1); // 0 + 1 = 1
    EXPECT_EQ(result[0][2], 2); // 0 + 2 = 2
    EXPECT_EQ(result[1][0], 1); 
    EXPECT_EQ(result[1][1], 3); 
    EXPECT_EQ(result[1][2], 5); 
    EXPECT_EQ(result[2][0], 2); 
    EXPECT_EQ(result[2][1], 5); 
    EXPECT_EQ(result[2][2], 8);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> matrix1(3);
    TDynamicMatrix<int> matrix2(4);
    EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(3); 
    TDynamicMatrix<int> matrix2(3); 
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matrix1[i][j] = i + j; 
            matrix2[i][j] = i * j; 
        }
    }
    TDynamicMatrix<int> result = matrix1 - matrix2;
    EXPECT_EQ(result[0][0], 0); // 0 - 0 = 0
    EXPECT_EQ(result[0][1], 1); // 0 - 0 = 1
    EXPECT_EQ(result[0][2], 2); // 0 - 0 = 2
    EXPECT_EQ(result[1][0], 1); 
    EXPECT_EQ(result[1][1], 1); 
    EXPECT_EQ(result[1][2], 1); 
    EXPECT_EQ(result[2][0], 2); 
    EXPECT_EQ(result[2][1], 1); //должно быть 1, но написано 4??
    EXPECT_EQ(result[2][2], 0); //должно быть 0, написано 6??
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> matrix1(3); 
    TDynamicMatrix<int> matrix2(4); 
    EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
}

