#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>
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

    selSortColsMatrixByColCriteria(m, getMin);
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
                                              0, 1}, 2, 2);

    matrix trueMatrix = createMatrixFromArray((int[]) {1, -2,
                                                       0, 1}, 2, 2);

    assert(isMutuallyInverseMatrices(m, trueMatrix));

    freeMemMatrix(m);
    freeMemMatrix(trueMatrix);
}

//---------------------------------------- TASK 7
long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int sizeA = m.nCols + m.nRows - 1;
    int *addingArray = malloc(sizeof(int) * sizeA);
    int startPosition = m.nRows - 1;

    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j) {
            int actualPosition = startPosition + j - i;

            if (i == 0 || j == 0)
                addingArray[actualPosition] = m.values[i][j];
            else
                addingArray[actualPosition] = max(addingArray[actualPosition], m.values[i][j]);
        }

    addingArray[startPosition] = 0;

    long long sumOfMaxesOfPD = getSum(addingArray, sizeA);
//MEM LEAK WAS HERE
    free(addingArray);

    return sumOfMaxesOfPD;
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);

    int wantedResult = 20;

    assert(findSumOfMaxesOfPseudoDiagonal(m) == wantedResult);

    freeMemMatrix(m);
}

//---------------------------------------- TASK 8
int getMinInArea(matrix m) {
    position maximum = getMaxValuePos(m);

    int rowNumber = maximum.rowIndex;
    int leftElement = maximum.colIndex;
    int rightElement = maximum.colIndex;

    int minInArea = m.values[maximum.rowIndex][maximum.colIndex];
//were unstable, testing. fixed
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

//---------------------------------------- TASK 9
void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

void test_sortByDistances() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              40, 50, 60,
                                              7, 8, 9}, 3, 3);

    matrix wantedMatrix = createMatrixFromArray((int[]) {1, 2, 3,
                                                         7, 8, 9,
                                                         40, 50, 60}, 3, 3);
    sortByDistances(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 10
int countEqClassesByRowsSum(matrix m) {
    long long *rowSum = malloc(sizeof(long long) * m.nRows);

    for (int i = 0; i < m.nRows; ++i)
        rowSum[i] = getSum(m.values[i], m.nCols);
    //PREVENT LEAK BY CREATING VAR FOR RESULT, FREE CREATED ARRAY!!!!!!!
    int eqClassesCounter = countNUnique(rowSum, m.nRows);

    free(rowSum);

    return eqClassesCounter;
}

void test_countEqClassesByRowsSum() {
    matrix m = createMatrixFromArray((int[]) {7, 1,
                                              2, 7,
                                              5, 4,
                                              4, 3,
                                              1, 6,
                                              8, 0}, 6, 2);
    int wantedResult = 3;

    assert(countEqClassesByRowsSum(m) == wantedResult);

    freeMemMatrix(m);
}

//---------------------------------------- TASK 11
int getNSpecialElement(matrix m, int nRows, int nCols) {
    int amountOfSpec = 0;
//begin from left to right. look for spec element, calc sumOfCol
    for (size_t j = 0; j < m.nCols; j++) {
        int specElement = m.values[0][j];
        int coloumnSum = 0;

        for (size_t i = 1; i < m.nRows; i++) {
            if (m.values[i][j] > specElement) {
                coloumnSum += specElement;
                specElement = m.values[i][j];
            } else
                coloumnSum += m.values[i][j];
        }

        if (specElement > coloumnSum)
            amountOfSpec++;
    }

    return amountOfSpec;
}

void test_getNSpecialElement() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 5, 4,
                                              2, 3, 6, 7,
                                              12, 2, 1, 2}, 3, 4);
    int wantedResult = 2;

    assert(getNSpecialElement(m, 3, 4) == wantedResult);

    freeMemMatrix(m);
}

//---------------------------------------- TASK 12
position getLeftMin(matrix m) {
    int minimum = m.values[0][0];
    position minLeftPos = {0, 0};

    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[i][j] < minimum) {
                minimum = m.values[i][j];
                minLeftPos = (position) {i, j};
            }

    return minLeftPos;
}

void swapPenultimateRow(matrix m) {
    position minimum = getLeftMin(m);
    if (m.nRows < 2) {
        fprintf(stderr, "Matrices are too little");
        exit(2022);
    }

    int col[m.nRows];
    for (size_t i = 0; i < m.nRows; i++)
        col[i] = m.values[i][minimum.colIndex];

    memcpy(m.values[m.nRows - 2], col, sizeof(int) * m.nCols);
}

