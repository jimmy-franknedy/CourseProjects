// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "MatrixMath.h"

// Module-level variables
float zero_matrix[3][3] = {
    {},
    {},
    {}
};

float twobytwo_matrix[2][2] = {
    {},
    {}
};

float solutions_matrix[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

float test1_matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

float test1_determinant = 0;

float test2_matrix[3][3] = {
    {-1, -2, -3},
    {-4, -5, -6},
    {-7, -8, -9}
};

float test2_transpose[3][3] = {
    {-1, -4, -7},
    {-2, -5, -8},
    {-3, -6, -9}
};

float test3_matrix[3][3] = {
    {100, 200, 300},
    {400, 500, 600},
    {700, 800, 900}
};

float test3_transpose [3][3] = {
    {100, 400, 700},
    {200, 500, 800},
    {300, 600, 900}
};

float test4_matrix[3][3] = {
    {99, 199, 299},
    {399, 499, 599},
    {699, 799, 899}
};

float test5_matrix[3][3] = {
    {4, -1, 1}, // 0
    {4, 5, 3}, // 1
    {-2, 0, 0} // 2
};

float test5_submatrix1[2][2] = {
    {5, 3},
    {0, 0}
};

float test5_submatrix2[2][2] = {
    {4, 1},
    {-2, 0}
};

float test5_submatrix3[2][2] = {
    {4, -1},
    {4, 5}
};

float test6_matrix[3][3] = {
    {-4, 1, -1},
    {-4, -5, -3},
    {2, 0, 0}
};

float test7_matrix[3][3] = {
    {000.0009, 000.0008, 000.0007},
    {000.0006, 000.0005, 000.0004},
    {000.0003, 000.0002, 000.0001}
};

float test8_matrix[3][3] = {
    {000.00085, 000.00075, 000.00065},
    {000.00055, 000.00045, 000.00035},
    {000.00025, 000.00015, 000.00005}
};

float test8_transpose [3][3] = {
    {000.00085, 000.00055, 000.00025},
    {000.00075, 000.00045, 000.00015},
    {000.00065, 000.00035, 000.00005}
};

float test9_matrix[3][3] = {
    {0.0000, 0.0000, 0.0000},
    {0.0000, 0.0000, 0.0000},
    {0.0000, 0.0000, 0.0000},
};

float test10_matrix[3][3] = {
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
};

float test11_matrix[3][3] = {
    {0, -1, -2},
    {-3, -4, -5},
    {-6, -7, -8},
};

float test12_matrix[3][3] = {
    {-1, -2, -3},
    {-4, -5, -6},
    {-7, -8, -9},
};

float test13_matrix[3][3] = {
    {-10, 21, 33},
    {4, -5, 67},
    {17, -8, 9},
};
float test13_determinant = 20002;

float test14_matrix[3][3] = {
    {-10, 12, 3.1},
    {4, -5.5, 7},
    {2.4, -7, 9.0},
};
float test14_determinant = -271.28;

float test15_matrix[3][3] = {
    {1, 2, 3},
    {0, 4, 5},
    {1, 0, 6}
};

float test15_inverse[3][3] = {
    {1.0909095, -0.5454555, -0.0909095},
    {0.2272735, 0.1363645, -0.2272735},
    {-0.1818185, 0.0909095, 0.1818185}
};

float test16_matrix[3][3] = {
    {1, 2, 3},
    {0, 1, 5},
    {5, 6, 0}
};

float test16_inverse[3][3] = {
    {-6.0000005, 3.6000005, 1.4000005},
    {5.0000005, -3.0000005, -1.0000005},
    {-1.0000005, 0.8000005, 0.2000005}
};


float test_scalar = 1;
float test_scalar2 = -1;
float test_scalar3 = 0;



int h = 0;
int v = 0;

int h1 = 1;
int v1 = 1;

int h2 = 2;
int v2 = 2;

int MatrixPassCounter_MatrixEquals = 0;
int MatrixPassCounter_MatrixAdd = 0;
int MatrixPassCounter_MatrixMultiply = 0;
int MatrixPassCounter_MatrixScalarAdd = 0;
int MatrixPassCounter_MatrixScalarMultiply = 0;
int MatrixPassCounter_MatrixTrace = 0;
int MatrixPassCounter_MatrixTranspose = 0;
int MatrixPassCounter_MatrixSubmatrix = 0;
int MatrixPassCounter_MatrixDeterminant = 0;
int MatrixPassCounter_MatrixInverse = 0;

int MatrixTrace_solution1 = 15;
int MatrixTrace_solution2 = -15;
int MatrixTrace_solution3 = 0;

int main()
{
    BOARD_Init();

    printf("Beginning Jimmy's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    printf("Output of MatrixPrint(): \n");
    MatrixPrint(test8_matrix);
    printf("Expected output of MatrixPrint(): \n");
    MatrixPrint(test8_matrix);

    //Add more tests here!

    printf("Demonstrating MatrixEquals():\n");
    MatrixEquals(test7_matrix, test7_matrix);
    if (MatrixEquals(test7_matrix, test7_matrix) == 1) {
        MatrixPassCounter_MatrixEquals++;
    }
    MatrixEquals(test7_matrix, test8_matrix);
    if (MatrixEquals(test7_matrix, test8_matrix) == 1) {
        MatrixPassCounter_MatrixEquals++;
    }

    printf("Demonstrating MatrixAdd():\n");
    MatrixAdd(test1_matrix, test2_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test9_matrix) == 1) {
        MatrixPassCounter_MatrixAdd++;
    }
    MatrixAdd(test3_matrix, test10_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test4_matrix) == 1) {
        MatrixPassCounter_MatrixAdd++;
    }

    printf("Demonstrating MatrixMultiply():\n");
    MatrixMultiply(test2_matrix, test10_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test1_matrix) == 1) {
        MatrixPassCounter_MatrixMultiply++;
    }
    MatrixMultiply(test5_matrix, test10_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test6_matrix) == 1) {
        MatrixPassCounter_MatrixMultiply++;
    }

    printf("Demonstrating MatrixScalarAdd():\n");
    MatrixScalarAdd(test_scalar, test2_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test11_matrix)) {
        MatrixPassCounter_MatrixScalarAdd++;
    }
    MatrixScalarAdd(test_scalar2, test3_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test4_matrix)) {
        MatrixPassCounter_MatrixScalarAdd++;
    }

    printf("Demonstrating MatrixScalarMultiply():\n");
    MatrixScalarMultiply(test_scalar, test2_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test12_matrix)) {
        MatrixPassCounter_MatrixScalarMultiply++;
    }
    MatrixScalarMultiply(test_scalar3, test7_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test9_matrix)) {
        MatrixPassCounter_MatrixScalarMultiply++;
    }

    printf("Demonstrating MatrixTrace():\n");
    MatrixTrace(test1_matrix);
    if (MatrixTrace(test1_matrix) == MatrixTrace_solution1) {
        MatrixPassCounter_MatrixTrace++;
    }
    MatrixTrace(test2_matrix);
    if (MatrixTrace(test2_matrix) == MatrixTrace_solution2) {
        MatrixPassCounter_MatrixTrace++;
    }
    MatrixTrace(test9_matrix);
    if (MatrixTrace(test9_matrix) == MatrixTrace_solution3) {
        MatrixPassCounter_MatrixTrace++;
    }

    printf("Demonstrating MatrixTranspose():\n");
    MatrixTranspose(test2_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test2_transpose)) {
        MatrixPassCounter_MatrixTranspose++;
    }
    MatrixTranspose(test3_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test3_transpose)) {
        MatrixPassCounter_MatrixTranspose++;
    }
    MatrixTranspose(test8_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test8_transpose)) {
        MatrixPassCounter_MatrixTranspose++;
    }

    printf("Demonstrating MatrixSubmatrix():\n");
    MatrixSubmatrix(h, v, test5_matrix, twobytwo_matrix);
    int counter = 0; // Counter is used to see if the current element in the array matches
    int totalArea = 4; // Counter is used to hold the total number of elements in a 2x2 matrix
    float value1; // Counter used to account for the current element in matrix mat1
    float value2; // Counter used to account for the current element in matrix mat2
    float difference; // Counter used to calculate the return's proximity
    int vertical = 0;
    for (vertical = 0; vertical < 2; vertical++) {
        int horizontal = 0;
        for (horizontal = 0; horizontal < 2; horizontal++) {
            value1 = twobytwo_matrix[vertical][horizontal];
            value2 = test5_submatrix1[vertical][horizontal];
            difference = value1 - value2;
            if (difference < 0) {
                difference *= -1;
            }
            if (difference <= FP_DELTA) {
                counter++;
            }
        }
    }
    if (counter == totalArea) {
        MatrixPassCounter_MatrixSubmatrix++;
    }

    MatrixSubmatrix(h1, v1, test5_matrix, twobytwo_matrix);
    vertical -= vertical;
    counter -= counter;
    for (vertical = 0; vertical < 2; vertical++) {
        int horizontal = 0;
        for (horizontal = 0; horizontal < 2; horizontal++) {
            value1 = twobytwo_matrix[vertical][horizontal];
            value2 = test5_submatrix2[vertical][horizontal];
            difference = value1 - value2;
            if (difference < 0) {
                difference *= -1;
            }
            if (difference <= FP_DELTA) {
                counter++;
            }
        }
    }
    if (counter == totalArea) {
        MatrixPassCounter_MatrixSubmatrix++;
    }

    MatrixSubmatrix(h2, v2, test5_matrix, twobytwo_matrix);
    vertical -= vertical;
    counter -= counter;
    for (vertical = 0; vertical < 2; vertical++) {
        int horizontal = 0;
        for (horizontal = 0; horizontal < 2; horizontal++) {
            value1 = twobytwo_matrix[vertical][horizontal];
            value2 = test5_submatrix3[vertical][horizontal];
            difference = value1 - value2;
            if (difference < 0) {
                difference *= -1;
            }
            if (difference <= FP_DELTA) {
                counter++;
            }
        }
    }
    if (counter == totalArea) {
        MatrixPassCounter_MatrixSubmatrix++;
    }

    printf("Demonstrating MatrixDeterminant():\n");
    if (MatrixDeterminant(test1_matrix) == test1_determinant) {
        MatrixPassCounter_MatrixDeterminant++;
    }
    if (MatrixDeterminant(test13_matrix) == test13_determinant) {
        MatrixPassCounter_MatrixDeterminant++;
    }
    if (MatrixDeterminant(test14_matrix) == test14_determinant) {
        MatrixPassCounter_MatrixDeterminant++;
    }

    printf("Demonstrating MatrixInverse():\n");
    MatrixInverse(test15_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test15_inverse)) {
        MatrixPassCounter_MatrixInverse++;
    }
    MatrixInverse(test16_matrix, solutions_matrix);
    if (MatrixEquals(solutions_matrix, test16_inverse)) {
        MatrixPassCounter_MatrixInverse++;
    }
    printf("Final Results: \n");
    printf("PASSED (%d/2): MatrixEquals()\n", MatrixPassCounter_MatrixEquals);
    printf("PASSED (%d/2): MatrixAdd()\n", MatrixPassCounter_MatrixAdd);
    printf("PASSED (%d/2): MatrixMultiply()\n", MatrixPassCounter_MatrixMultiply);
    printf("PASSED (%d/2): MatrixScalarAdd()\n", MatrixPassCounter_MatrixScalarAdd);
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", MatrixPassCounter_MatrixScalarMultiply);
    printf("PASSED (%d/3): MatrixTrace()\n", MatrixPassCounter_MatrixTrace);
    printf("PASSED (%d/3): MatrixTranspose()\n", MatrixPassCounter_MatrixTranspose);
    printf("PASSED (%d/3): MatrixSubmatrix()\n", MatrixPassCounter_MatrixSubmatrix);
    printf("PASSED (%d/3): MatrixDeterminant()\n", MatrixPassCounter_MatrixDeterminant);
    printf("PASSED (%d/2): MatrixInverse()\n", MatrixPassCounter_MatrixInverse);
    printf("--Test Complete--");
    while (1);

}