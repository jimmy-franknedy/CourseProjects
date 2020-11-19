// Jimmy Franknedy
// jfrankne

#include "Player.h"
#include "stdio.h"
#include <string.h>

// Create an array to hold the item IDs in the User's Inventory
static int userInventory[INVENTORY_SIZE] = {};

// Counter to hold the position in the User's inventory
static int userInventoryPosition = 0;

// Counter used to parse through the User's inventory
static int userInventoryLoop = 0;

// Counter used to hold the item in the User's inventory at position [userInventoryLoop]
static int userInventoryCurrentItem = 0;

// Function used to check if an item can be added into the User's Inventory

int AddToInventory(uint8_t item)
{
    if (userInventoryPosition != INVENTORY_SIZE) {
        userInventory[userInventoryPosition] = item;
        userInventoryPosition++;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

// Function used to check if an item is in the User's Inventory

int FindInInventory(uint8_t item)
{
    // Reset the pointer to the 0th position of the userInventory Array
    userInventoryLoop = 0;
    while (userInventoryLoop != INVENTORY_SIZE) {
        userInventoryCurrentItem = userInventory[userInventoryLoop];
        if (userInventoryCurrentItem == item) {
            return SUCCESS;
        }
        userInventoryLoop++;
    }
    return STANDARD_ERROR;
}