void test_swapPenultimateRow() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 1}, 3, 3);

    matrix wantedMatrix = createMatrixFromArray((int[]) {1, 2, 3,
                                                         1, 4, 7,
                                                         7, 8, 1}, 3, 3);

    swapPenultimateRow(m);

    assert(areTwoMatricesEqual(m, wantedMatrix));

    freeMemMatrix(m);
    freeMemMatrix(wantedMatrix);
}

//---------------------------------------- TASK 13
_Bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i)
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return 0;

    return 1;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int amountOfNonDecMatrices = 0;

    for (int i = 0; i < nMatrix; ++i)
        if (hasAllNonDescendingRows(ms[i]))
            amountOfNonDecMatrices++;

    return amountOfNonDecMatrices;
}

void test_countNonDescendingRowsMatrices() {
    matrix *wantedMatrices = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,

                    9, 8, 7,
                    6, 5, 4,

                    145, 7678, 121,
                    2523876, -757, 7979

            }, 3, 2, 3
    );

    int wantedResult = 1;

    assert(countNonDescendingRowsMatrices(wantedMatrices, 3) == wantedResult);

    freeMemMatrices(wantedMatrices, 3);
}

//---------------------------------------- TASK 14
int countZeroRows(matrix m) {
    int amountOfZeroRows = 0;

    for (int i = 0; i < m.nRows; ++i)
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            amountOfZeroRows++;

    return amountOfZeroRows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int zeroestMatrix[nMatrix];

    for (size_t i = 0; i < nMatrix; i++)
        zeroestMatrix[i] = countZeroRows(ms[i]);

    printf("Matrices with max rows of zero\n");

    int max = getMax(zeroestMatrix, nMatrix);

    for (int i = 0; i < nMatrix; i++)
        if (zeroestMatrix[i] == max)
            outputMatrix(ms[i]);
}

void test_printMatricesWithMaxZeroRows() {
    matrix *wantedMatrices = createArrayOfMatrixFromArray(
            (int[]) {
                    0, 1,
                    1, 0,
                    0, 0,

                    1, 1,
                    1, 2,
                    1, 1,

                    0, 0,
                    0, 0,
                    4, 7,

                    0, 0,
                    1, 0,
                    0, 0,

                    0, 1,
                    0, 2,
                    0, 3,

            }, 5, 3, 2);

    printMatrixWithMaxZeroRows(wantedMatrices, 5);

    freeMemMatrices(wantedMatrices, 5);
}

//---------------------------------------- TASK 15
int calculateNorm(matrix m) {
    int norm = abs(m.values[0][0]);

    for (size_t i = 0; i < m.nRows; ++i) {
        int max = abs(getMax(m.values[i], m.nCols));

        if (norm < max)
            norm = max;
    }

    return norm;
}

void printMatricesWithMinNorm(matrix *ms, int nMatrix) {
    int normInMatrices[nMatrix];
    for (size_t i = 0; i < nMatrix; ++i)
        normInMatrices[i] = calculateNorm(ms[i]);

    printf("Matrices with lowest norm\n");

    int min = getMin(normInMatrices, nMatrix);
    for (size_t i = 0; i < nMatrix; i++)
        if (normInMatrices[i] == min)
            outputMatrix(ms[i]);
}

void test_printMatrixWithMinNorm() {
    matrix *wantedMatrices = createArrayOfMatrixFromArray(
            (int[]) {
                    0, 1,
                    1, 0,
                    0, 0,

                    1, 1,
                    1, 2,
                    1, 1,

                    0, 0,
                    0, 0,
                    4, 7,

                    0, 0,
                    1, 0,
                    0, 0,

                    0, 1,
                    0, 2,
                    0, 3,

            }, 5, 3, 2);

    printMatricesWithMinNorm(wantedMatrices, 5);

    freeMemMatrices(wantedMatrices, 5);
}


void test() {
    test_changeRowsByMinAndMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_printMatricesWithMaxZeroRows();
    test_printMatrixWithMinNorm();
}

int main() {
    test();
    printf("ALL SYSTEMS ARE OPERATIONAL, CAPTAIN");

    return 256;
}
