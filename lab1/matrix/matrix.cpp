#include <iostream>
#include "matrix.h"

int main() {
    matrix myMtr(3, 3);
    matrix mtr1(3, 2);
    matrix mtr2(2, 3);

    setRandomElems(mtr1, 10);
    setRandomElems(mtr2, 10);

    std::cout << "Matrix C 3x3 of 0:" << std::endl;
    printMatrix(myMtr);
    std::cout << "==============================================" << std::endl;

    setRandomElems(myMtr, 10);

    std::cout << "Matrix A 2x3 of double(pseudo-random):" << std::endl;
    printMatrix(mtr1);
    std::cout << "==============================================" << std::endl;
    std::cout << "Matrix B 3x2 of double(pseudo-random):" << std::endl;
    printMatrix(mtr2);
    std::cout << "==============================================" << std::endl;
    std::cout << "Matrix C 3x3 of double(pseudo-random):" << std::endl;
    printMatrix(myMtr);
    std::cout << "==============================================" << std::endl;

    std::cout << "Matrix A + A:" << std::endl;
    printMatrix(mtr1+mtr1);
    std::cout << "==============================================" << std::endl;

    std::cout << "Matrix B * 1.1:" << std::endl;
    printMatrix(mtr2 * 1.1);
    std::cout << "==============================================" << std::endl;

    std::cout << "Transponsed matrix A:" << std::endl;
    printMatrix(mtr1.transpose());
    std::cout << "==============================================" << std::endl;

    std::cout << "Determinant for matrix C:" << std::endl;
    std::cout << myMtr.getDeterminant() << std::endl;
    std::cout << "==============================================" << std::endl;

    std::cout << "Reverse matrix for matrix C:" << std::endl;
    printMatrix(myMtr.reverse());
    std::cout << "==============================================" << std::endl;

    std::cout << "Elem of matrix C on position [1, 1]:" << std::endl;
    std::cout << myMtr.getElem(1, 1) << std::endl;
    std::cout << "==============================================" << std::endl;

    myMtr[matrix::I(1, 1)] = 1488.1;

    std::cout << "Elem of matrix C on position [1, 1] after changing using [struct]:" << std::endl;
    std::cout << myMtr[matrix::I(1, 1)] << std::endl;
    std::cout << "==============================================" << std::endl;

    return 0;
}
