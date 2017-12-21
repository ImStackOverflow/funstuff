// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "MatrixMath.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****
// **** Declare function prototypes ****

int main() {
    BOARD_Init();
    short i, j, z, check, passed, total;
    float result[3][3];
    float mat2[3][3] = {
        {3, 0, 2},
        {2, 0, -2},
        {0, 1, 1}
    };
    float mat1[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };
    float coeficient = 3;
    /* i and j are for for loops
     * z is for while loop
     * check is for checking validity
     * coeficient is for value passed into function (scalar add//multiply)
     * result is result matrix */

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/


    /******************************************************************************
     * check matrix multiply
     *****************************************************************************/
    total = 0;
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        MatrixMultiply(mat1, mat2, result);
        int c;
        float sum;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                for (c = 0; c < 3; c++) {
                    sum += mat1[i][c] * mat2[c][j];
                }
                if (abs(result[i][j] - (sum) <= FP_DELTA)) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 0) {
            break;
        }
        if (check == 1) {
            passed++;
            total++;

        }
        z++;
    }


    printf("Matrix Multiply passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix add
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        float mat3[3][3] = {
            {3, 0, 2},
            {2, 0, -2},
            {0, 1, 1}
        };
        MatrixAdd(mat1, mat3, result); //function changes values in mat2 for some reason
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (abs(result[i][j] - (mat1[i][j] + mat3[i][j])) <= FP_DELTA) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    if (passed < 2) {
        printf("\nmatrix is being replaced with unknown numbers on first trial of matrixadd\n"
                "despite the matricies not being changed in function MatrixAdd\n"
                "\n");
    }

    printf("Matrix Add passed: (%i/2)\n", passed);



    /******************************************************************************
     * check matrix equals
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        if (MatrixEquals(mat1, mat1) == 1) { // pass same matrix
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix equals passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix scalar multiply
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        float mat3[3][3] = {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        };
        check = 0;
        MatrixScalarMultiply(coeficient, mat1, result);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (abs(result[i][j] - (mat3[i][j] * coeficient)) <= FP_DELTA) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix scalar multiply passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix scalar add
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        MatrixScalarAdd(coeficient, mat1, result);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (abs(result[i][j] - (mat1[1][j] + coeficient)) <= FP_DELTA) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix scalar add passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix determinant
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        result[1][1] = mat1[0][0]*(mat1[1][1] * mat1[2][2] - mat1[2][1] * mat1[1][2]);
        result[1][1] -= mat1[0][1]*(mat1[1][0] * mat1[2][2] - mat1[2][0] * mat1[1][2]);
        result[1][1] += mat1[0][2]*(mat1[1][0] * mat1[2][1] - mat1[2][0] * mat1[1][1]);
        int size = sizeof (mat1) / sizeof (mat1[0]);
        result[2][2] = MatrixDeterminant(mat1, size);
        if (abs(result[1][1] - result[2][2]) <= FP_DELTA) {
            passed++;
            total++;
        }
        z++;
    }
    printf("Matrix determinant passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix trace
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        if (abs(MatrixTrace(mat1) - (mat1[0][0] + mat1[1][1] + mat1[2][2]))
                <= FP_DELTA) {
            check = 1;
        } else {
            check = 0;
            break;
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix trace passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix transpose
     *****************************************************************************/
    z = 0;
    passed = 0;
    while (z < 2) {
        check = 0;
        MatrixTranspose(mat1, result);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (abs(result[i][j] - mat1[j][i]) <= FP_DELTA) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix transpose passed: (%i/2)\n", passed);

    /******************************************************************************
     * check matrix inverse
     *****************************************************************************/
    z = 0;
    passed = 0;
    float checkarray[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    while (z < 2) {
        check = 0;
        MatrixInverse(mat1, result);
        MatrixMultiply(result, mat1, result);
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (abs(result[i][j] - checkarray[i][j]) <= FP_DELTA) {
                    check = 1;
                } else {
                    check = 0;
                    break;
                }
            }
            if (check == 0) {
                break;
            }
        }
        if (check == 1) {
            passed++;
            total++;
        } else {
        }
        z++;
    }
    printf("Matrix inverse passed: (%i/2)\n", passed);
    printf("______________________________________");

    printf("\ntotal tests passed: %u/18\n", total);


    /******************************************************************************
     * check matrix print
     *****************************************************************************/
    double test[3][3] = {
        {1.1, 2.2, 3.3},
        {4.4, 5.5, 6.6},
        {7.7, 8.8, 9.9}
    };

    printf("the output of MatrixPrint is: \n");
    MatrixPrint(test);

    printf("the output of MatrixPrint should look like: \n");
    printf("______________________\n");
    printf("| 1.10 | 2.20 | 3.30 |\n");
    printf("----------------------\n");
    printf("| 4.40 | 5.50 | 6.60 |\n");
    printf("----------------------\n");
    printf("| 7.70 | 8.80 | 9.90 |\n");
    printf("----------------------\n");


    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/
    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

