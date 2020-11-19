// Jimmy Franknedy
// jfrankne

#define SIZE 20
#define SKIP_DESC 6
#define SKIP 3
#define MASK 15
#define ITEM_SIZE 10
#define COMPASS 3
#define PASS 1
#define TWO 2 

#include "Game.h"
#include "stdio.h"
#include "UNIXBOARD.h"
#include "Player.h"
#include <string.h>

struct ChooseYourAdventure {
    FILE *currentFile;
    int twoVersions;
    int strLock;
    int currentRoomNumber;
    int titleLength[1];

    // Variables used to get Version 1 of Room
    int descLength[1];
    char descName[GAME_MAX_ROOM_DESC_LENGTH + 1];
    int itemReq[1];
    int itemReqID[ITEM_SIZE];
    int itemContLength[1];
    int itemContID[ITEM_SIZE];

    // Variables used to get Version 2 of room
    int descLength_V2[1];
    char descName_V2[GAME_MAX_ROOM_DESC_LENGTH + 1];
    int itemReq_V2[1];
    int itemReqID_V2[ITEM_SIZE];
    int itemContLength_V2[1];
    int itemContID_V2[ITEM_SIZE];

    // Variables used in both Version 1 & 2 of the room
    int roomExitN[COMPASS];
    int roomExitE[COMPASS];
    int roomExitS[COMPASS];
    int roomExitW[COMPASS];

    char fileName[SIZE];
    char titleName[GAME_MAX_ROOM_TITLE_LENGTH + 1];

    uint8_t roomExitDirection;
    uint8_t roomExitRoom;
};

struct ChooseYourAdventure GameofThrones;

int LoadRoom(int nextRoom)
{
    // Reset all the arrays
    memset(GameofThrones.descLength, 0, sizeof (GameofThrones.descLength));
    memset(GameofThrones.descLength_V2, 0, sizeof (GameofThrones.descLength_V2));
    memset(GameofThrones.descName, 0, sizeof (GameofThrones.descName));
    memset(GameofThrones.descName_V2, 0, sizeof (GameofThrones.descName_V2));
    memset(GameofThrones.fileName, 0, sizeof (GameofThrones.fileName));
    memset(GameofThrones.itemContID, 0, sizeof (GameofThrones.itemContID));
    memset(GameofThrones.itemContID_V2, 0, sizeof (GameofThrones.itemContID_V2));
    memset(GameofThrones.itemContLength, 0, sizeof (GameofThrones.itemContLength));
    memset(GameofThrones.itemContLength_V2, 0, sizeof (GameofThrones.itemContLength_V2));
    memset(GameofThrones.itemReq, 0, sizeof (GameofThrones.itemReq));
    memset(GameofThrones.itemReqID, 0, sizeof (GameofThrones.itemReqID));
    memset(GameofThrones.itemReqID_V2, 0, sizeof (GameofThrones.itemReqID_V2));
    memset(GameofThrones.itemReq_V2, 0, sizeof (GameofThrones.itemReq_V2));
    memset(GameofThrones.roomExitE, 0, sizeof (GameofThrones.roomExitE));
    memset(GameofThrones.roomExitN, 0, sizeof (GameofThrones.roomExitN));
    memset(GameofThrones.roomExitS, 0, sizeof (GameofThrones.roomExitS));
    memset(GameofThrones.roomExitW, 0, sizeof (GameofThrones.roomExitW));
    memset(GameofThrones.titleLength, 0, sizeof (GameofThrones.titleLength));
    memset(GameofThrones.titleName, 0, sizeof (GameofThrones.titleName));
    GameofThrones.twoVersions = 0;

    GameofThrones.currentRoomNumber = nextRoom;
    sprintf(GameofThrones.fileName, "RoomFiles/room%d.txt", GameofThrones.currentRoomNumber);
    FILE *startingFile = fopen(GameofThrones.fileName, "rb");
    GameofThrones.currentFile = startingFile;
    // Check to see if the file is NULL
    if (GameofThrones.currentFile != NULL) {
        fseek(GameofThrones.currentFile, SKIP, SEEK_SET);
        // Read in the title
        fread(GameofThrones.titleLength, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.titleName, 1, GameofThrones.titleLength[0], GameofThrones.currentFile);
        // Read in the item requirements
        fread(GameofThrones.itemReq, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.itemReqID, 1, GameofThrones.itemReq[0], GameofThrones.currentFile);
        // Read in the description
        fread(GameofThrones.descLength, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.descName, 1, GameofThrones.descLength[0], GameofThrones.currentFile);
        // Read in the items contained
        fread(GameofThrones.itemContLength, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.itemContID, 1, GameofThrones.itemContLength[0], GameofThrones.currentFile);
        // Read in the number of exits
        fread(GameofThrones.roomExitN, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.roomExitE, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.roomExitS, 1, 1, GameofThrones.currentFile);
        fread(GameofThrones.roomExitW, 1, 1, GameofThrones.currentFile);
        // Check to see if there is another version of the file
        if (GameofThrones.itemReq[0] == 0) {
            fclose(GameofThrones.currentFile);
            return SUCCESS;
        } else {
            GameofThrones.twoVersions = 1;
            // Read in the item requirements
            fread(GameofThrones.itemReq_V2, 1, 1, GameofThrones.currentFile);
            fread(GameofThrones.itemReqID_V2, 1, GameofThrones.itemReq_V2[0], GameofThrones.currentFile);
            // Read in the description
            fread(GameofThrones.descLength_V2, 1, 1, GameofThrones.currentFile);
            fread(GameofThrones.descName_V2, 1, GameofThrones.descLength_V2[0], GameofThrones.currentFile);
            // Read in the items contained
            fread(GameofThrones.itemContLength_V2, 1, 1, GameofThrones.currentFile);
            fread(GameofThrones.itemContID_V2, 1, GameofThrones.itemContLength_V2[0], GameofThrones.currentFile);
            fclose(GameofThrones.currentFile);
            return SUCCESS;
        }
    } else if (startingFile == NULL) {
        FATAL_ERROR();
    }
    FATAL_ERROR();
}

