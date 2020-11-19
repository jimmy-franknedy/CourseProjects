/*
 * File:   MatrixMath.c
 * Author: Jimmy Franknedy
 * email:  jfrankne@ucsc.edu
 *
 * Created on July 9, 2019, 1:DIMDIM PM
 */

#include "xc.h"

// Added additional libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MatrixMath.h"

void MatrixPrint(float mat[DIM][DIM])
{
    printf("____________________________\n");
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            printf("|%8.4f", (double) mat[horizontal][vertical]);
        }
        printf("|");
        printf("\n");
    }
    printf("____________________________\n");
}

int MatrixEquals(float mat1[DIM][DIM], float mat2[DIM][DIM])
{
    int counter = 0; // Counter is used to see if the current element in the array matches
    int total = DIM * DIM;
    float value1; // Counter used to account for the current element in matrix mat1
    float value2; // Counter used to account for the current element in matrix mat2
    float difference; // Counter used to calculate the return's proximity
    int validity = 0; // Counter used to indicate if the ma1 == mat2
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat1[horizontal][vertical];
            //printf("value1: %f\n", (double)value1);
            value2 = mat2[horizontal][vertical];
            //printf("value2: %f\n", (double)value2);
            difference = value1 - value2;
            // TESTING TO SEE DIFFERENCE
            //printf("value1(%8.4f) - value2(%8.4f) = (%8.4f)\n", (double) value1, (double) value2, (double) difference);

            if (difference < 0) {
                difference *= -1;
            }
            if (difference <= FP_DELTA) {
                counter++;
            }
        }
    }
    if (counter == total) {
        // Condition if both matrices match
        validity++;
    }
    return validity;
}

void MatrixAdd(float mat1[DIM][DIM], float matDIM[DIM][DIM], float result[DIM][DIM])
{
    float sum = 0;
    float value1; // Counter used to account for the current element in matrix mat1
    float valueDIM; // Counter used to account for the current element in matrix matDIM
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat1[horizontal][vertical];
            valueDIM = matDIM[horizontal][vertical];
            sum += value1;
            sum += valueDIM;
            result[horizontal][vertical] = sum;
            sum *= 0;
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    //MatrixPrint(result);
}

void MatrixMultiply(float mat1[DIM][DIM], float mat2[DIM][DIM], float result[DIM][DIM])
{
    float product = 1;
    float value1; // Counter used to account for the current element in matrix mat1
    float value2; // Counter used to account for the current element in matrix mat2
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat1[horizontal][vertical];
            value2 = mat2[horizontal][vertical];
            product *= value1;
            product *= value2;
            result[horizontal][vertical] = product;
            product /= product;
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    //MatrixPrint(result);
}

void MatrixScalarAdd(float x, float mat[DIM][DIM], float result[DIM][DIM])
{
    float sum = 0; // Counter used to calculate the scalar addition for an element in the matrix
    float value1; // Counter used to account for the current element in matrix mat
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat[horizontal][vertical];
            sum += value1;
            sum += x;
            result[horizontal][vertical] = sum;
            sum *= 0;
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    // MatrixPrint(result);
}

void MatrixScalarMultiply(float x, float mat[DIM][DIM], float result[DIM][DIM])
{
    float product = 1; // Counter used to calculate the scalar addition for an element in the matrix
    float value1; // Counter used to account for the current element in matrix mat
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat[horizontal][vertical];
            product *= value1;
            product *= x;
            result[horizontal][vertical] = product;
            product /= product;
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    //MatrixPrint(result);
}

float MatrixTrace(float mat[DIM][DIM])
{
    float value1;    // Counter used to account for the current element in matrix mat
    float trace = 0; // Counter used to calculate the trace of the matrix
    int horizontal = 0;
    int vertical = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        value1 = mat[horizontal][vertical];
        trace += value1;
        vertical++;
    }
    // TESTING TO SEE THE VALUE OF TRACE * REMOVE
    //printf("Trace: %f\n", (double) trace);

    return trace;
}

void MatrixTranspose(float mat[DIM][DIM], float result[DIM][DIM])
{
    float value1; // Counter used to account for the current element in matrix mat
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat[horizontal][vertical];
            result[vertical][horizontal] = value1;
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    // MatrixPrint(result);
}

void MatrixSubmatrix(int i, int j, float mat[DIM][DIM], float result[DIM - 1][DIM - 1])
{
    float value1; // Counter used to account for the current element in matrix mat
    int horizontal2 = 0; // Counter used to navigate through array 'result'
    int vertical2 = 0; // Counter used to navigate through array 'result'
    int horizontal = 0;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = mat[horizontal][vertical];
            if (horizontal == i || vertical == j) {
                // Pseudocode: Don't do anything to result
                //             if value1 is in the dedicated row or colum
                //             set by the user.
                continue;
            } else {
                // Pseudocode: Input the value into result
                //             if value1 is NOT in the dedicated row or colum
                //             set by the user
                if (horizontal2 == DIM - 1) {
                    vertical2++;
                    horizontal2 -= horizontal2;
                    result[vertical2][horizontal2] = value1;
                    horizontal2++;
                } else {
                    result[vertical2][horizontal2] = value1;
                    horizontal2++;
                }
            }
        }
    }
    // TESTING TO SEE CALCULATION * REMOVE *
    // Matrix2Print(result);
}

