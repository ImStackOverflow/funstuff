#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Game.h"


#define RoomTemplate "RoomFiles/room%d.txt"
#define arrLength(x) sizeof(x)/sizeof(*x)

typedef struct {
    int north;
    int east;
    int south;
    int west;
} exits;

typedef struct {
    int roomNumber;
    char file[25];
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    int ItemReq;
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    int items;
    exits exits;
} game;



//FILE *CurrentRoom;
game room;

int loadRoom();

int loadInventory()
{

}

int GameGoNorth(void)
{
    loadRoom();
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
	room.roomNumber = room.exits.north;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }

}

int GameGoEast(void)
{
    loadRoom();
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
	room.roomNumber = room.exits.east;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }

}

int GameGoSouth(void)
{
    loadRoom();
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
	room.roomNumber = room.exits.south;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

int GameGoWest(void)
{
    loadRoom();
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
	room.roomNumber = room.exits.west;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

int GameInit(void)
{
    room.roomNumber = STARTING_ROOM;
    loadRoom();
}

int GameGetCurrentRoomTitle(char *title)
{
    if (strcpy(title, room.title)) {
	*(++title) = '\0';
	return arrLength(title);
    } else {
	return STANDARD_ERROR;
    }
}

int GameGetCurrentRoomDescription(char *desc)
{
    if (strcpy(desc, room.description)) {
	*(++desc) = '\0';
	return arrLength(desc);
    } else {
	return STANDARD_ERROR;
    }
}

uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t exits = 0;
    if (room.exits.north) {
	exits |= 0b1000;
    }
    if (room.exits.east) {
	exits |= 0b0100;
    }
    if (room.exits.south) {
	exits |= 0b0010;
    }
    if (room.exits.west) {
	exits |= 0b0001;
    }
    return exits;

}

int loadRoom()
{
    int nowhere, i;
    sprintf(room.file, RoomTemplate, room.roomNumber);
    FILE *CurrentRoom = fopen(room.file, "rb");

    /******get title******/
    for (i = 0; i < GAME_MAX_ROOM_TITLE_LENGTH + 1; i++) {//reset title
	room.title[i] = 0;
    }

    int length = fgetc(CurrentRoom); //get title length
    char character;

    for (i = 0; i < length; i++) {//get title-length characters
	if (character = fgetc(CurrentRoom)) {//set title
	    room.title[i] = character;
	} else {
	    room.title[0] = '\0';
	    break;
	}
    }
    room.title[++i] = '\0';

    /****get desription****/
    for (i = 0; i < GAME_MAX_ROOM_DESC_LENGTH + 1; i++) { //reset description
	room.description[i] = 0;
    }
    length = fgetc(CurrentRoom); //get items
    for (i = 0; i < length; i++) {
	nowhere = fgetc(CurrentRoom);
    }

    length = fgetc(CurrentRoom);
    for (i = 0; i < length; i++) {//get description-length characters
	if (character = fgetc(CurrentRoom)) {
	    room.description[i] = character;
	} else {
	    room.description[0] = '\0';
	    break;
	}
    }
    room.description[++i] = '\0';

    /****items in room****/

    length = fgetc(CurrentRoom); //get number of items in room
    for (i = 0; i < length; i++) {//get item-length characters
	if (character = fgetc(CurrentRoom)) {//set title
	    AddToInventory(character);
	} else {
	    room.description[0] = '\0';
	    break;
	}
    }


    /****get exits****/
    room.exits.north = fgetc(CurrentRoom);
    room.exits.east = fgetc(CurrentRoom);
    room.exits.south = fgetc(CurrentRoom);
    room.exits.west = fgetc(CurrentRoom);

    fclose(CurrentRoom);
}