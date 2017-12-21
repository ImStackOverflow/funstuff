// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"
#include "Morse.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>


// **** Set any macros or preprocessor directives here ****
// Specify a bit mask for setting/clearing the pin corresponding to BTN4. Should only be used when
// unit testing the Morse event checker.
#define BUTTON4_STATE_FLAG (1 << 7)
#define width 21

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
char characters[width], topline[width];
int j, x;
MorseEvent check;

// **** Declare any function prototypes here ****
void cleartop(void);
void addDotDash(MorseChar add);
void addChar(char add);

int main()
{
    BOARD_Init();


    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    MorseInit();
    OledInit();
    OledDrawString(characters);
    OledUpdate();
    for (;;) {
	switch (check) {

	case MORSE_EVENT_DASH:
	    addDotDash(MORSE_EVENT_DASH);
	    MorseDecode(MORSE_CHAR_DASH);
	    break;

	case MORSE_EVENT_DOT:
	    addDotDash(MORSE_CHAR_DOT);
	    MorseDecode(MORSE_CHAR_DOT);
	    break;

	case MORSE_EVENT_NONE:
	    addChar('a');
	    break;

	case MORSE_EVENT_INTER_LETTER:
	    addChar(MorseDecode(MORSE_CHAR_END_OF_CHAR));
	    break;

	case MORSE_EVENT_INTER_WORD:
	    addChar(' ');
	    break;
	}
	OledUpdate();
    }




    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     *****************************************************************************/

    while (1);
}

void cleartop(void) //resets top line (dots and dashes)
{
    char res[width];
    int i;
    for (i = 0; i < 21; i++) {
	res[i] = '\0';
    }
    OledDrawString(res);
    OledUpdate();
}

void addChar(char add) //resets top line and prints character
{
    cleartop();
    characters[++j] = add;
    OledDrawString(characters);
    OledUpdate();
}

void addDotDash(MorseChar add)//prints dot and dash on top line 
{
    topline[++x] = add;
    if (add == MORSE_CHAR_DASH || add == MORSE_CHAR_DOT) {//only print if char is dot or dash
	OledDrawString(topline);
	OledUpdate();
    }
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void)
{//.01 sec
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    //******** Put your code here *************//
    check = MorseCheckEvents();

}
