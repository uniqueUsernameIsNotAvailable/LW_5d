#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "libs/data_structures/matrix/matrix.h"

//---------------------------------------- TASK 1
void changeRowsByMinAndMax(matrix m) {


    position minElementPos = getMinValuePos(m);
    position maxElementPos = getMaxValuePos(m);

    swapRows(m, (minElementPos).rowIndex, (maxElementPos).rowIndex);
}

void test_changeRowsByMinAndMax() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    matrix wantedMatrix = createMatrixFromArray((int[]) {7, 8, 9,
                                                         4, 5, 6,
                                                         1, 2, 3}, 3, 3);

    changeRowsByMinAndMax(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 2
void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void test_sortRowsByMaxElement() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3}, 3, 3);

    matrix wantedMatrix = createMatrixFromArray((int[]) {3, 2, 3,
                                                         7, 1, 2,
                                                         1, 8, 1}, 3, 3);

    sortRowsByMaxElement(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 3
void sortColsByMinElement(matrix m) {

    insertionSortColsMatrixByColCriteria(m, getMin);
}

void test_sortColsByMinElement() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 2, 4, 3, 3,
                                              2, 5, 1, 8, 2, 7,
                                              6, 1, 4, 4, 8, 3}, 3, 6);

    matrix wantedMatrix = createMatrixFromArray((int[]) {5, 2, 3, 3, 3, 4,
                                                         5, 1, 2, 2, 7, 8,
                                                         1, 4, 6, 8, 3, 4}, 3, 6);

    sortColsByMinElement(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 4
void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m))
        *m = mulMatrices(*m, *m);
}

void test_getSquareOfMatrixIfSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              2, 1}, 2, 2);

    matrix wantedMatrix = createMatrixFromArray((int[]) {5, 4,
                                                         4, 5}, 2, 2);

    getSquareOfMatrixIfSymmetric(&m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 5
void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long aOfSum[m.nRows];

    for (size_t i = 0; i < m.nRows; ++i)
        aOfSum[i] = getSum(m.values[i], m.nCols);

    if (isUnique(aOfSum, m.nRows))
        transposeSquareMatrix(m);
}

void test_transposeIfMatrixHasNotEqualSumOfRows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    matrix wantedMatrix = createMatrixFromArray((int[]) {1, 4, 7,
                                                         2, 5, 8,
                                                         3, 6, 9}, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 6
_Bool isMutuallyInverseMatrices(matrix m, matrix m1) {
    if (m.nRows != m1.nRows || m.nCols != m1.nCols)
        return 0;

    matrix m2 = mulMatrices(m, m1);
    _Bool result = isEMatrix(m2);

    freeMemMatrix(m2);

    return result;
}

void test_isMutuallyInverseMatrices() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              0,1}, 2, 2);

    matrix trueMatrix = createMatrixFromArray((int[]) {1, -2,
                                                       0, 1}, 2, 2);

    assert(isMutuallyInverseMatrices(m, trueMatrix));

    freeMemMatrix(m);
    freeMemMatrix(trueMatrix);
}
//---------------------------------------- TASK 7

/*
 * TODO: REWRITE LEFT TO RIGHT
 * ARRAY FOR MAXES
 * K = j + 2 - i
*/
int getMaxFromPDiagonal(matrix m, int i, int j) {
    int maxElement = m.values[i][j];

    while (i < m.nRows && j < m.nCols)
        maxElement = max(maxElement, m.values[i++][j++]);

    return maxElement;
}

long long findSumOfMaxesOfPseudoDiagonal() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);

    long long sumOfMaxOfPDiagonal = 0;
    for (int i = 1; i < m.nRows; ++i)
        sumOfMaxOfPDiagonal += getMaxFromPDiagonal(m, i, 0);

    for (int i = 0; i < m.nCols; ++i)
        sumOfMaxOfPDiagonal += getMaxFromPDiagonal(m, 0, i);

    //SUBTRACT MAIN DIAG
    return sumOfMaxOfPDiagonal - getMaxFromPDiagonal(m, 0, 0);
}

//TODO:
//---------------------------------------- TASK 8
int getMinInArea(matrix m) {
    position maximum = getMaxValuePos(m);

    int rowNumber = maximum.rowIndex;
    int leftElement = maximum.colIndex;
    int rightElement = maximum.colIndex;

    int minInArea = m.values[maximum.rowIndex][maximum.colIndex];
//were unstable, testing.
    while (rowNumber >= 0) {
        for (int i = leftElement; i < rightElement; i++)
            minInArea = min(m.values[rowNumber][i], minInArea);

        if (rightElement < m.nCols - 1)//is true?
            rightElement++;

        if (leftElement > 0)
            leftElement--;

        rowNumber--;
    }

    return minInArea;
}

void test_getMinInArea() {
    matrix m = createMatrixFromArray((int[]) {10, 7, 5, 6,
                                              3, 11, 8, 9,
                                              4, 1, 12, 2}, 3, 4);
    int wantedResult = 5;

    assert(getMinInArea(m) == wantedResult);

    freeMemMatrix(m);
}


int main() {
    test_changeRowsByMinAndMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    //test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();

    return 0;
}
