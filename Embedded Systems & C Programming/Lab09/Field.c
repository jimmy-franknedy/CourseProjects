// Jimmy Franknedy
// jfrankne@ucsc.edu


#include "xc.h"
#include <stdint.h>
#include "Field.h"
#include <string.h>
#include "BOARD.h"
#include "stdio.h"
#include "BattleBoats.h"

#define LIVES 0

#define SMALL 3
#define MEDIUM 4
#define LARGE 5
#define HUGE 6

#define VALUE4 4
#define VALUE3 3
#define VALUE2 2
#define NEG_1 -1

/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field * opp_field)
{
    printf("    0 1 2 3 4 5 6 7 8 9  \n");
    printf("   --------------------- \n");
    int horizontal = 0;
    for (horizontal = 0; horizontal < FIELD_ROWS; horizontal++) {
        printf("%d [ ", horizontal);
        int vertical;
        for (vertical = 0; vertical < FIELD_COLS; vertical++) {
            int currentSquare = own_field->grid[horizontal][vertical];
            switch (currentSquare) {
            case FIELD_SQUARE_EMPTY:
                printf(".");
                break;
            case FIELD_SQUARE_SMALL_BOAT:
                printf("3");
                break;
            case FIELD_SQUARE_MEDIUM_BOAT:
                printf("4");
                break;
            case FIELD_SQUARE_LARGE_BOAT:
                printf("5");
                break;
            case FIELD_SQUARE_HUGE_BOAT:
                printf("6");
                break;
            case FIELD_SQUARE_UNKNOWN:
                printf("?");
                break;
            case FIELD_SQUARE_HIT:
                printf("H");
                break;
            case FIELD_SQUARE_MISS:
                printf("M");
                break;
            case FIELD_SQUARE_INVALID:
                printf("!");
                break;
            }
            printf(" ");
        }
        printf("]\n");
    }
}

/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus.
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be set when boats are added)
 * 
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 * 
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field * opp_field)
{
    // Fill the grid with the status that it is empty
    // Need to set BoatLives or something like that?
    int horizontal;
    for (horizontal = 0; horizontal < FIELD_ROWS; horizontal++) {
        int vertical;
        for (vertical = 0; vertical < FIELD_COLS; vertical++) {
            own_field->grid[horizontal][vertical] = FIELD_SQUARE_EMPTY;
            opp_field->grid[horizontal][vertical] = FIELD_SQUARE_EMPTY;
        }
    }
    // Setting boat lives to their respective lengths
    own_field->hugeBoatLives = LIVES;
    opp_field->hugeBoatLives = LIVES;
    own_field->largeBoatLives = LIVES;
    opp_field->largeBoatLives = LIVES;
    own_field->mediumBoatLives = LIVES;
    opp_field->mediumBoatLives = LIVES;
    own_field->smallBoatLives = LIVES;
    opp_field->smallBoatLives = LIVES;
}

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  SQUARE_STATUS_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square 
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if ((row <= FIELD_ROWS && row >= 0) && (col <= FIELD_COLS && col >= 0)) {
        // Return the FIELD_SQUARE value at that coordinate.
        // Check if this code actually works
        SquareStatus GetStatus = f->grid[row][col];
        return GetStatus;
    }
    return FIELD_SQUARE_INVALID;
}

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 * 
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    // Check if this code works!
    if ((row <= FIELD_ROWS && row >= 0) && (col <= FIELD_COLS && col >= 0)) {
        // Get the old value at the field location
        SquareStatus OldSquareStatus = FieldGetSquareStatus(f, row, col);
        // Set the new value at the field location
        f->grid[row][col] = p;
        // Return the old value at the field location
        return OldSquareStatus;
    }
    // Return an INVALID if an error occurs
    return FIELD_SQUARE_INVALID;
}