float MatrixDeterminant(float mat[DIM][DIM])
{
    int horizontal = 0;
    int vertical = 0;
    float negative = 1;
    float selected = 0; // Counter used to hold elements of arrays needed for final calculation
    float value1 = 0; // Counter used to hold elements of arrays needed for final calculation
    float value2 = 0; // Counter used to hold elements of arrays needed for final calculation
    float product1; // Calculates the left-diagonal product in microMatrix     
    float product2; // Calculates the right-diagonal product in micrMatrix
    float productDIM; // Calculates the product between difference and selected element in mat
    float difference; // Calculates the difference between product1 & product2
    float sum = 0; // Calculates the sum between the different differences.
    float microMatrix[2][2] = {
        {},
        {}
    };

    for (vertical = 0; vertical < DIM; vertical++) {
        selected = mat[horizontal][vertical];

        // DISPLAYS VALUE OF selected *REMOVE *
        // printf("mat[%d][%d] = (selected)%f\n", a, b, (double) selected);

        if (DIM == 2) {
            value1 = microMatrix[0][0];
            value2 = microMatrix[1][1];
            product1 = value1 * value2;
            value1 = microMatrix[0][1];
            value2 = microMatrix[1][0];
            product2 = value1 * value2;
            difference = product1 - product2;
            sum = difference + 0;
        }

        if (DIM == 3) {
            MatrixSubmatrix(horizontal, vertical, mat, microMatrix);
            value1 = microMatrix[0][0];
            value2 = microMatrix[1][1];
            product1 = value1 * value2;
            value1 = microMatrix[0][1];
            value2 = microMatrix[1][0];
            product2 = value1 * value2;
            difference = product1 - product2;
            productDIM = selected * difference * negative;
            sum += productDIM;
            negative *= -1;
        }
        //TESTING TO SEE sum * REMOVE *
        //printf("sum: %f\n", (double) sum); 
    }

    // TESTING TO SEE final sum * REMOVE *
    //printf("Determinant: %f\n", (double) sum);
    return sum;
}

void MatrixInverse(float mat[DIM][DIM], float result[DIM][DIM])
{
    int horizontal2 = 0;
    int vertical2 = 0;
    int horizontal = 0;
    float negative = 1;
    float value1 = 0; // Counter used to hold elements of arrays needed for final calculation
    float value2 = 0; // Counter used to hold elements of arrays needed for final calculation
    float product1; // Calculates the left-diagonal product in microMatrix     
    float product2; // Calculates the right-diagonal product in micrMatrix
    float productDIM = 0; // Calculates the product between difference and selected element in mat
    float difference; // Calculates the difference between product1 & product2
    float dividend = 0; // Counter used to calculate (1/determinentValue) * Transpose of Cofactor M.
    float microMatrix[2][2] = {
        {},
        {}
    };
    float cofactorMatrix[3][3] = {
        {},
        {},
        {}
    };

    float transposeMatrix[3][3] = {
        {},
        {},
        {}
    };

    // CALCULATING COFACTOR OF mat
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            MatrixSubmatrix(horizontal, vertical, mat, microMatrix);
            value1 = microMatrix[0][0];
            value2 = microMatrix[1][1];
            product1 = value1 * value2;
            value1 = microMatrix[0][1];
            value2 = microMatrix[1][0];
            product2 = value1 * value2;
            difference = product1 - product2;
            productDIM = difference * negative;
            if (horizontal2 == DIM) {
                //printf("[(h2,v2)]:(%d,%d)\n", (int)horizontal2, (int)vertical2);
                vertical2++;
                horizontal2 -= horizontal2;
                cofactorMatrix[horizontal2][vertical2] = productDIM;
                horizontal2++;
            } else {
                cofactorMatrix[horizontal2][vertical2] = productDIM;
                //printf("[(h2,v2)]:(%d,%d)\n", (int)horizontal2, (int)vertical2);
                horizontal2++;
            }
            negative *= -1;
            //printf("[(h,v)]:(%d,%d)\n", (int)horizontal, (int)vertical);
        }
    }

    // CALCULATING TRANSPOSE of COFACTOR of mat
    MatrixTranspose(cofactorMatrix, transposeMatrix);

    // CALCULATING (1/DETERMINANT) * (TRANSPOSE OF COFACTOR of mat)
    horizontal2 -= horizontal2;
    vertical2 -= vertical2;
    for (horizontal = 0; horizontal < DIM; horizontal++) {
        int vertical = 0;
        for (vertical = 0; vertical < DIM; vertical++) {
            value1 = transposeMatrix[horizontal][vertical];
            dividend = value1 / MatrixDeterminant(mat);
            if (horizontal2 == DIM) {
                vertical2++;
                horizontal2 -= horizontal2;
                result[horizontal2][vertical2] = dividend;
                //printf("(%d,%d): %f\n", (int) horizontal2, (int) vertical2, (double) dividend);
                horizontal2++;
            } else {
                result[horizontal2][vertical2] = dividend;
                //printf("(%d,%d): %f\n", (int) horizontal2, (int) vertical2, (double) dividend);
                horizontal2++;
            }
            negative *= -1;
        }
    }
}
