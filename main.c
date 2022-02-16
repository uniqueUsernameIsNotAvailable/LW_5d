#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
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
void sortRowsByMinElement() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3}, 3, 3);

    insertionSortRowsMatrixByRowCriteria(m, getMax);

    outputMatrix(m);
}
//---------------------------------------- TASK 3

//---------------------------------------- TASK 4

//---------------------------------------- TASK 5

//---------------------------------------- TASK 6

//---------------------------------------- TASK 7

//---------------------------------------- TASK 8









int main() {

    changeRowsByMinAndMax();
    sortRowsByMinElement();
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
