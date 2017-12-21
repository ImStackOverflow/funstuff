#include "Morse.h"
#include "Buttons.h"
#include "Tree.h"
#define LEVEL 6
#define DecodeReset message = star

typedef enum {
    waiting, dot, dash, letter
} fsm;
/****global varriables****/
Node *star, *message;

int MorseInit(void) //initializes tree star
{
    ButtonsInit();
    char p[(1 << LEVEL) - 1] = " eish54v#3uf####2arl#####wp#"
	    "#j#itndb6#x##kc##y##mgz7#q##o#8##90"; //formated data
    star = TreeCreate(LEVEL, p);
    if (star) {
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

char MorseDecode(MorseChar in) //uses temporary tree message
{
    MorseChar poop; //return value
    switch (in) {
    case MORSE_CHAR_DASH:
	message = message->rightChild;
	if (message->data != MORSE_CHAR_END_OF_CHAR) { //make sure still valid data
	    poop = SUCCESS;
	} else {
	    in = MORSE_CHAR_END_OF_CHAR; //if not valid
	}
	break;
    case MORSE_CHAR_DOT:
	message = message->leftChild;
	if (message->data != MORSE_CHAR_END_OF_CHAR) {
	    poop = SUCCESS;
	} else {
	    in = MORSE_CHAR_END_OF_CHAR;
	}
	break;
    case MORSE_CHAR_END_OF_CHAR:
	poop = message->data; //will return # if input is not valid
	break;
    case MORSE_CHAR_DECODE_RESET:
	message = star;
	poop = SUCCESS; //return reset to be handled in main()
	break;
    }
    return poop;
}

MorseEvent MorseCheckEvents(void)
{
    ButtonEventFlags butt = ButtonsCheckEvents();
    static fsm morse;
    MorseEvent back;
    static int timer;

    switch (morse) {

    case waiting:
	if (butt & BUTTON_EVENT_4DOWN) {
	    timer = 0;
	    butt = BUTTON_EVENT_NONE;
	    morse = dot;
	} else {
	    morse = waiting;
	}
	break;
    case dot:
	timer++;
	if (timer > MORSE_EVENT_LENGTH_DOWN_DOT) {//make dash if held for long time
	    morse = dash;

	} else if ((butt & BUTTON_EVENT_4UP) && (timer <= MORSE_EVENT_LENGTH_DOWN_DOT)) {//otherwise its a dot
	    butt = BUTTON_EVENT_NONE;
	    morse = letter;
	    timer = 0;
	    back = MORSE_EVENT_DOT; //return dot event
	} else {//otherwise keep checking if its a dot/dash
	    morse = dot;
	}
	break;
    case dash://button already held down for long period
	if (butt & BUTTON_EVENT_4UP) {//once button is released
	    butt = BUTTON_EVENT_NONE;
	    timer = 0;
	    morse = letter;
	    back = MORSE_EVENT_DASH;
	}
	break;
    case letter:
	//inter word state
	timer++;
	if (butt & BUTTON_EVENT_NONE && timer >= MORSE_EVENT_LENGTH_UP_INTER_WORD) {//if no action for long time
	    timer = 0;
	    morse = waiting;
	    back = MORSE_EVENT_INTER_WORD;
	}
	if (butt & BUTTON_EVENT_4DOWN) {
	    if (timer >= MORSE_EVENT_LENGTH_UP_INTER_LETTER) {
		timer = 0;
		butt = BUTTON_EVENT_NONE;
		morse = dot;
		back = MORSE_EVENT_INTER_LETTER;
	    } else {
		morse = dot;
		timer = 0;
	    }
	}
	break;
    }
    return back;
}