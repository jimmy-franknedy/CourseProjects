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
#include "rpn.h"
#include "stack.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main()
{
    BOARD_Init();

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

#define number0 0    
#define number1 1
#define number2 2
#define number3 3
#define number4 4
#define number5 5
#define number6 6

    printf("Welcome to jfrankne'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {
        int errorCheck = 0;
        printf("\nEnter floats and + - / * in RPN format:\n");
        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        while (getchar() != '\n');
        errorCheck = RPN_Evaluate(rpn_sentence, &result);
        printf("error: %d\n", errorCheck);
        if (errorCheck == number0) {
            printf("RPN Calculation = %.2f\n", result);
        }
        if (errorCheck == number1) {
            printf("RPN Calculation Error: Stack cannot push value!\n");
        }
        if (errorCheck == number2) {
            printf("RPN Calculation Error: Stack cannot pull value!\n");
        }
        if (errorCheck == number3) {
            printf("RPN Calculation Error: Invalid Input!\n");
        }
        if (errorCheck == number4) {
            printf("RPN Calculation Error: Can't divide by 0!\n");
        }
        if (errorCheck == number5) {
            printf("RPN Calculation Error: Stack has no too few values to pull from!\n");
        }
        if (errorCheck == number6) {
            printf("RPN Calculation Error: Stack has too many leftover elements!\n");
        }
        result *= 0;
        fflush(stdin);
    }
    while (1);
}
