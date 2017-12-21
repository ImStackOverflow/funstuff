#include "Field.h"
#include "Protocol.h"
#include "BOARD.h"

void FieldInit(Field *f, FieldPosition p)
{
    int i, j;
    //Clear Field Position
    for (i = 0; i < 6; i++) {

        for (j = 0; j < 10; j++) {
            f->field[i][j] = p; //Ask about this syntax
        }
    }

    //Initialize Boat Lives (How big boat is)
    f->smallBoatLives = FIELD_BOAT_LIVES_SMALL;
    f->mediumBoatLives = FIELD_BOAT_LIVES_MEDIUM;
    f->largeBoatLives = FIELD_BOAT_LIVES_LARGE;
    f->hugeBoatLives = FIELD_BOAT_LIVES_HUGE;
}

FieldPosition FieldAt(const Field *f, uint8_t row, uint8_t col)
{
    return f->field[row][col];
    //Check if it's a boat on position or not
    //Return Boat or Return the hit or miss?
}

FieldPosition FieldSetLocation(Field *f, uint8_t row, uint8_t col, FieldPosition p)
{
    int oldPosition;
    oldPosition = f->field[row][col];
    f->field[row][col] = p;
    return oldPosition;
}

uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType type)
{
    int Parameter = 0;
    int size, i;
    switch (type) {
    case FIELD_BOAT_SMALL:
        size = 3;
        break;
    case FIELD_BOAT_MEDIUM:
        size = 4;
        break;
    case FIELD_BOAT_LARGE:
        size = 5;
        break;
    case FIELD_BOAT_HUGE:
        size = 6;
        break;
    }
    switch (dir) {
        //Direction pointing up
    case FIELD_BOAT_DIRECTION_NORTH:
        if (row - size < 0) {
            return FALSE;
        }
        for (i = 0; i < size; i++) {
            if (f->field[row - i][col] != 0) {
                Parameter = 1;
            }
        }
        //Check if Overlap
        if (Parameter == 1) {
            return FALSE;
        } else {
            for (i = 0; i < size; i++) {
                if (f->field[row - i][col] == 0) {
                    f->field[row - i][col] = size;
                }
            }
        }
        break;
        //Boat Pointing Right
    case FIELD_BOAT_DIRECTION_EAST:
        if (col + size > 10) {
            return FALSE;
        }
        for (i = 0; i < size; i++) {
            if (f->field[row][col + i] != 0) {
                Parameter = 1;
            }
        }
        //Check if Overlap
        if (Parameter == 1) {
            return FALSE;
        } else {
            for (i = 0; i < size; i++) {
                if (f->field[row][col + i] == 0)
                    f->field[row][col + i] = size;
            }
        }
        break;
        //Boat Pointing Down
    case FIELD_BOAT_DIRECTION_SOUTH:
        if (row + size > 10) {
            return FALSE;
        }
        for (i = 0; i < size; i++) {
            if (f->field[row + i][col] != 0) {
                Parameter = 1;
            }
        }
        //Check if Overlap
        if (Parameter == 1) {
            return FALSE;
        } else {
            for (i = 0; i < size; i++) {
                if (f->field[row + i][col] == 0)
                    f->field[row + i][col] = size;
            }
        }
        break;
        //Boat Pointing Left
    case FIELD_BOAT_DIRECTION_WEST:
        if (col - size < 0) {
            return FALSE;
        }
        for (i = 0; i < size; i++) {
            if (f->field[row][col - i] != 0) {
                Parameter = 1;
            }
        }
        //Check if Overlap
        if (Parameter == 1) {
            return FALSE;
        } else {
            for (i = 0; i < size; i++) {
                if (f->field[row][col - i] == 0)
                    f->field[row][col - i] = size;
            }
        }
        break;

    }
    return TRUE;
}

FieldPosition FieldRegisterEnemyAttack(Field *f, GuessData * gData)
{
    int boat;
    boat = f->field[gData->row][gData->col];
   //Boat hit
    if (boat != 0) {
        //small boat
        if (boat == 3) {
            f->smallBoatLives = f->smallBoatLives - 1;
            if (f->smallBoatLives == 0) {
                gData->hit = HIT_SUNK_SMALL_BOAT;
            } else {
                gData->hit = HIT_HIT;
            }
            //Medium Boat
        } else if (boat == 4) {
            f->mediumBoatLives = f->mediumBoatLives - 1;
            if (f->mediumBoatLives == 0) {
                gData->hit = HIT_SUNK_MEDIUM_BOAT;
            } else {
                gData->hit = HIT_HIT;
            }
            //Large Boat
        } else if (boat == 5) {
            f->largeBoatLives = f->largeBoatLives - 1;
            if (f->largeBoatLives == 0) {
                gData->hit = HIT_SUNK_LARGE_BOAT;
            } else {
                gData->hit = HIT_HIT;
            }
            //Huge Boat
        } else if (boat == 6) {
            f->hugeBoatLives = f->hugeBoatLives - 1;
            if (f->hugeBoatLives == 0) {
                gData->hit = HIT_SUNK_HUGE_BOAT;
            } else {
                gData->hit = HIT_HIT;
            }
        }
        f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
    } else {
        f->field[gData->row][gData->col] = FIELD_POSITION_MISS;
    }
    return boat;
}

FieldPosition FieldUpdateKnowledge(Field *f, const GuessData * gData)
{
    int oldPosition = f->field[gData->row][gData->col];
    if (gData->hit != HIT_MISS) {
        f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
    } else {
        f->field[gData->row][gData->col] = FIELD_POSITION_MISS;
    }
    if (gData->hit == HIT_SUNK_SMALL_BOAT) {
        f->smallBoatLives = 0;
    } else if (gData->hit == HIT_SUNK_MEDIUM_BOAT) {
        f->mediumBoatLives = 0;
    } else if (gData->hit == HIT_SUNK_LARGE_BOAT) {
        f->largeBoatLives = 0;
    } else if (gData->hit == HIT_SUNK_HUGE_BOAT) {
        f->hugeBoatLives = 0;
    }
    return oldPosition;

}

uint8_t FieldGetBoatStates(const Field * f)
{
    //Check Which boat is alive
    uint8_t BoatState = 0;
    if (f->smallBoatLives != 0) {
        BoatState += FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives != 0) {
        BoatState += FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives != 0) {
        BoatState += FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives != 0) {
        BoatState += FIELD_BOAT_STATUS_HUGE;
    }
    return BoatState;
    //Return 4bit value to see if boat is still alive
    //0 = dead, 1 = alive
}