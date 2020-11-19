// Jimmy Franknedy
// jfrankne

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CMPE13 Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


// User libraries

// **** Set any macros or preprocessor directives here ****
#define SUCCESS 1
#define SIZE 15
#define INPUT 2
#define LOWER_N 'n'
#define LOWER_S 's'
#define LOWER_E 'e'
#define LOWER_W 'w'
#define LOWER_Q 'q'
#define THOU 1000
#define END '\n'

// **** Declare any data types here ****

// **** Define any global or external variables here ****
static char titleArray[GAME_MAX_ROOM_TITLE_LENGTH + 1];
static char *titlePTR = titleArray;
static char descArray[GAME_MAX_ROOM_DESC_LENGTH + 1];
static char *descPTR = descArray;
static char UserInput;
static int NorthFlag = 0;
static int EastFlag = 0;
static int SouthFlag = 0;
static int WestFlag = 0;
static int updatedDirection = 0;
static int SETUP = 1;
static char inputString[THOU];
static int trackInput = 0;
static int checkInput = 0;

// **** Declare any function prototypes here ****
int SwitchDirection (int currRoom);
int LoadRoom (int nextRoom);

int main()
{
    /******************************** Your custom code goes below here ********************************/
    GameInit();
    while (1) {
        if (SETUP == 1) {
            // Used to display the room.
            memset(titleArray, 0, sizeof (titleArray));
            memset(descArray, 0, sizeof (descArray));
            GameGetCurrentRoomTitle(titlePTR);
            printf("\nTitle: %s\n\n", titlePTR);
            GameGetCurrentRoomDescription(descPTR);
            printf("Description: %s\n\n", descPTR);
            GameGetCurrentRoomExits();
            printf("Exits: ");
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
                NorthFlag = 1;
                printf("n ");
            }
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
                EastFlag = 1;
                printf("e ");
            }
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
                SouthFlag = 1;
                printf("s ");
            }
            if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
                WestFlag = 1;
                printf("w ");
            }
            SETUP = 0;
        }
        printf("\n\nEnter Direction to Travel (n,e,s,w) or q to quit followed by enter: ");
        while ((checkInput = getchar()) != END) {
            inputString[trackInput] = checkInput;
            ++trackInput;
        }
        int checkInputLength = strlen(inputString);
        if (checkInputLength == 1) {
            UserInput = inputString[0];
            if (UserInput == LOWER_N && NorthFlag == 1) {
                printf("\n\n");
                NorthFlag = 0;
                updatedDirection = GAME_ROOM_EXIT_NORTH_EXISTS;
                updatedDirection = SwitchDirection(updatedDirection);
                SETUP = 1;
                GameGoNorth();
            } else if (UserInput == LOWER_E && EastFlag == 1) {
                printf("\n\n");
                EastFlag = 0;
                updatedDirection = GAME_ROOM_EXIT_EAST_EXISTS;
                updatedDirection = SwitchDirection(updatedDirection);
                SETUP = 1;
                GameGoEast();
            } else if (UserInput == LOWER_S && SouthFlag == 1) {
                printf("\n\n");
                SouthFlag = 0;
                updatedDirection = GAME_ROOM_EXIT_SOUTH_EXISTS;
                updatedDirection = SwitchDirection(updatedDirection);
                SETUP = 1;
                GameGoSouth();
            } else if (UserInput == LOWER_W && WestFlag == 1) {
                printf("\n\n");
                WestFlag = 0;
                updatedDirection = GAME_ROOM_EXIT_WEST_EXISTS;
                updatedDirection = SwitchDirection(updatedDirection);
                SETUP = 1;
                GameGoWest();
            } else if (UserInput == LOWER_Q) {
                SETUP = 1;
                exit(SUCCESS);
            }
        }
        memset(inputString, 0, sizeof (inputString));
        checkInput = 0;
        trackInput = 0;
    }
    /**************************************************************************************************/
}

