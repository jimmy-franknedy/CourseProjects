

// Skip to content
// Using Gmail with screen readers

// 1 of 28,320
// The folders
// Inbox
// x

// jo taco
// Attachments
// 9:34 AM (14 minutes ago)
// to me


// 6 Attachments

#include <stdio.h>
#include "BOARD.h"
#include "MatrixMath.h"

/******************************************************************************
 * Matrix Display:
 *****************************************************************************/
/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(float mat[3][3]){
    printf("\nOutput Of MatrixPrint():\n");
    printf(" _____________________\n");
    printf("|%03.4f|%03.4f|%03.4f|\n",mat[0][0],mat[0][1],mat[0][2]);
    printf(" --------------------\n");
    printf("|%03.4f|%03.4f|%03.4f|\n",mat[1][0],mat[1][1],mat[1][2]);
    printf(" --------------------\n");
    printf("|%03.4f|%03.4f|%03.4f|\n",mat[2][0],mat[2][1],mat[2][2]);
    printf(" --------------------\n");
}

/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of the corresponding element of mat2,  otherwise return FALSE
 * Neither mat1 nor mat2 is modified by this function.
 */
//FP_DELTA 0.0001
int MatrixEquals(float mat1[3][3], float mat2[3][3]){
    int i, j;
    for(i = 0; i<DIM; i++){
        for (j = 0; j<DIM; j++){
            if(mat1[i][j]>mat2[i][j]+FP_DELTA || mat1[i][j]<mat2[i][j]-FP_DELTA){
                return FALSE;
            }
        }
    }
    return TRUE;
}

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]){
int i, j;
    for(i = 0; i<DIM; i++){
        for (j = 0; j<DIM; j++){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }  
}

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    for(int horizontal = 0; horizontal < DIM; horizontal++)
    {
        for(int vertical = 0; vertical < DIM; vertical++)
        {
            for(int sum = 0 ; sum < DIM; sum++)
            {
                sum += mat1[horizontal][sum] * mat2[sum][vertical];

            }
        }
    }
}

/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]){
int i, j;
    for(i = 0; i<DIM; i++){
        for (j = 0; j<DIM; j++){
            result[i][j] = mat[i][j] + x;
        }
    } 
}
/**
 * MatrixScalarAdd performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]){
    int i, j;
    for(i = 0; i<DIM; i++){
        for (j = 0; j<DIM; j++){
            result[i][j] = mat[i][j] * x;
        }
    }
}

/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
float MatrixTrace(float mat[3][3]){
    float trace = 0;
    for(int e = 0; e<DIM; e++){
        trace += mat[e][e];
        //trace += mat[i][i];
        // return trace;
    }
    
    // Note: return will exit the function (in this case it will elave MatrixTrace) and return a value
    // when you are returning something from a function it should be the last thing you do, so if you wanna check the value
    // of your trace, print it BEFORE you return and make sure you use the right parameters, cause I'm not sure if %d is
    // the case for floats :o

    //printf("\n%d",trace);
    return trace;
}


/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[3][3], float result[3][3]){
    int i, j;
    for(i = 0; i<DIM; i++){
        for (j = 0; j<DIM; j++){
            result[i][j] = mat[i][j];
        }
    }
}

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]);

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[3][3]);


/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: none
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[3][3], float result[3][3]);

MatrixMath.c
Displaying MatrixMath.c. 