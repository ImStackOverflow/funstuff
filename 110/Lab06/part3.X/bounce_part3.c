// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "OledDriver.h"
#include "Oled.h"
#include "Buttons.h"
#include "leds.h"
// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdint.h>

// User libraries
#define ever (;;)
#define b4Lights 0xC0
#define b3Lights 0x30
#define b2Lights 0x0C
#define b1Lights 0x03

#define debug

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

typedef struct {
    int event;
    int state;
} butt;

butt buttons;

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_8, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    ButtonsInit();
    LEDS_INIT();
    LEDS_SET(0xFF);
    int shine = 0x00;
    for ever {
	if (buttons.event) {//if something happens to button

	    //check switch 1
	    if (!(SWITCH_STATES() & SWITCH_STATE_SW1)) { //if switch up
		if (buttons.state & BUTTON_EVENT_1UP) { //toggle lights using up event
		    shine ^= b1Lights; //toggle lights
		}
	    } else if (SWITCH_STATES() & SWITCH_STATE_SW1) { //if switch activated
		if (buttons.state & BUTTON_EVENT_1DOWN) {//toggle lights using down event
		    shine ^= b1Lights;
		}
	    }

	    //check switch 2
	    if (!(SWITCH_STATES() & SWITCH_STATE_SW2)) { //if switch up
		if ((buttons.state & BUTTON_EVENT_2UP)) { //toggle lights using up event
		    shine ^= b1Lights; //toggle lights
		}
	    } else if (SWITCH_STATES() & SWITCH_STATE_SW2) { //if switch activated
		if (buttons.state & BUTTON_EVENT_2DOWN) {//toggle lights using down event
		    shine ^= b1Lights;
		}
	    }

	    //check switch 3
	    if (!(SWITCH_STATES() & SWITCH_STATE_SW3)) { //if switch up
		if ((buttons.state & BUTTON_EVENT_3UP)) { //toggle lights using up event
		    shine ^= b1Lights; //toggle lights
		}
	    } else if (SWITCH_STATES() & SWITCH_STATE_SW3) { //if switch activated
		if (buttons.state & BUTTON_EVENT_3DOWN) {//toggle lights using down event
		    shine ^= b1Lights;
		}
	    }

	    //check switch 4
	    if (!(SWITCH_STATES() & SWITCH_STATE_SW4)) { //if switch up
		if ((buttons.state & BUTTON_EVENT_4UP)) { //toggle lights using up event
		    shine ^= b1Lights; //toggle lights
		}
	    } else if (SWITCH_STATES() & SWITCH_STATE_SW4) { //if switch activated
		if (buttons.state & BUTTON_EVENT_4DOWN) {//toggle lights using down event
		    shine ^= b1Lights;
		}
	    }
	    buttons.event = 0; //reset button event
	}
	LEDS_SET(shine);
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It checks for button events and stores them in a
 * module-level variable.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);
    if (buttons.state != ButtonsCheckEvents()) { //if theres a change
	buttons.state = ButtonsCheckEvents();
	buttons.event = 1;
    }
}