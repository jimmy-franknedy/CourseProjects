//#include "Field.h"
#include "Field.h"
#include "FieldOled.h"
#include <stdio.h>
#include <stdint.h>
#include "BattleBoats.h"
#include "BOARD.h"

static Field oppField;
static Field ownField;
static Field extraField;
static SquareStatus SQSTtest1;
static SquareStatus SQSTtest2;
static SquareStatus SQSEtest1 = FIELD_SQUARE_EMPTY;
static SquareStatus SQSEtest2 = FIELD_SQUARE_LARGE_BOAT;
//static SquareStatus FREAtest1;
//static SquareStatus FREAtest2;
static uint8_t rowTest1 = 8;
static uint8_t rowTest2 = 3;
static uint8_t colTest1 = 1;
static uint8_t colTest2 = 9;
//static uint8_t returnVal1;
//static uint8_t returnVal2;
//static BoatType boat1 = FIELD_BOAT_TYPE_HUGE;
//static BoatType boat2 = FIELD_BOAT_TYPE_SMALL;
static BoatDirection verical = FIELD_DIR_SOUTH;
static BoatDirection horizontal = FIELD_DIR_EAST;
//static GuessData guess1;
//static GuessData guess2;

int main(void)
{
    BOARD_Init();
    FieldInit(&ownField, &oppField);
    printf("FieldInit():\n");
    if (oppField.smallBoatLives == 0) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    FieldInit(&ownField, &oppField);
    if (oppField.mediumBoatLives == 0) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\nFieldGetSQ: \n");
    SQSTtest1 = FieldGetSquareStatus(&ownField, rowTest1, colTest1);
    if (SQSTtest1 == 9) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    SQSTtest2 = FieldGetSquareStatus(&ownField, rowTest2, colTest2);
    if (SQSTtest2 == 0) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\nFieldSetSQ: \n");
    SQSTtest1 = FieldSetSquareStatus(&ownField, rowTest1, colTest1, SQSEtest1);
    if (SQSTtest1 == 9) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    SQSTtest2 = FieldSetSquareStatus(&ownField, rowTest2, colTest2, SQSEtest2);
    if (SQSTtest2 == 0) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\nFieldAddBoat: \n");
    Field myField;
    FieldInit(&myField, &extraField);
    int test1 = FieldAddBoat(&myField, 69, -33, horizontal, FIELD_BOAT_TYPE_SMALL);
    if (test1 == 0) {
        printf("Passed Test 1\n");
    }
    int test2 = FieldAddBoat(&myField, 1, 0, horizontal, FIELD_BOAT_TYPE_HUGE);
    if (test2 == 1) {
        printf("Passed Test 2\n");
    }
    int test3 = FieldAddBoat(&myField, 1, 1, verical, FIELD_BOAT_TYPE_MEDIUM);
    if (test3 == 0) {
        printf("Passed Test 3\n");
    }
    printf("\nFieldRegisterEnemyAttack: \n");
    GuessData guess1;
    GuessData guess2;
    guess1.col = 3;
    guess1.row = 0;
    guess2.col = 3;
    guess2.row = 1;
    FieldRegisterEnemyAttack(&myField, &guess1);
    FieldRegisterEnemyAttack(&myField, &guess2);
    if (guess1.result == RESULT_MISS) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    if (guess2.result == RESULT_HIT) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed Test 2\n");
    }
    printf("\nFieldUpdateKnowledge():\n");
    SquareStatus updateknow1 = FieldUpdateKnowledge(&myField, &guess1);
    SquareStatus updateknow2 = FieldUpdateKnowledge(&myField, &guess2);
    if (myField.grid[guess1.row][guess1.col] == FIELD_SQUARE_MISS
            && updateknow1 == FIELD_SQUARE_EMPTY) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    if (myField.grid[guess2.row][guess2.col] == FIELD_SQUARE_HIT
            && updateknow2 == FIELD_SQUARE_HUGE_BOAT) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    printf("\nFieldPrint_UART()\n");
    FieldPrint_UART(&myField, &oppField);
    printf("\nFieldGetBoatStates()\n");
    uint8_t boatStates = FieldGetBoatStates(&myField);
    printf("Expected: 9\nResult:   %d\n", boatStates);
    printf("\nFieldAIPlaceAllBoats()\n");

    Field AIField;
    Field OPPField;
    FieldInit(&AIField, &OPPField);
    uint8_t PlcAllBoat = FieldAIPlaceAllBoats(&AIField);
    if (PlcAllBoat == SUCCESS) {
        printf("Passed Test\n");
    } else {
        printf("Failed Test\n");
    }
    FieldPrint_UART(&AIField, &OPPField);

    printf("\nFieldAIDecideGuess()\n");
    printf("These should be random numbers\n");
    GuessData AIstruct = FieldAIDecideGuess(&oppField);
    printf("Row: %d\nCol: %d\n", AIstruct.row, AIstruct.col);
    AIstruct = FieldAIDecideGuess(&oppField);
    printf("Row: %d\nCol: %d\n", AIstruct.row, AIstruct.col);
    AIstruct = FieldAIDecideGuess(&oppField);
    printf("Row: %d\nCol: %d\n", AIstruct.row, AIstruct.col);
    while (1);
}