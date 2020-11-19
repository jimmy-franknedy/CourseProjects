/*
 * File:   stack.c
 * Author: jfrankne [jfrankne@ucsc.edu]
 *
 * Created on July 15, 2019, 12:42 PM
 */

// Include header files
#include "BOARD.h"
#include "stdio.h"
#include "rpn.h"
#include "stack.h"
#include <string.h>

#define value0 0    
#define value1 1
#define value2 2
#define value3 3
#define value4 4
#define value5 5
#define value6 6
#define add '+'
#define sub '-'
#define mul '*'
#define div '/'
#define zero 0
#define space_numb 46
#define period 48

// Helper Function Prototype
int checkOperator(char *tokenString);
int checkInput(char *tokenString, int stringLength);

int RPN_Evaluate(char * rpn_string, double * result)
{
    struct Stack stack;
    StackInit(&stack);
    int size_rpnString = strlen(rpn_string);
    char *space = " ";
    char *null = '\0';
    char *firstToken = strtok(rpn_string, " ");
    if (firstToken == space || firstToken == (null)) 
    {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    if (checkOperator(firstToken) == value1 ||
            checkOperator(firstToken) == value2 ||
            checkOperator(firstToken) == value3 ||
            checkOperator(firstToken) == value4) {
        return RPN_ERROR_STACK_UNDERFLOW;
    }
    if (checkInput(firstToken, size_rpnString) == value1) {
        double convertedToFloat = atof(firstToken);
        if (StackPush(&stack, convertedToFloat) != SUCCESS) {
            return RPN_ERROR_STACK_OVERFLOW;
        }
    } else {
        return RPN_ERROR_INVALID_TOKEN;
    }
    char *currentToken;
    while (currentToken != NULL) {
        currentToken = strtok(NULL, " ");
        if (currentToken == NULL) {
            break;
        }
        if (checkOperator(currentToken) > value0) {
            double operand1; // First value in stack
            double operand2; // Second value in stack
            double operand3; // Result of operand1 [operator] operand2
            if (StackPop(&stack, &operand1) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&stack, &operand2) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (checkOperator(currentToken) == value1) {
                operand3 = operand2 + operand1;
            } else if (checkOperator(currentToken) == value2) {
                operand3 = operand2 - operand1;
            } else if ((checkOperator(currentToken) == value3)) {
                operand3 = operand2 * operand1;
            } else if (checkOperator(currentToken) == value4) {
                if (operand1 == value0) {
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                } else {
                    operand3 = operand2 / operand1;
                }
            }
            if (StackPush(&stack, operand3) != SUCCESS) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
        } else if (checkInput(currentToken, size_rpnString) == value1) {
            double convertedToFloat = atof(currentToken);
            if (StackPush(&stack, convertedToFloat) != SUCCESS) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
        } else if (checkInput(currentToken, size_rpnString) == value1
                && StackIsEmpty(&stack) == FALSE) {
            return RPN_ERROR_INVALID_TOKEN;
        }
    }
    if (StackGetSize(&stack) == value1) {
        double operand4 = value0;
        StackPop(&stack, &operand4);
        *result = (double) operand4;
        printf("Popping off result & returning it!\n");
        return RPN_NO_ERROR;
    }
    if (StackGetSize(&stack) < value1) {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    if (StackGetSize(&stack) > value1) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    return RPN_NO_ERROR; // Final Checkpoint. States that RPN_Evaluate was SUCCESS.
}

int checkOperator(char *tokenString)
// Checks if the current stringToken is an operator
{
    char tokenCheck = *tokenString;
    if (tokenCheck == add && ((strlen(tokenString)) == 1)) {
        return value1;
    } else if (tokenCheck == sub && ((strlen(tokenString)) == 1)) {
        return value2;
    } else if (tokenCheck == mul && ((strlen(tokenString)) == 1)) {
        return value3;
    } else if (tokenCheck == div && ((strlen(tokenString)) == 1)) {
        return value4;
    } else {
        return value0;
    }
}

int checkInput(char *tokenString, int stringLength)
// Checks if the input is a value numeric input
{
    char stringValue[stringLength];
    char string2Value[stringLength];
    double floatValue = atof(tokenString);
    sprintf(stringValue, "%f", floatValue);
    sprintf(string2Value, "%s", tokenString);
    int stringCompare = strcmp(stringValue, string2Value);
    if (stringCompare == zero ||
            stringCompare == space_numb ||
            stringCompare == period) {
        return RPN_ERROR_STACK_OVERFLOW;
    }
    return RPN_NO_ERROR;
}