int GameGoNorth(void)
{
    // The current room has a NORTH exit.
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
        // Change the CurrentRoom to the room of the NORTH
        int goNorth = GameofThrones.roomExitN[0];
        int CheckLoadNorth = LoadRoom(goNorth);
        if (CheckLoadNorth == 1) {
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoEast(void)
{
    // The current room has a EAST exit.
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
        // Change the CurrentRoom to the room of the EAST
        int goEast = GameofThrones.roomExitE[0];
        int CheckLoadEast = LoadRoom(goEast);
        if (CheckLoadEast == 1) {
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoSouth(void)
{
    // The current room has a SOUTH exit.
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        // Change the CurrentRoom to the room of the SOUTH
        int goSouth = GameofThrones.roomExitS[0];
        int CheckLoadSouth = LoadRoom(goSouth);
        if (CheckLoadSouth == 1) {
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoWest(void)
{
    // The current room has a WEST exit.
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
        // Change the CurrentRoom to the room of the WEST
        int goWest = GameofThrones.roomExitW[0];
        int CheckLoadWest = LoadRoom(goWest);
        if (CheckLoadWest == 1) {
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameInit(void)
{
    int init = STARTING_ROOM;
    int Check = LoadRoom(init);
    if (Check == PASS) {
        return SUCCESS;
    }
    FATAL_ERROR();
}

int GameGetCurrentRoomTitle(char *title)
{
    strcpy(title, GameofThrones.titleName);
    int titleLength = strlen(title) + 1;
    return titleLength;
}

int GameGetCurrentRoomDescription(char *desc)
{
    // This counter is used to hold a string once it is copied
    GameofThrones.strLock = 0;
    // This condition is used to determine the items and description of the room if there
    // are only 1 version of it.
    if (GameofThrones.twoVersions == 0) {
        uint8_t Item_Test1 = (uint8_t) GameofThrones.itemContID[0];
        uint8_t Description_Test1 = (uint8_t) GameofThrones.itemReqID[0];
        if (GameofThrones.itemReq[0] == 0) {
            strcpy(desc, GameofThrones.descName);
            if (GameofThrones.itemContLength[0] > 0) {
                if (FindInInventory(Item_Test1) == STANDARD_ERROR) {
                    AddToInventory(Item_Test1);
                }
            }
        } else if (GameofThrones.itemReq[0] > 0) {
            if (FindInInventory(Description_Test1) == SUCCESS) {
                strcpy(desc, GameofThrones.descName);
            }
        }
    } else if (GameofThrones.twoVersions == 1) {
        // This condition is used to determine the items and description of the room if there
        // are 2 versions of it.
        uint8_t Item_Test1 = (uint8_t) GameofThrones.itemContID[0];
        uint8_t Description_Test1 = (uint8_t) GameofThrones.itemReqID[0];
        uint8_t Item_Test2 = (uint8_t) GameofThrones.itemContID_V2[0];
        uint8_t Description_Test2 = (uint8_t) GameofThrones.itemReqID_V2[0];
        if (GameofThrones.itemReq[0] == 0) {
            if (GameofThrones.strLock == 0) {
                strcpy(desc, GameofThrones.descName);
                GameofThrones.strLock = 1;
            }
            if (GameofThrones.itemContLength[0] > 0) {
                if (FindInInventory(Item_Test1) == STANDARD_ERROR) {
                    AddToInventory(Item_Test1);
                }
            }
        } else if (GameofThrones.itemReq[0] > 0) {
            if (FindInInventory(Description_Test1) == SUCCESS) {
                if (GameofThrones.strLock == 0) {
                    strcpy(desc, GameofThrones.descName);
                    GameofThrones.strLock = 1;
                }
            }
        }
        if (GameofThrones.itemReq_V2[0] == 0 && (GameofThrones.twoVersions == 1)) {
            if (GameofThrones.strLock == 0) {
                strcpy(desc, GameofThrones.descName_V2);
                GameofThrones.strLock = 1;
            }
            if (GameofThrones.itemContLength_V2[0] > 0) {
                if (FindInInventory(Item_Test2) == STANDARD_ERROR) {
                    AddToInventory(Item_Test2);
                }
            }
        } else if (GameofThrones.itemReq_V2[0] > 0 && (GameofThrones.twoVersions == 1)) {
            if (FindInInventory(Description_Test2) == SUCCESS) {
                if (GameofThrones.strLock == 0) {
                    strcpy(desc, GameofThrones.descName_V2);
                    GameofThrones.strLock = 1;
                }
            }
        }
    }
    int descLength = strlen(desc) + 1;
    return descLength;
}

uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t openExits = 0;
    if (GameofThrones.roomExitN[0] > 0) {
        openExits = openExits | GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (GameofThrones.roomExitE[0] > 0) {
        openExits = openExits | GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (GameofThrones.roomExitS[0] > 0) {
        openExits = openExits | GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (GameofThrones.roomExitW[0] > 0) {
        openExits = openExits | GAME_ROOM_EXIT_WEST_EXISTS;
    }
    // Bit Masked to only return the lower 4 bits which correspond to a direction exit
    openExits = openExits & MASK;
    return openExits;
}

int SwitchDirection(int currRoom)
{
    int result = 0;
    if (currRoom == GAME_ROOM_EXIT_NORTH_EXISTS) {
        result = GameofThrones.roomExitN[0];
    } else if (currRoom == GAME_ROOM_EXIT_EAST_EXISTS) {
        result = GameofThrones.roomExitE[0];
    } else if (currRoom == GAME_ROOM_EXIT_SOUTH_EXISTS) {
        result = GameofThrones.roomExitS[0];
    } else if (currRoom == GAME_ROOM_EXIT_WEST_EXISTS) {
        result = GameofThrones.roomExitW[0];
    }
    return result;
}
