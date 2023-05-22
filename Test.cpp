#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"

using namespace std;

void read_matrices_from_file(const string& filename, Matrix& A, Matrix& B) {
    std::ifstream infile(filename);
    double ADet, BDet;
    int Arang;
    int rows1, cols1, rows2, cols2;
    infile >> rows1 >> cols1 >> rows2 >> cols2;
    A = Matrix(rows1, cols1);
    B = Matrix(rows2, cols2);

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            infile >> A(i, j);
        }
    }
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            infile >> B(i, j);
        }
    }
}

TEST(Test1, SumMartix) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix summ = A + B;
    double result[3][3] = { {3, 7, 5}, {1, 7, 7}, { 3, 4, 5 } };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(summ(i,j), result[i][j]);
        }
    }
  
  EXPECT_TRUE(true);
}

TEST(Test2, Difference) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix difference = A - B;
    double result[3][3] = { {1, 5, -1}, {-1, -3, -3}, { -1, -2, -3} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(difference(i, j), result[i][j]);
        }
    }

    EXPECT_TRUE(true);
}

TEST(Test3, Ñomposition) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix composition = A * B;
    double result[3][3] = { {12, 38, 44}, {6, 16, 18}, { 4, 9, 12} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(composition(i, j), result[i][j]);
        }
    }

    EXPECT_TRUE(true);
}

TEST(Test4, Partial) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix partialA = (A / 2);
    Matrix partialB = (B / 2);
    double resultForA[3][3] = { {1, 3, 1}, {0, 1, 1}, { 0.5, 0.5, 0.5} };
    double resultForB[3][3] = { {0.5, 0.5, 1.5}, {0.5, 2.5, 2.5}, { 1, 1.5, 2} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(partialA(i, j), resultForA[i][j]);
            EXPECT_EQ(partialB(i, j), resultForB[i][j]);
        }
    }

    EXPECT_TRUE(true);
}

TEST(Test5, Determinant) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    double determinantA = A.det();
    double determinantB = B.det();
    double resultForA = 8;
    double resultForB = -10;

    EXPECT_DOUBLE_EQ(determinantA, resultForA);
    EXPECT_DOUBLE_EQ(determinantB, resultForB);
    
    EXPECT_TRUE(true);
}

TEST(Test6, RankMatrix) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    double rankMatrixA = A.rang();
    double rankMatrixB = B.rang();
    double resultForA = 3;
    double resultForB = 3;

    EXPECT_EQ(rankMatrixA, resultForA);
    EXPECT_EQ(rankMatrixB, resultForB);

    EXPECT_TRUE(true);
}

TEST(Test7, Inverse) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix inverseA = A.inverseMatrix();
    Matrix inverseB = B.inverseMatrix();
    double resultForA[3][3] = { {0, -0.5, 1}, {0.25, 0, -0.5}, { -0.25, 0.5, 0.5} };
    double resultForB[3][3] = { {-0.5, -0.5, 1}, {-0.6, 0.2, 0.2}, { 0.7, 0.1, -0.4} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(inverseA(i, j), resultForA[i][j]);
            EXPECT_EQ(inverseB(i, j), resultForB[i][j]);
        }
    }

    EXPECT_TRUE(true);
}

TEST(Test8, Transposed) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix transposedA = A.transposedMatrix();
    Matrix transposedB = B.transposedMatrix();
    double resultForA[3][3] = { {2, 0, 1}, {6, 2, 1}, { 2, 2, 1} };
    double resultForB[3][3] = { {1, 1, 2}, {1, 5, 3}, { 3, 5, 4} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(transposedA(i, j), resultForA[i][j]);
            EXPECT_EQ(transposedB(i, j), resultForB[i][j]);
        }
    }

    EXPECT_TRUE(true);
}

TEST(Test9, Exponentiation) {

    Matrix A, B;
    read_matrices_from_file("data.txt", A, B);

    Matrix exponentiationA = A.exponentiation(3);
    Matrix exponentiationB = B.exponentiation(4);
    double resultForA[3][3] = { {30, 106, 82}, {10, 30, 22}, {11, 41, 29} };
    double resultForB[3][3] = { {564, 1315, 1620}, {1408, 3313, 4064}, {1049, 2457, 3021} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(exponentiationA(i, j), resultForA[i][j]);
            EXPECT_EQ(exponentiationB(i, j), resultForB[i][j]);
        }
    }

    EXPECT_TRUE(true);
}