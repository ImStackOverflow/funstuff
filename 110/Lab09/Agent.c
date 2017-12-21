#include "Agent.h"
#include "Protocol.h"
#include "Field.h"
#include "BOARD.h"
#include "Oled.h"
#include "FieldOled.h"
#include <stdlib.h>

Field myField;
Field enemyField;
FieldOledTurn turn;

void AgentInit()
{
    turn = FIELD_OLED_TURN_NONE;
    int i;
    int row = rand() % 6;
    int col = rand() % 10;
    int direction = rand() % 4;
    FieldInit(&myField, FIELD_POSITION_EMPTY);
    FieldInit(&enemyField, FIELD_POSITION_UNKNOWN);
    //Generate Random Field
    for (i = 0; i < 4; i++) {
	do {
	    row = rand() % 6;
	    col = rand() % 10;
	    direction = rand() % 4;
	} while (FieldAddBoat(&myField, row, col, direction, i) == FALSE);
    }
    FieldOledDrawScreen(&myField, &enemyField, turn);



}

int AgentRun(char in, char *outBuffer)
{

    typedef enum {
	messParsing, NegData, Tie
    } failure;
    static failure agent_type;
    ProtocolParserStatus SendData;
    char message[PROTOCOL_MAX_MESSAGE_LEN];
    int order;
    static NegotiationData YourNData, EnemyNData;
    static GuessData YourGData, EnemyGData;
    static AgentState State = AGENT_STATE_GENERATE_NEG_DATA;


    switch (State) {

    case AGENT_STATE_GENERATE_NEG_DATA:
	ProtocolGenerateNegotiationData(&YourNData); //generate data
	ProtocolEncodeChaMessage(outBuffer, &YourNData); //create message and store to outbuffer
	State = AGENT_STATE_SEND_CHALLENGE_DATA; //move to next state
	break;

    case AGENT_STATE_SEND_CHALLENGE_DATA:
	SendData = ProtocolDecode(in, &EnemyNData, &EnemyGData);
	if (SendData == PROTOCOL_PARSING_FAILURE) {
	    agent_type = messParsing; // if failed
	    State = AGENT_STATE_INVALID;
	} else if (SendData == PROTOCOL_PARSED_CHA_MESSAGE) {//parsed a cha message
	    ProtocolEncodeDetMessage(outBuffer, &YourNData); //make det message and send to outbuffer
	} else {//otherwise keep decoding
	    State = AGENT_STATE_SEND_CHALLENGE_DATA;
	}
	ProtocolEncodeDetMessage(message, &YourNData);
	State = AGENT_STATE_DETERMINE_TURN_ORDER;
	break;

    case AGENT_STATE_DETERMINE_TURN_ORDER:

	if (ProtocolValidateNegotiationData(&EnemyNData)) {
	    order = ProtocolGetTurnOrder(&YourNData, &EnemyNData);
	    if (order == TURN_ORDER_TIE) {
		agent_type = Tie;
		State = AGENT_STATE_INVALID;
		//Enemy Won
	    } else if (order == TURN_ORDER_DEFER) {
		turn = FIELD_OLED_TURN_THEIRS;
		FieldOledDrawScreen(&myField, &enemyField, turn);
		State = AGENT_STATE_WAIT_FOR_GUESS;
		//I won
	    } else if (order == TURN_ORDER_START) {
		turn = FIELD_OLED_TURN_MINE;
		FieldOledDrawScreen(&myField, &enemyField, turn);
		State = AGENT_STATE_SEND_GUESS;
	    }
	} else {
	    agent_type = NegData;
	}
	break;

    case AGENT_STATE_SEND_GUESS:
	YourGData.row = rand() % 6;
	YourGData.col = rand() % 10;
	ProtocolEncodeCooMessage(message, &YourGData);
	break;

    case AGENT_STATE_WAIT_FOR_HIT:
	if (ProtocolDecode(in, &EnemyNData, &EnemyGData) == PROTOCOL_PARSED_HIT_MESSAGE) {

	    if (YourGData.hit == HIT_HIT) {

	    } else if (EnemyGData.hit == HIT_SUNK_HUGE_BOAT) {

	    } else if (EnemyGData.hit == HIT_SUNK_SMALL_BOAT) {
	    } else if (EnemyGData.hit == HIT_SUNK_LARGE_BOAT) {

	    } else if (EnemyGData.hit == HIT_SUNK_MEDIUM_BOAT) {

	    } else {
	    }
	}

	break;

    case AGENT_STATE_WAIT_FOR_GUESS:

	break;

    case AGENT_STATE_INVALID:
	switch (agent_type) {
	case messParsing:
	    OledClear(OLED_COLOR_BLACK);
	    OledDrawString(AGENT_ERROR_STRING_PARSING);
	    break;
	case NegData:
	    OledClear(OLED_COLOR_BLACK);
	    OledDrawString(AGENT_ERROR_STRING_NEG_DATA);
	    break;
	case Tie:
	    OledClear(OLED_COLOR_BLACK);
	    OledDrawString(AGENT_ERROR_STRING_ORDERING);
	    break;
	}
	OledUpdate();
	break;

    case AGENT_STATE_LOST:
	OledClear(OLED_COLOR_BLACK);
	OledDrawString("you lost! :(\n");
	OledUpdate();
	break;

    case AGENT_STATE_WON:
	OledClear(OLED_COLOR_BLACK);
	OledDrawString("you won! :)\n");
	OledUpdate();
	break;
    }
    return sizeof (outBuffer) / sizeof (*outBuffer);
}

uint8_t AgentGetStatus()
{

    return FieldGetBoatStates(&myField);
}

uint8_t AgentGetEnemyStatus()
{
    return FieldGetBoatStates(&enemyField);
}