
#include "Protocol.h"
#include "BOARD.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define mess_size(x) sizeof (x) / sizeof (*x)

int makeCheckSum(uint8_t data);

typedef enum {
    hit, cord, challenge, determine
} message_type;

typedef enum {
    waitin = 1, reading, first_checksum, second_checksum
} state;

/****global varriables****/

int ProtocolEncodeCooMessage(char *message, const GuessData *data)
{
    int c1, c2;

    char payload[PROTOCOL_MAX_PAYLOAD_LEN];

    if (sprintf(payload, PAYLOAD_TEMPLATE_COO, data->row, data->col) > 0) {//generate data message

	/***generate checksum****/
	union split { //split char into nibbles for hex
	    char start;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
	    };

	} split;

	//generate first half of checksum with message type
	split.start = 'C';
	c1 = split.first ^ split.second;
	split.start = 'O';
	c1 ^= (split.first ^ split.second);

	union chop {//split int into nibbles for hex
	    int number;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
		uint8_t third : 4;
		uint8_t fourth : 4;
	    };
	} chop;

	//generate second half of checksum using data
	chop.number = data->row;
	c2 = chop.first ^ chop.second ^ chop.third ^ chop.fourth;
	chop.number = data->col;
	c2 ^= chop.first ^ chop.second ^ chop.third ^ chop.fourth;

	//checksum = concatenation
	int checksum = c1 << 1 | c2;
	sprintf(message, MESSAGE_TEMPLATE, payload, checksum);
	return mess_size(message); //return length of message data
    } else {
	return STANDARD_ERROR;
    }
}

int ProtocolEncodeHitMessage(char *message, const GuessData * data)
{
    int c1, c2;

    char payload[PROTOCOL_MAX_PAYLOAD_LEN];
    if (sprintf(payload, PAYLOAD_TEMPLATE_HIT, data->row, data->col, data->hit) > 0) {//generate data message

	union split { //split char into nibbles for hex
	    char start;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
	    };

	} split;

	//generate first half of checksum with message type
	split.start = 'H';
	c1 = split.first ^ split.second;
	split.start = 'I';
	c1 ^= (split.first ^ split.second);
	split.start = 'T';
	c1 ^= (split.first ^ split.second);

	union chop {//split int into nibbles for hex
	    int number;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
		uint8_t third : 4;
		uint8_t fourth : 4;
	    };
	} chop;

	//generate second half of checksum using data
	chop.number = data->row;
	c2 = chop.first ^ chop.second ^ chop.third ^ chop.fourth;
	chop.number = data->col;
	c2 ^= chop.first ^ chop.second ^ chop.third ^ chop.fourth;
	chop.number = data->hit;
	c2 ^= chop.first ^ chop.second ^ chop.third ^ chop.fourth;

	int checksum = c1 << 1 | c2;
	sprintf(message, MESSAGE_TEMPLATE, payload, checksum);
	return mess_size(message); //return length of message data
    } else {
	return STANDARD_ERROR;
    }
}

int ProtocolEncodeChaMessage(char *message, const NegotiationData * data)
{
    int c1, c2;

    char payload[PROTOCOL_MAX_PAYLOAD_LEN];

    if (sprintf(payload, PAYLOAD_TEMPLATE_CHA, data->encryptedGuess, data->hash) > 0) {//generate data message

	union split { //split char into nibbles for hex
	    char start;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
	    };

	} split;

	//generate first half of checksum with message type
	split.start = 'C';
	c1 = split.first ^ split.second;
	split.start = 'H';
	c1 ^= (split.first ^ split.second);
	split.start = 'A';
	c1 ^= (split.first ^ split.second);

	union chop {//split int into nibbles for hex
	    int number;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
		uint8_t third : 4;
		uint8_t fourth : 4;
	    };
	} chop;

	//generate second half of checksum using data
	chop.number = data->encryptedGuess;
	c2 = chop.first ^ chop.second ^ chop.third ^ chop.fourth;
	chop.number = data->hash;
	c2 ^= chop.first ^ chop.second ^ chop.third ^ chop.fourth;

	//checksum = concatenation
	int checksum = c1 << 1 | c2;
	sprintf(message, MESSAGE_TEMPLATE, payload, checksum);
	return mess_size(message); //return length of message data
    } else {
	return STANDARD_ERROR;
    }
}

