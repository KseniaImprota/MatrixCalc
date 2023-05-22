#include <iostream>
#include <fstream>
#include <vector>
#include "gtest/gtest.h"
//#include "Matrix.h"

using namespace std;

int main(int argc, char** argv) {

   // A = A.transposedMatrix();
   // A.printMatrix();
   // (A * B).printMatrix();
   // (A / 2).printMatrix();
    //ADet = A.det();
   // BDet = B.det();
    //cout << BDet << endl;
    //cout << ADet << endl;
    //Arang = A.rang();
    //cout <<"rang " << Arang << endl;
    //B = B.inverseMatrix();
    //B.printMatrix();
    //A.printMatrix();
    //B.printMatrix();
    //A.exponentiation(2).printMatrix();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
