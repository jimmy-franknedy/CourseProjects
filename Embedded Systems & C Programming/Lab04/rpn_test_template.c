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
#include "stdio.h"

int main()
{
    BOARD_Init();
    double testPass_counter = 0;
    double testTotal_counter = 0;
    int test_RPN_NO_ERROR = 0;
    int test_RPN_ERROR_STACK_OVERFLOW = 0;
    int test_RPN_ERROR_STACK_UNDERFLOW = 0;
    int test_RPN_ERROR_INVALID_TOKEN = 0;
    int test_RPN_ERROR_DIVIDE_BY_ZERO = 0;
    int test_RPN_ERROR_TOO_FEW_ITEMS_REMAIN = 0;
    int test_RPN_ERROR_TOO_MANY_ITEMS_REMAIN = 0;
    
    int error = 0;

    printf("\n###### Beginning jfrankne's rpn test harness: ####\n\n");

    char testnull[] = " ";
    double resultnull;
    printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", testnull);
    error = RPN_Evaluate(testnull, &resultnull);
    testTotal_counter++;
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_TOO_FEW_ITEMS_REMAIN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n");
    }
    
    char test0[] = "1 1 1 1 1 + + + + ";
    double result0;
    double expected0 = 5;
    printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    testTotal_counter++;
    if (error == RPN_NO_ERROR) {
        printf("   \nFailed, RPN_Evaluate produced an error\n\n");
        printf("Error: %d\n", error);
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else if (result0 != expected0) {
        printf("   \nFailed, expected = %f , result = %f\n\n", expected0, result0);
    } else {
        printf("Success!\n\n");
        testPass_counter++;
        test_RPN_NO_ERROR++;
    }
    
    char test1[] = "16.5 3.5 + 1 * ";
    double result1;
    double expected1 = 20;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result1);
    testTotal_counter++;
    if (error == RPN_NO_ERROR) {
        printf("   \nFailed, RPN_Evaluate produced an error\n\n");
        printf("Error: %d\n", error);
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else if (result1 != expected1) {
        printf("   \nFailed, expected = %f , result = %f\n\n", expected1, result1);
    } else {
        printf("Success!\n\n");
        testPass_counter++;
        test_RPN_NO_ERROR++;
    }

    char test2[] = "17 2 * 1 * 5 5 + + ";
    double result2;
    double expected2 = 44;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result2);
    testTotal_counter++;
    if (error == RPN_NO_ERROR) {
        printf("   \nFailed, RPN_Evaluate produced an error\n\n");
        printf("Error: %d\n", error);
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else if (result2 != expected2) {
        printf("   \nFailed, expected = %f , result = %f\n\n", expected2, result2);
    } else {
        printf("Success!\n\n");
        testPass_counter++;
        test_RPN_NO_ERROR++;
    }
    
    char test3[] = "6 6 * 9 / 10 * 3 - ";
    double result3;
    double expected3 = 37;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result3);
    testTotal_counter++;
    if (error == RPN_NO_ERROR) {
        printf("   \nFailed, RPN_Evaluate produced an error\n\n");
        printf("Error: %d\n", error);
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else if (result3 != expected3) {
        printf("   \nFailed, expected = %f , result = %f\n\n", expected3, result3);
    } else {
        printf("Success!\n\n");
        testPass_counter++;
        test_RPN_NO_ERROR++;
    }
 
    char test4[] = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
    double result4;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test4);
    error = RPN_Evaluate(test4, &result4);
    testTotal_counter++;
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_STACK_OVERFLOW++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_STACK_OVERFLOW");
    }
    
    char test5[] = "-2 -23 -33 -14 -44 -5.5 -66 -72 -23 -44 -12 -14 -16 -65 -33 -79 -100 -20 0 1 1 1 1 1 1 1 1";
    double result5;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test5);
    error = RPN_Evaluate(test5, &result5);
    testTotal_counter++;
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_STACK_OVERFLOW++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_STACK_OVERFLOW");
    }
    
    char test6[] = "3 / 9";
    double result6;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test6);
    error = RPN_Evaluate(test6, &result6);
    testTotal_counter++;
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_STACK_UNDERFLOW++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_STACK_UNDERFLOW");
    }
    
    char test7[] = "7 * 3";
    double result7;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test7);
    error = RPN_Evaluate(test7, &result7);
    testTotal_counter++;
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_STACK_UNDERFLOW++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_STACK_UNDERFLOW");
    }
    
    char test8[] = "g";
    double result8;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test8);
    error = RPN_Evaluate(test8, &result8);
    testTotal_counter++;
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_INVALID_TOKEN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_INVALID_TOKEN");
    }
    
    char test9[] = "1.g";
    double result9;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test9);
    error = RPN_Evaluate(test9, &result9);
    testTotal_counter++;
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_INVALID_TOKEN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_INVALID_TOKEN");
    }
    
    char test10[] = "-2g.2";
    double result10;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test10);
    error = RPN_Evaluate(test10, &result10);
    testTotal_counter++;
    //printf("testTotal_counter++\n");
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_INVALID_TOKEN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_INVALID_TOKEN");
    }
    
    char test11[] = "240 0 /";
    double result11;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test11);
    error = RPN_Evaluate(test11, &result11);
    testTotal_counter++;
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_DIVIDE_BY_ZERO++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_DIVIDE_BY_ZERO");
    }
    
    char test12[] = "1 1 1 1 1 1 + + +";
    double result12;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test12);
    error = RPN_Evaluate(test12, &result12);
    testTotal_counter++;
    //printf("testTotal_counter++\n");
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_TOO_MANY_ITEMS_REMAIN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_TOO_MANY_ITEMS_REMAIN");
    }
    
    char test13[] = "16 15 - 1";
    double result13;
     printf("\n__________________________________________________\n\n");
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test13);
    error = RPN_Evaluate(test13, &result13);
    testTotal_counter++;
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("   \nSuccess! RPN_Evaluate produced an error\n");
        testPass_counter++;
        test_RPN_ERROR_TOO_MANY_ITEMS_REMAIN++;
        switch (error) {
        case 1: printf("RPN_ERROR_STACK_OVERFLOW\n\n");
            break;
        case 2: printf("RPN_ERROR_STACK_UNDERFLOW\n\n");
            break;
        case 3: printf("RPN_ERROR_INVALID_TOKEN\n\n");
            break;
        case 4: printf("RPN_ERROR_DIVIDE_BY_ZERO\n\n");
            break;
        case 5: printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n\n");
            break;
        case 6: printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n\n");
            break;
        default: printf("RPN_NO_ERROR\n\n");
            break;
        }
    } else {
        printf("   \nFailed expected: RPN_ERROR_TOO_MANY_ITEMS_REMAIN");
    }

    
    // Testing Conclusion
    double testPercentage = testPass_counter / testTotal_counter;
    testPercentage *= 100;

    printf("\n__________________________________________________\n\n");
    printf("Diagnostics:\n");
    printf("(PASSED (%d/4): RPN_NO_ERROR()\n",test_RPN_NO_ERROR);
    printf("(PASSED (%d/2): RPN_ERROR_STACK_OVERFLOW()\n",test_RPN_ERROR_STACK_OVERFLOW);
    printf("(PASSED (%d/2): RPN_ERROR_STACK_UNDERFLOW()\n",test_RPN_ERROR_STACK_UNDERFLOW);
    printf("(PASSED (%d/3): RPN_ERROR_INVALID_TOKEN()\n",test_RPN_ERROR_INVALID_TOKEN);
    printf("(PASSED (%d/1): RPN_ERROR_DIVIDE_BY_ZERO()\n",test_RPN_ERROR_DIVIDE_BY_ZERO);
    printf("(PASSED (%d/1): RPN_ERROR_TOO_FEW_ITEMS_REMAIN()\n",
            test_RPN_ERROR_TOO_FEW_ITEMS_REMAIN);
    printf("(PASSED (%d/2): RPN_ERROR_TOO_MANY_ITEMS_REMAIN()\n",
            test_RPN_ERROR_TOO_MANY_ITEMS_REMAIN);
    printf("\n--------------------------------------------------\n\n");
    printf("Final Results:\n");
    printf("Total Tests: %d\n", (int) testTotal_counter);
    printf("Tests Passed: %d\n", (int) testPass_counter);
    printf("Completion: %.2f%%\n", (double) testPercentage);
     printf("\n__________________________________________________\n\n");

    while (1);
}
/*
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    // ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n"); 
 */