int ProtocolEncodeDetMessage(char *message, const NegotiationData * data)
{
    int c1, c2;
    char payload[PROTOCOL_MAX_PAYLOAD_LEN];

    if (sprintf(payload, PAYLOAD_TEMPLATE_DET, data->guess, data->encryptionKey) > 0) {//generate data message

	union split { //split char into nibbles for hex
	    char start;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
	    };

	} split;

	//generate first half of checksum with message type
	split.start = 'D';
	c1 = split.first ^ split.second;
	split.start = 'E';
	c1 ^= (split.first ^ split.second);
	split.start = 'T';
	c1 ^= (split.first ^ split.second);

	union chop {//split int into nibbles for hex
	    int number;

	    struct {
		uint8_t first : 4;
		uint8_t second : 4;
		uint8_t third : 4;
		uint8_t fourth : 4;
	    };
	} chop;

	//generate second half of checksum using data
	chop.number = data->guess;
	c2 = chop.first ^ chop.second ^ chop.third ^ chop.fourth;
	chop.number = data->encryptionKey;
	c2 ^= chop.first ^ chop.second ^ chop.third ^ chop.fourth;

	//checksum = concatenation
	int checksum = c1 << 1 | c2;
	sprintf(message, MESSAGE_TEMPLATE, payload, checksum);
	return mess_size(message); //return length of message data
    } else {
	return STANDARD_ERROR;
    }
}

ProtocolParserStatus ProtocolDecode(char in, NegotiationData *nData, GuessData * gData)
{

    ProtocolParserStatus poop; //return value
    int checksum;
    static state check = waitin;
    static int index1 = 0, digits[10], j = 0, data[10], index2 = 0;
    static char message[10];
    static message_type mess;

    switch (check) {
    case waitin:
	if (in == '$') {//make sure message begins with $
	    check = reading;
	    poop = PROTOCOL_PARSING_GOOD;
	} else {//otherwise default out
	    poop = PROTOCOL_WAITING;
	}
	break;
    case reading:
	if (in != '*') {
	    if (in != ',') {
		char compare[] = "1234567890";
		if (strchr(compare, in) == NULL) {//check if char is letter
		    message[index1++] = in;
		} else {//otherwise char is number
		    char *out = &in;
		    digits[j++] = (int) atof(out); //store in temporary array until all digits recieved
		    return PROTOCOL_PARSING_GOOD;
		}
	    } else {//all data proceding comma recieved
		int initial = j; //for setting correct tens place of number
		check = 0; //temporarily store final number
		int i;
		for (i = 0; i < j; i++) {//convert single digits into total number
		    check += digits[i] * (pow(10, --initial));
		}
		data[index2++] = check;
		j = 0; //reset
		check = reading; //reset
		return PROTOCOL_PARSING_GOOD;
	    }
	} else {//add final piece of data before *
	    int initial = j;
	    check = 0;
	    int i;
	    for (i = 0; i < j; i++) {
		check += digits[i] * (pow(10, --initial));
	    }
	    data[index2++] = check;
	    j = 0;
	    check = first_checksum;
	    return PROTOCOL_PARSING_GOOD;
	}
	break;

    case first_checksum: //check first checksum half & determine type of message
	checksum = makeCheckSum(message[0])
		^ makeCheckSum(message[1])
		^ makeCheckSum(message[2]);
	if (in == checksum) {//checksum checks out
	    if (message[0] == 'H') {
		mess = hit;
	    } else if (message[0] == 'D') {
		mess = determine;
	    } else if (message[0] == 'C') {
		if (message[1] == 'H') {
		    mess = challenge;
		} else {
		    mess = cord;
		}
	    }
	    check = second_checksum; //move onto next stage
	    return PROTOCOL_PARSING_GOOD;
	} else {//message not recieved correctly
	    return PROTOCOL_PARSING_FAILURE;
	}
	break;

    case second_checksum://check second checksum half and append data into correct struct

	switch (mess) {

	case hit:
	    checksum = makeCheckSum(data[0])
		    ^ makeCheckSum(data[1])
		    ^ makeCheckSum(data[2]);
	    if (in == checksum) {//check checksum
		gData->row = data[0];
		gData->col = data[1];
		gData->hit = data[2];
		poop = PROTOCOL_PARSED_HIT_MESSAGE;
	    } else {
		poop = PROTOCOL_PARSING_FAILURE;
	    }
	    break;

	case cord:
	    checksum = makeCheckSum(data[0])
		    ^ makeCheckSum(data[1]);
	    if (in == checksum) {//check checksum
		gData->row = data[0];
		gData->col = data[1];
		poop = PROTOCOL_PARSED_COO_MESSAGE;
	    } else {
		poop = PROTOCOL_PARSING_FAILURE;
	    }
	    break;

	case challenge:
	    checksum = makeCheckSum(data[0])
		    ^ makeCheckSum(data[1]);
	    if (in == checksum) {//check checksum
		nData->encryptedGuess = data[0];
		nData->hash = data[1];
		poop = PROTOCOL_PARSED_CHA_MESSAGE;
	    } else {
		poop = PROTOCOL_PARSING_FAILURE;
	    }
	    break;

	case determine:
	    checksum = makeCheckSum(data[0])
		    ^ makeCheckSum(data[1]);
	    if (in == checksum) {//check checksum
		nData->guess = data[0];
		nData->encryptionKey = data[1];
		poop = PROTOCOL_PARSED_DET_MESSAGE;
	    } else {
		poop = PROTOCOL_PARSING_FAILURE;
	    }
	    break;

	default:

	    break;
	}
	//reset
	index1 = 0;
	index2 = 0;
	j = 0;
	check = waitin;
	break;
    default:
	poop = PROTOCOL_PARSING_FAILURE;
	break;
    }
    return poop;
}

