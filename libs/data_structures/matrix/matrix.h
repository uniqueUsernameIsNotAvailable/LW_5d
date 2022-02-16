#ifndef LW_5D_MATRIX_H
#define LW_5D_MATRIX_H

#include "../../algorithms/array/array.h"

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;


/*!
 * Размещает в динамической памяти матрицу размером nRows на nCols
 * @param nRows - кол-во строк в матрице
 * @param nCols - кол-во столбцов в матрице
 * @return матрица в виде (matrix) {values, nRows, nCols}
 */
matrix getMemMatrix(size_t nRows, size_t nCols);

/*!
 * Размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
 * @param nMatrices - кол-во матриц
 * @param nRows - кол-во строк в матрице
 * @param nCols - кол-во столбцов в матрице
 * @return указатель на нулевую матрицу
 */
matrix *getMemArrayOfMatrices(size_t nMatrices, size_t nRows, size_t nCols);

/*!
 * Освобождает память, выделенную под хранение матрицы m
 * @param m - матрица
 */
void freeMemMatrix(matrix m);

/*!
 * Освобождает память, выделенную под хранение массива ms из nMatrices матриц
 * @param ms - указатель на массив из матриц
 * @param nMatrices - кол-во матриц
 */
void freeMemMatrices(matrix *ms, int nMatrices);

/*!
 * Ввод матрицы m
 * @param m - матрица
 */
void inputMatrix(matrix m);

/*!
 * Ввод массива из nMatrices матриц, хранящейся по адресу ms
 * @param ms - указатель на массив из матриц
 * @param nMatrices - кол-во матриц
 */
void inputMatrices(matrix *ms, int nMatrices);

/*!
 * Вывод матрицы m
 * @param m - матрица
 */
void outputMatrix(matrix m);

/*!
 * Вывод массива из nMatrices матриц, хранящейся по адресу ms
 * @param ms - указатель на массив из матриц
 * @param nMatrices - кол-во матриц
 */
void outputMatrices(matrix *ms, int nMatrices);

/*!
 * Обмен строк с порядковыми номерами i1 и i2 в матрице m
 * @param m - матрица
 * @param i1 - порядковый номер первой строки
 * @param i2 - порядковый номер второй строки
 */
void swapRows(matrix m, int i1, int i2);

/*!
 * Обмен столбцов с порядковыми номерами j1 и j2 в матрице m
 * @param m - матрица
 * @param j1 - порядковый номер первого столбца
 * @param j2 - порядковый номер второго столбца
 */
void swapColumns(matrix m, int j1, int j2);


/*!
 * Сортировка вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк
 * @param m - матрица
 * @param criteria - функция, по неубыванию значения которой выполняется сортировка
 * @details Пример: создание функции-критерия под массив -> передача фуккции как критерий в эту в функцию -> функция считает значение функции-критерия для каждой строки, записывает результат в промежуточный массив -> сортировка промежуточного массива, но при обмене элементов происходит обмен и соответствующих строк
 */
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

/*!
 * Сортировка вставками столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
 * @param m - матрица
 * @param criteria - функция, по неубыванию значения которой выполняется сортировка
 * @details Функция критерий ожидает указатель на последовательный участок памяти. Но в силу такого размещения матриц это невозможно, поэтому придётся выполнить копирование столбца в промежуточный массив и только потом вычислять значение критерия. Таким образом допускается, что будет использована дополнительная память для значений критерия и столбца матрицы
 */
void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

/*!
 * Возвращает 1, если матрица m является квадратной, 0 – в противном случае.
 * @param m - матрица
 * @return 0 или 1
 */
_Bool isSquareMatrix(matrix m);

/*!
 * Возвращает значение 1, если матрицы m1 и m2 равны, 0 – в противном случае.
 * @param m1 - первая матрица
 * @param m2 - вторая матрица
 * @return 0 или 1
 */
_Bool areTwoMatricesEqual(matrix m1, matrix m2);

/*!
 * Возвращает 1, если матрица m является единичной, 0 – в противном случае.
 * @param m - матрица
 * @return 0 или 1
 */
_Bool isEMatrix(matrix m);

/*!
 * Возвращает 1, если матрица m является симметричной, 0 – в противном случае.
 * @param m - матрица
 * @return 0 или 1
 */
_Bool isSymmetricMatrix(matrix m);

/*!
 * Транспонирует квадратную матрицу m
 * @param m - матрица
 */
void transposeSquareMatrix(matrix m);

/*!
 * Возвращает позицию минимального элемента матрицы m
 * @param m - матрица
 * @return minIndex - индекс минимального элемента в виде позиции
 */
position getMinValuePos(matrix m);

/*!
 * Возвращает позицию максимального элемента матрицы m
 * @param m - матрица
 * @return maxIndex - индекс максимального элемента в виде позиции
 */
position getMaxValuePos(matrix m);

/*!
 * Возвращает матрицу, размера nRows на nCols, построенного из элементов массива a, размещенную в динамической памяти
 * @param a - указатель на массив для постройки матрицы
 * @param nRows - кол-во строк
 * @param nCols - кол-во столбцов
 * @return матрица в виде (matrix) {values, nRows, nCols}
 */
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

/*!
 * Возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных в динамической памяти, построенных из элементов массива a
 * @param values - указатель на массив
 * @param nMatrices - кол-во матриц
 * @param nRows - кол-во строк в матрице
 * @param nCols - кол-во столбцов в матриц
 * @return указатель на нулевую матрицу
 */
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);


#endif //LW_5D_MATRIX_H
