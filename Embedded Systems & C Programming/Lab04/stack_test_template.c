// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "stack.h"
#include "stdio.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning jfrankne's stack test harness: ######\n\n");

    //What follows is starter code.  You will need to modify it!
    int StackInit_PassCounter = 0;
    int StackPush_PassCounter = 0;
    int StackPop_PassCounter = 0;
    int StackIsEmpty_PassCounter = 0;
    int StackIsFull_PassCounter = 0;
    int StackGetSize_PassCounter = 0;

    printf("Test prommpts:\n");

    //test StackInit():
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack;
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        StackInit_PassCounter++;
    }
    struct Stack stackFail;
    if (stackFail.currentItemIndex != -1) {
        StackInit_PassCounter++;
    }

    //test StackPush():
    printf("Does StackPush() push an element onto the stack appropriately?\n");
    struct Stack stack2;
    StackInit(&stack2);
    stack2.currentItemIndex = 18;
    if (StackPush(&stack2, 12) == SUCCESS) {
        StackPush_PassCounter++;
    }
    struct Stack stack2Fail;
    stack2Fail.currentItemIndex = 19;
    if (StackPush(&stack2Fail, 12) == STANDARD_ERROR) {
        StackPush_PassCounter++;
    }

    //test StackPop():
    printf("Does StackPop() pop an element off the stack appropriately?\n");
    struct Stack stack3;
    StackInit(&stack3);
    stack3.currentItemIndex = 0;
    double value = 0;
    if (StackPop(&stack3, &value) == SUCCESS) {
        StackPop_PassCounter++;
    }
    struct Stack stack3Fail;
    StackInit(&stack3Fail);
    stack3Fail.currentItemIndex = -1;
    double valueFail = 12;
    if (StackPop(&stack3Fail, &valueFail) == STANDARD_ERROR) {
        StackPop_PassCounter++;
    }

    //test StackIsEmpty():
    printf("Does StackIsEmpty() check to see if the stack is empty appropriately?\n");
    struct Stack stack4;
    StackInit(&stack4);
    if (StackIsEmpty(&stack4) == TRUE) {
        StackIsEmpty_PassCounter++;
    }
    struct Stack stack4Fail;
    StackInit(&stack4Fail);
    stack4Fail.currentItemIndex = STACK_SIZE - 1;
    if (StackIsEmpty(&stack4Fail) == FALSE) {
        StackIsEmpty_PassCounter++;
    }


    //test StackIsFull():
    printf("Does StackIsFull() check to see if the stack is full appropriately?\n");
    struct Stack stack5;
    StackInit(&stack5);
    stack5.currentItemIndex = STACK_SIZE - 1;
    if (StackIsFull(&stack5) == TRUE) {
        StackIsFull_PassCounter++;
    }
    struct Stack stack5Fail;
    StackInit(&stack5Fail);
    if (StackIsFull(&stack5Fail) == FALSE) {
        StackIsFull_PassCounter++;
    }

    //test StackGetSize():
    printf("Does StackGetSize() check for active elements appropriately?\n");
    struct Stack stack6;
    StackInit(&stack6);
    stack6.currentItemIndex = 12;
    if (StackGetSize(&stack6) == 13) {
        StackGetSize_PassCounter++;
    }
    struct Stack stack6Fail;
    StackInit(&stack6Fail);
    stack6Fail.currentItemIndex = 8 * 1;
    if (StackGetSize(&stack6Fail) == 9) {
        StackGetSize_PassCounter++;
    }

    printf("\nFinal Results:\n");
    printf("PASSED (%d/2): StackInit()\n", StackInit_PassCounter);
    printf("PASSED (%d/2): StackPush() \n", StackPush_PassCounter);
    printf("PASSED (%d/2): StackPop()\n", StackPop_PassCounter);
    printf("PASSED (%d/2): StackIsEmpty()\n", StackIsEmpty_PassCounter);
    printf("PASSED (%d/2): StackIsFull()\n", StackIsFull_PassCounter);
    printf("PASSED (%d/2): StackGetSize()\n", StackGetSize_PassCounter);

    while (1);
    return 0;
}