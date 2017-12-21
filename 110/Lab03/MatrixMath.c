#include <stdio.h>
#include "MatrixMath.h"

/******************************************************************************
 * Matrix multiply
 *****************************************************************************/

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int sum, a, b, c;
    for (a = 0; a < 3; a++) {
	for (b = 0; b < 3; b++) {
	    sum = 0;
	    for (c = 0; c < 3; c++) {
		sum += mat1[a][c] * mat2[c][b];
	    }
	    result[a][b] = sum;
	}
    }
}

/******************************************************************************
 * Matrix add
 *****************************************************************************/

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i, j;
    for (i = 0; i <= 3; i++) { //rows in matrix
	for (j = 0; j <= 3; j++) {//collum in matrix
	    result[i][j] = (mat1[i][j] + mat2[i][j]);
	}
    }
}

/******************************************************************************
 * Matrix equals
 *****************************************************************************/

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    int a, b;
    for (a = 0; a < 3; a++) {
	for (b = 0; b < 3; b++) {
	    if (mat1[a][b] != mat2[a][b]) {
		return 0;
	    }
	}
    }
    return 1;
}

/******************************************************************************
 * matrix scalar multiply
 *****************************************************************************/
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int i, j;
    for (i = 0; i <= 3; i++) { //rows in matrix
	for (j = 0; j <= 3; j++) {//collum in matrix
	    result[i][j] = (mat[i][j] * x);
	}
    }
}

/******************************************************************************
 * Matrix scalar add
 *****************************************************************************/

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int a, b;
    for (a = 0; a < 3; a++) {
	for (b = 0; b < 3; b++) {
	    result[a][b] = (x + mat[a][b]);
	}
    }
}

/******************************************************************************
 * matrix determinant
 *****************************************************************************/

float MatrixDeterminant(float mat[3][3], int arrlen)
{
    float part1, part2;
    float determinant = 0;
    float subtract = 0;
    int z, j, i;
    arrlen--;
    for (z = 0; z <= arrlen + 1;) {
	j = z++;
	i = 0;
	part1 = 1;

	do {
	    part1 *= mat[i][j];
	    i++;
	    j++;
	    if (j == arrlen + 1) {
		j = 0;
	    }
	} while (i <= arrlen);
	determinant += part1;
    }

    j = arrlen;
    for (z = 0; z <= arrlen; z++) {
	i = 0;
	part2 = 1;
	do {
	    part2 *= mat[i][j];
	    i++;
	    j--;
	    if (j < 0) {
		j = 2;
	    }
	} while (i <= arrlen);
	subtract += part2;
    }
    determinant -= subtract;
    return determinant;
}

/******************************************************************************
 * Matrix trace
 *****************************************************************************/

float MatrixTrace(float mat[3][3])
{
    int a;
    float sum = 0;
    for (a = 0; a < 3; a++) {
	sum += mat[a][a];
    }
    return sum;
}

/******************************************************************************
 * Matrix transpose
 *****************************************************************************/

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int a, b;
    for (a = 0; a < 3; a++) {
	for (b = 0; b < 3; b++) {
	    result[a][b] = mat[b][a];
	}
    }
}

/******************************************************************************
 * Matrix inverse
 *****************************************************************************/

void MatrixInverse(float mat[3][3], float result[3][3])
{
    float hold[3][3];
    hold[0][0] = (mat[1][1] * mat[2][2])-(mat[1][2] * mat[2][1]);
    hold[0][1] = (mat[1][2] * mat[2][0])-(mat[1][0] * mat[2][2]);
    hold[0][2] = (mat[1][0] * mat[2][1])-(mat[1][1] * mat[2][0]);
    hold[1][0] = (mat[0][2] * mat[2][1])-(mat[0][1] * mat[2][2]);
    hold[1][1] = (mat[0][0] * mat[2][2])-(mat[0][2] * mat[2][0]);
    hold[1][2] = (mat[0][1] * mat[2][0])-(mat[0][0] * mat[2][1]);
    hold[2][0] = (mat[0][1] * mat[1][2])-(mat[0][2] * mat[1][1]);
    hold[2][1] = (mat[0][2] * mat[1][0])-(mat[0][0] * mat[1][2]);
    hold[2][2] = (mat[0][0] * mat[1][1])-(mat[0][1] * mat[1][0]);
    MatrixTranspose(hold, result);
    int i, j;
    float determinant = MatrixDeterminant(mat, 3);
    for (i = 0; i <= 2; i++) { //rows in matrix
	for (j = 0; j <= 2; j++) {//collum in matrix
	    result[i][j] /= determinant;
	}
    }
}

/******************************************************************************
 * Matrix print
 *****************************************************************************/

void MatrixPrint(double mat[3][3])
{
    printf("______________________\n");
    printf("| %.2f | %.2f | %.2f |\n", mat[0][0], mat[0][1], mat[0][2]);
    printf("----------------------\n");
    printf("| %.2f | %.2f | %.2f |\n", mat[1][0], mat[1][1], mat[1][2]);
    printf("----------------------\n");
    printf("| %.2f | %.2f | %.2f |\n", mat[2][0], mat[2][1], mat[2][2]);
    printf("----------------------\n");
}

/******************************************************************************
 * Matrix adjugate
 *****************************************************************************/