
#include "Player.h"
#include "Game.h"

int Inventory[INVENTORY_SIZE], InventoryIndex;

int AddToInventory(uint8_t item)
{
    if (InventoryIndex < INVENTORY_SIZE) {
	Inventory[InventoryIndex] = item;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item)
{
    int i;
    for (i = 0; i < InventoryIndex; i++) {
	if (Inventory[InventoryIndex] == item) {
	    return SUCCESS;
	}
    }
    return STANDARD_ERROR;
}