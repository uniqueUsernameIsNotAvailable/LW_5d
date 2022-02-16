#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


matrix getMemMatrix(size_t nRows, size_t nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);

    for (size_t i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);

    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

void freeMemMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        free(m.values[i]);

    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
}

void inputMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = 0; j < m.nCols; j++)
            scanf("%d", &m.values[i][j]);
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (size_t i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

void outputMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }

    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (size_t i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void swapRows(matrix m, int i1, int i2) {
    swap(&m.values[i1], &m.values[i2], sizeof(int));
}

void swapColumns(matrix m, int j1, int j2) {
    for (size_t i = 0; i < m.nRows; i++)
        swap(&m.values[i][j1], &m.values[i][j2], sizeof(int));
}


void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteriaArray = (int *) malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = i; j > 0 && criteriaArray[j - 1] > criteriaArray[j]; j--) {
            swap(&criteriaArray[j - 1], &criteriaArray[j], sizeof(int));
            swapRows(m, j, j - 1);
        }
    }

    free(criteriaArray);
}


void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteriaArray = (int *) malloc(sizeof(int) * m.nCols);
    int *auxiliaryArray = (int *) malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j)
            auxiliaryArray[j] = m.values[j][i];

        criteriaArray[i] = criteria(auxiliaryArray, m.nRows);
    }

    for (int i = 0; i < m.nCols; ++i) {
        for (int j = i; j > 0 && criteriaArray[j - 1] > criteriaArray[j]; j--) {
            swap(&criteriaArray[j - 1], &criteriaArray[j], sizeof(int));
            swapColumns(m, j, j - 1);
        }
    }

    free(criteriaArray);
    free(auxiliaryArray);
}

_Bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

_Bool areTwoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nCols != m2.nCols || m1.nRows != m2.nRows)
        return 0;

    for (size_t i = 0; i < m1.nRows; i++)
        for (size_t j = 0; j < m1.nCols; j++)
            if ((m1).values[i][j] != (m2).values[i][j])
                return 0;

    return 1;
}

_Bool isEMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = 0; j < m.nCols; j++)
            if (i == j && m.values[i][j] != 1 || i != j && m.values[i][j] != 0)
                return 0;

    return 1;

}

_Bool isSymmetricMatrix(matrix m) {
    if (isSquareMatrix(m) == 0)
        return 0;

    for (int i = 0; i < (m).nRows; ++i)
        for (int j = 0; j < (m).nCols; ++j)
            if ((m).values[i][j] != (m).values[j][i])
                return 0;

    return 1;
}

void transposeSquareMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = i + 1; j < m.nCols; j++)
            swap(&m.values[i][j], &m.values[j][i], sizeof(int));
}

position getMinValuePos(matrix m) {
    position minIndex = {0, 0};
    int minValue = m.values[0][0];

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minIndex = (position) {i, j};
            }

    return minIndex;
}

position getMaxValuePos(matrix m) {
    position maxIndex = {0, 0};
    int maxValue = m.values[0][0];

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxIndex = (position) {i, j};
            }

    return maxIndex;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int inArrayCounter = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[inArrayCounter++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int inArrayCounter = 0;
    for (int h = 0; h < nMatrices; h++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[h].values[i][j] = values[inArrayCounter++];

    return ms;
}

//--------------------------------------------------- NEW FUNCTIONS FROM TASKS

matrix mulMatrices(matrix m1, matrix m2) {
    if ((m1).nRows != (m2).nCols) {
        fprintf(stderr, "Matrices won't multiply");
        exit(2022);
    }

    matrix mProduct = getMemMatrix((m2).nRows, (m1).nCols);

    for (int i = 0; i < (m1).nCols; ++i)
        for (int j = 0; j < (m2).nRows; ++j) {
            (mProduct).values[i][j] = 0;
            for (int k = 0; k < (m1).nRows; ++k)
                (mProduct).values[i][j] += (m1).values[i][k] * (m2).values[k][j];
        }

    return mProduct;
}