/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed. All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *     
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    int CurrentBoatsAlive = 0;
    if (f->hugeBoatLives) {
        CurrentBoatsAlive++;
    }
    if (f->largeBoatLives) {
        CurrentBoatsAlive++;
    }
    if (f->mediumBoatLives) {
        CurrentBoatsAlive++;
    }
    if (f->smallBoatLives) {
        CurrentBoatsAlive++;
    }
    int returnError = 0;
    static int boatCount = 0;
    if (CurrentBoatsAlive != VALUE4) {
        // Check if the row and col coordinates are in range of the field
        if ((row <= FIELD_ROWS && row >= 0) && (col <= FIELD_COLS && col >= 0)) {
            // Get the status of the coordinates of "row" and "col"
            SquareStatus CheckCoordiante = FieldGetSquareStatus(f, row, col);
            SquareStatus FieldSetBoat;
            if (CheckCoordiante == FIELD_SQUARE_EMPTY) {
                // Coordinate is empty check the direction the user wants to place the boat
                int sizeCheck = 0;
                switch (boat_type) {
                case FIELD_BOAT_TYPE_SMALL:
                {
                    // Set the size of the boat to 3
                    FieldSetBoat = FIELD_SQUARE_SMALL_BOAT;
                    f->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                    sizeCheck = SMALL;
                    break;
                }
                case FIELD_BOAT_TYPE_MEDIUM:
                {
                    // Set the size of the boat to 4
                    FieldSetBoat = FIELD_SQUARE_MEDIUM_BOAT;
                    f->smallBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                    sizeCheck = MEDIUM;
                    break;
                }
                case FIELD_BOAT_TYPE_LARGE:
                {
                    FieldSetBoat = FIELD_SQUARE_LARGE_BOAT;
                    f->smallBoatLives = FIELD_BOAT_SIZE_LARGE;
                    // Set the size of the boat to 5
                    sizeCheck = LARGE;
                    break;
                }
                case FIELD_BOAT_TYPE_HUGE:
                {
                    FieldSetBoat = FIELD_SQUARE_HUGE_BOAT;
                    f->smallBoatLives = FIELD_BOAT_SIZE_LARGE;
                    // Set the size of the boat to 6
                    sizeCheck = HUGE;
                    break;
                }
                }
                // Counter used to check the length of the boat-to-be-placed
                int checkDirection;
                // Counter used to increment the column;
                int checkCol = col;
                // Counter used to increment the row;
                int checkRow = row;
                // Counter used to keep track of the valid spaces a boat can be placed at.
                int validDirection = 0;
                if (dir == FIELD_DIR_EAST) {
                    int checkDistance = checkCol + sizeCheck;
                    if (checkDistance <= FIELD_COLS) {
                        // Loop through the boat length and check if the spaces are valid
                        for (checkDirection = 0; checkDirection < sizeCheck; checkDirection++) {
                            if (f->grid[row][checkCol] == FIELD_SQUARE_EMPTY) {
                                // Add to the validity counter signifying that the space is valid.
                                validDirection++;
                            }
                            // Increment to the next column;
                            checkCol++;
                        }
                        // If the space for the boat is valid and matches it's length then place it
                        if (validDirection == sizeCheck) {
                            // Reset checkCol back to the input 'col' in order to increment correctly
                            checkCol = col;
                            // Set the boat!
                            for (checkDirection = 0; checkDirection < sizeCheck; checkDirection++) {
                                f->grid[row][checkCol] = FieldSetBoat;
                                checkCol++;
                            }
                            boatCount++;
                            return SUCCESS;
                        } else {
                            returnError = 1;
                            return STANDARD_ERROR;
                        }
                    } else {
                        returnError = 1;
                        return STANDARD_ERROR;
                    }
                } else if (dir == FIELD_DIR_SOUTH) {
                    int checkDistance = checkRow + sizeCheck;
                    if (checkDistance <= FIELD_ROWS) {
                        // Loop through the boat length and check if the spaces are valid
                        for (checkDirection = 0; checkDirection < sizeCheck; checkDirection++) {
                            if (f->grid[checkRow][col] == FIELD_SQUARE_EMPTY) {
                                // Add to the validity counter signifying that the space is valid.
                                validDirection++;
                            }
                            // Increment to the next column;
                            checkRow++;
                        }
                        // If the space for the boat is valid and matches it's length then place it
                        if (validDirection == sizeCheck) {
                            // Reset checkRow back to the input 'row' in order to increment correctly
                            checkRow = row;
                            // Set the boat!
                            for (checkDirection = 0; checkDirection < sizeCheck; checkDirection++) {
                                f->grid[checkRow][col] = FieldSetBoat;
                                checkRow++;
                            }
                            boatCount++;
                            return SUCCESS;
                        } else {
                            return STANDARD_ERROR;
                        }
                    } else {
                        returnError = 1;
                    }
                } else {
                    returnError = 1;
                }
            } else {
                returnError = 1;
            }
        } else
            returnError = 1;
        if (returnError == 1) {
            return STANDARD_ERROR;
        } else {
            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
}

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */
SquareStatus FieldRegisterEnemyAttack(Field *f, GuessData *gData)
{
    // Check the coordinates for the shot guess with the field data
    SquareStatus CurrentSquare = f->grid[gData->row][gData->col];
    // If the guess coordinates match with a boat coordinate...
    if (CurrentSquare == FIELD_SQUARE_SMALL_BOAT) {
        // Decrement the life of the boat
        f->smallBoatLives--;
        // Store the result of this attack in gData->result
        // 2 Types: Ship is sunk / Ship is hit
        if (f->smallBoatLives == 0) {
            gData->result = RESULT_SMALL_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
    } else if (CurrentSquare == FIELD_SQUARE_MEDIUM_BOAT) {
        // Decrement the life of the boat
        f->mediumBoatLives--;
        // Store the result of this attack in gData->result
        // 2 Types: Ship is sunk / Ship is hit
        if (f->mediumBoatLives == 0) {
            gData->result = RESULT_MEDIUM_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
    } else if (CurrentSquare == FIELD_SQUARE_LARGE_BOAT) {
        // Decrement the life of the boat
        f->largeBoatLives--;
        // Store the result of this attack in gData->result
        // 2 Types: Ship is sunk / Ship is hit
        if (f->largeBoatLives == 0) {
            gData->result = RESULT_LARGE_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
    } else if (CurrentSquare == FIELD_SQUARE_HUGE_BOAT) {
        // Decrement the life of the boat
        f->hugeBoatLives--;
        // Store the result of this attack in gData->result
        // 2 Types: Ship is sunk / Ship is hit
        if (f->hugeBoatLives == 0) {
            gData->result = RESULT_HUGE_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
    } else if (CurrentSquare == FIELD_SQUARE_EMPTY) {
        // Store the result of this attack in gData->result
        gData->result = RESULT_MISS;
    }
    return STANDARD_ERROR;
}

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *f, const GuessData *gData)
{
    // If the guess data resulted in a hit shot
    if (gData->result == RESULT_HIT) {
        // Get the current (old) value of the square
        SquareStatus OldSquareStatus = FieldGetSquareStatus(f, gData->row, gData->col);
        // Set the value of the square to a hit on the field
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        // Return the "old" value of the square
        return OldSquareStatus;
    }// If the guess data resulted in a miss shot
    else if (gData->result == RESULT_MISS) {
        // Get the current (old) value of the square
        SquareStatus OldSquareStatus = FieldGetSquareStatus(f, gData->row, gData->col);
        // Set the value of the square to a miss on the field
        f->grid[gData->row][gData->col] = FIELD_SQUARE_MISS;
        // Return the "old" value of the square
        return OldSquareStatus;
    }
    return STANDARD_ERROR;
}

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field *f)
{
    uint8_t checkBoatLives = 0;
    if (f->hugeBoatLives != 0) {
        checkBoatLives |= FIELD_BOAT_STATUS_HUGE;
    }
    if (f->largeBoatLives != 0) {
        checkBoatLives |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->mediumBoatLives != 0) {
        checkBoatLives |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->smallBoatLives != 0) {
        checkBoatLives |= FIELD_BOAT_STATUS_SMALL;
    }
    return checkBoatLives;
}

/**
 * This function is responsible for placing all the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *f)
{
    // Declare a random 'row' value
    uint8_t randomRow;

    // Declare a random 'col' value
    uint8_t randomCol;

    // Declare a random direction
    BoatDirection randomDirection;
    int randomDir;

    // Declare a random boat type
    BoatType randomBoatType = 0;
    static int boatCounter = 3;

    // Declare an instance that will check if FieldAddBoat is valid
    uint8_t Trial = 0;
    while (!Trial) {
        switch (boatCounter) {
        case 3:
            randomBoatType = FIELD_BOAT_TYPE_HUGE;
            break;
        case 2:
            randomBoatType = FIELD_BOAT_TYPE_LARGE;
            break;
        case 1:
            randomBoatType = FIELD_BOAT_TYPE_MEDIUM;
            break;
        case 0:
            randomBoatType = FIELD_BOAT_TYPE_SMALL;
            break;
        }
        randomRow = rand();
        randomRow %= FIELD_ROWS;
        randomCol = rand();
        randomCol %= FIELD_COLS;
        randomDir = rand();
        if (randomDir % VALUE2 == 0) {
            randomDirection = FIELD_DIR_EAST;
        } else {
            randomDirection = FIELD_DIR_SOUTH;
        }
        Trial = FieldAddBoat(f, randomCol, randomRow, randomDirection, randomBoatType);
        if (Trial) {
            boatCounter--;
        }
    }
    Trial = 0;
    while (!Trial) {
        switch (boatCounter) {
        case 3:
            randomBoatType = FIELD_BOAT_TYPE_HUGE;
            break;
        case 2:
            randomBoatType = FIELD_BOAT_TYPE_LARGE;
            break;
        case 1:
            randomBoatType = FIELD_BOAT_TYPE_MEDIUM;
            break;
        case 0:
            randomBoatType = FIELD_BOAT_TYPE_SMALL;
            break;
        }
        randomRow = rand();
        randomRow %= FIELD_ROWS;
        randomCol = rand();
        randomCol %= FIELD_COLS;
        randomDir = rand();
        if (randomDir % VALUE2 == 0) {
            randomDirection = FIELD_DIR_EAST;
        } else {
            randomDirection = FIELD_DIR_SOUTH;
        }
        Trial = FieldAddBoat(f, randomCol, randomRow, randomDirection, randomBoatType);
        if (Trial) {
            boatCounter--;
        }
    }
    Trial = 0;
    while (!Trial) {
        switch (boatCounter) {
        case 3:
            randomBoatType = FIELD_BOAT_TYPE_HUGE;
            break;
        case 2:
            randomBoatType = FIELD_BOAT_TYPE_LARGE;
            break;
        case 1:
            randomBoatType = FIELD_BOAT_TYPE_MEDIUM;
            break;
        case 0:
            randomBoatType = FIELD_BOAT_TYPE_SMALL;
            break;
        }
        randomRow = rand();
        randomRow %= FIELD_ROWS;
        randomCol = rand();
        randomCol %= FIELD_COLS;
        randomDir = rand();
        if (randomDir % VALUE2 == 0) {
            randomDirection = FIELD_DIR_EAST;
        } else {
            randomDirection = FIELD_DIR_SOUTH;
        }
        Trial = FieldAddBoat(f, randomCol, randomRow, randomDirection, randomBoatType);
        if (Trial) {
            boatCounter--;
        }
    }
    Trial = 0;
    while (!Trial) {
        switch (boatCounter) {
        case 3:
            randomBoatType = FIELD_BOAT_TYPE_HUGE;
            break;
        case 2:
            randomBoatType = FIELD_BOAT_TYPE_LARGE;
            break;
        case 1:
            randomBoatType = FIELD_BOAT_TYPE_MEDIUM;
            break;
        case 0:
            randomBoatType = FIELD_BOAT_TYPE_SMALL;
            break;
        }
        randomRow = rand();
        randomRow %= FIELD_ROWS;
        randomCol = rand();
        randomCol %= FIELD_COLS;
        randomDir = rand();
        if (randomDir % VALUE2 == 0) {
            randomDirection = FIELD_DIR_EAST;
        } else {
            randomDirection = FIELD_DIR_SOUTH;
        }
        Trial = FieldAddBoat(f, randomCol, randomRow, randomDirection, randomBoatType);
        if (Trial) {
            boatCounter--;
        }
    }
}

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field *f)
{
    static int horizontal = 0;
    static int vertical = 0;
    GuessData guessReturn;
    horizontal = rand() % 10;
    vertical = rand() % 10;
    guessReturn.col = horizontal;
    guessReturn.row = vertical;
    return guessReturn;
}

/** 
 * For Extra Credit:  Make the two "AI" functions above 
 * smart enough to beat our AI in more than 55% of games.
 */