void ProtocolGenerateNegotiationData(NegotiationData * data)
{

    union split { //to split 16 bits into bytes

	uint16_t number;
	char split[2];
    } split;
    data->guess = rand();
    data->encryptionKey = rand();
    data->encryptedGuess = data->guess ^ data->encryptionKey;
    split.number = data->guess; //split guess
    data->hash = split.split[0] ^ split.split[1]; //first half of hash
    split.number = data->encryptionKey; //split encryption key
    data->hash ^= (split.split[0] ^ split.split[1]); //second half of hash
}

uint8_t ProtocolValidateNegotiationData(const NegotiationData * data)
{

    union split { //to split 16 bits into bytes
	uint16_t number;
	char split[2];
    } split;
    uint16_t check;

    //generate hash from recievied data
    split.number = data->guess;
    check = split.split[0] ^ split.split[1];
    split.number = data->encryptionKey;
    check ^= (split.split[0]^split.split[1]);

    if (check == data->hash) { //check if generated hash matches sent hash
	return 1;
    } else {

	return 0;
    }
}

TurnOrder ProtocolGetTurnOrder(const NegotiationData *myData, const NegotiationData * oppData)
{
    TurnOrder poop;
    short turn = ((myData->encryptionKey ^ oppData->encryptionKey) & 0x01);
    if (turn) {//greater nunmber goes first
	if (myData->guess > oppData->guess) {
	    poop = TURN_ORDER_START;
	} else if (myData->guess == oppData->guess) {
	    poop = TURN_ORDER_TIE;
	} else {
	    poop = TURN_ORDER_DEFER;
	}
    } else {//lesser number goes first
	if (myData->guess < oppData->guess) {
	    poop = TURN_ORDER_START;
	} else if (myData->guess == oppData->guess) {
	    poop = TURN_ORDER_TIE;
	} else {
	    poop = TURN_ORDER_DEFER;
	}
    }
    return poop;
}

int makeCheckSum(uint8_t data)
{
    int firstHalf = data >> 4;
    int checksum = data^firstHalf;
    checksum &= 0x0F;
    return checksum;
}