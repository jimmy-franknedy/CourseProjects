/*
 * File:   stack.c
 * Author: jfrankne [jfrankne@ucsc.edu]
 *
 * Created on July 15, 2019, 12:42 PM
 */
#include "BOARD.h"
#include "stack.h"
#include "stdio.h"

void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value)
{
    if (stack->currentItemIndex >= STACK_SIZE - 1 || stack->initialized != 1) {
        return STANDARD_ERROR;
    } else {
        stack->currentItemIndex++;
        stack->stackItems[stack->currentItemIndex] = value;
        return SUCCESS;
    }
}

int StackPop(struct Stack *stack, double *value)
{
    if (stack->currentItemIndex < 0 || stack->initialized != 1) {
        return STANDARD_ERROR;
    } else {
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex--;
        return SUCCESS;
    }
}

int StackIsEmpty(const struct Stack *stack)
{
    if (stack->currentItemIndex == -1 && stack->initialized == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackIsFull(const struct Stack *stack)
{
    if (stack->currentItemIndex == STACK_SIZE - 1 && stack->initialized == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized != 1) {
        return SIZE_ERROR;
    } else {
        int result = stack->currentItemIndex;
        result++;
        return result;
    }
}
