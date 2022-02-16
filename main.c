#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <malloc.h>
#include "libs/data_structures/matrix/matrix.h"

//---------------------------------------- TASK 1
void changeRowsByMinAndMax() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    position minElementPos = getMinValuePos(m);
    position maxElementPos = getMaxValuePos(m);

    swapRows(m, (minElementPos).rowIndex, (maxElementPos).rowIndex);

    outputMatrix(m);
}

//---------------------------------------- TASK 2
void sortRowsByMaxElement() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3}, 3, 3);

    insertionSortRowsMatrixByRowCriteria(m, getMax);

    outputMatrix(m);
}

//---------------------------------------- TASK 3
void sortColsByMinElement() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 2, 4, 3, 3,
                                              2, 5, 1, 8, 2, 7,
                                              6, 1, 4, 4, 8, 3}, 3, 6);

    insertionSortColsMatrixByColCriteria(m, getMin);

    outputMatrix(m);
}

//---------------------------------------- TASK 4
void getSquareOfMatrixIfSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              2, 1}, 2, 2);

    if (isSymmetricMatrix(m))
        m = mulMatrices(m, m);

    outputMatrix(m);
}

//---------------------------------------- TASK 5
void transposeIfMatrixHasNotEqualSumOfRows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    long long aOfSum[m.nRows];

    for (size_t i = 0; i < m.nRows; ++i)
        aOfSum[i] = getSum(m.values[i], m.nCols);

    if (isUnique(aOfSum, m.nRows))
        transposeSquareMatrix(m);

    outputMatrix(m);
}

//---------------------------------------- TASK 6

//---------------------------------------- TASK 7

//---------------------------------------- TASK 8









int main() {

    changeRowsByMinAndMax();
    sortRowsByMaxElement();
    sortColsByMinElement();
    getSquareOfMatrixIfSymmetric();
    transposeIfMatrixHasNotEqualSumOfRows();

//    matrix m = createMatrixFromArray((int[]) {0, 1, 2,
//                                              0, 1, 2,
//                                              0, 1, 2}, 3, 3);
//    swapColumns(m, 0, 1);
//    outputMatrix(m);
//    //matrix m = getMemMatrix(3,3);
//   // inputMatrix(m);
//    int a[] = {1, 2, 3,
//                4, 5, 6,
//                7, 8, 9};
//    matrix m = createMatrixFromArray(a, 3, 3);
//    //transposeSquareMatrix(m);
//    swapColumns(m,1, 0);
//    //swapRows(m,0, 2);
//    outputMatrix(m);
//    //printf("%d %d ",getMinValuePos(m).rowIndex, getMinValuePos(m).colIndex);
    //test();

    return 0;
}
