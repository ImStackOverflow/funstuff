// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "leds.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Adc.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdint.h>


// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timers, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define ON 1
#define OFF 0
#define LONG_PRESS 4
#define ever (;;)
#define BUTTON_RESET t2.event = 0; t2.counter = 0
#define b4_PRESS (check & BUTTON_EVENT_4DOWN)
#define b3_PRESS (check & BUTTON_EVENT_3DOWN)
// **** Declare any datatypes here ****

typedef enum {
    bake, toast, broil
} mode;

typedef enum { //fsm switch case
    reset, start, countdown, p_reset, change
} fsm;

typedef enum {
    time, temp
} pot;

typedef struct { //machine data
    int CookingTimeRemaining; //remaining time
    int CookingTimeStart; //user chosen time(0:00 - 4:15)
    int temp; //user chosen temp (300-555)
    fsm State; //logical state
    mode CookMode; //oven mode
    int BCount; //stores button data for switching between modes
    pot input; //pot affects time or temp
} oven;

typedef struct {
    uint8_t event;
    int counter;
} timer;

// **** Define any module-level, global, or external variables here ****
oven Oven; //machine data
timer t1;
timer t2;
timer t3;
ButtonEventFlags check;

// Configuration Bit settings
void DrawOven(int state);
void DrawInfo(int time);

int main()
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR1 to F_PB / 256 / 2 yields a 0.5s timer.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, BOARD_GetPBClock() / 256 / 2);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, BOARD_GetPBClock() / 256 / 5);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T3);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T3, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    OledInit();
    AdcInit();
    ButtonsInit();
    LEDS_INIT();
    BUTTON_RESET;
    int count = 0;

    Oven.State = reset;
    DrawOven(OFF);
    OledUpdate();
    LEDS_GET() = 0xFF;
    LEDS_SET(LEDS_GET());
    for ever {

	switch (Oven.State) {
	case reset: //sets all data to initial and then goes to start case
	    Oven.BCount = 0;
	    Oven.CookMode = bake;
	    Oven.CookingTimeRemaining = 0;
	    Oven.CookingTimeStart = 0;
	    Oven.State = start;
	    Oven.temp = 300;
	    Oven.input = time;
	    LEDS_GET() = 0xFF;
	    LEDS_SET(LEDS_GET());
	    check = ButtonsCheckEvents();
	    BUTTON_RESET;
	    break;
	case start:
	    if (AdcChanged()) {//if pot is changed
		switch (Oven.input) { //choose what pot is changing

		case time:
		    Oven.CookingTimeStart = ((int) AdcRead() / 4);
		    DrawInfo(Oven.CookingTimeStart);
		    DrawOven(OFF);
		    OledUpdate();
		    break;

		case temp:
		    Oven.temp = 300 + ((int) AdcRead() / 4);
		    DrawInfo(Oven.CookingTimeStart);
		    DrawOven(OFF);
		    OledUpdate();
		    break;
		}
	    }
	    if (check & BUTTON_EVENT_3DOWN)//button 3 is down
	    {
		BUTTON_RESET;
		Oven.input = temp;
		Oven.State = change;

	    }
	    if (check & BUTTON_EVENT_4DOWN)//button 4 is down
	    {
		TIMER_2HZ_RESET();
		BUTTON_RESET;
		Oven.CookingTimeRemaining = Oven.CookingTimeStart;
		DrawOven(ON);
		DrawInfo(Oven.CookingTimeStart);
		OledUpdate();
		Oven.State = countdown;
	    }

	    break;
	case countdown:
	    if (check & BUTTON_EVENT_4DOWN) {//button 4 down
		BUTTON_RESET;
		Oven.State = p_reset;
	    }

	    if (t1.event == 1 && Oven.CookingTimeRemaining == 0) {//ec
		//done counting down
		TIMER_2HZ_RESET();
		DrawInfo(Oven.CookingTimeRemaining);
		DrawOven(OFF);
		Oven.State = reset;
	    }

	    if (t1.event == 1 && Oven.CookingTimeRemaining > 0) {//counting down
		Oven.CookingTimeRemaining--;
		if (count == (Oven.CookingTimeStart / 8)) {
		    LEDS_SET(LEDS_GET() << 1);
		    count = 0;
		} else {
		    count++;
		}
		DrawInfo(Oven.CookingTimeRemaining);
		DrawOven(ON);
		OledUpdate();
		t1.event = OFF;
	    }

	    break;
	case p_reset:
	    if (t1.event == 1 && Oven.CookingTimeRemaining > 0) {
		Oven.CookingTimeRemaining--;
		if (count == (Oven.CookingTimeStart / 8)) {
		    LEDS_SET(LEDS_GET() << 1);
		    count = 0;
		} else {
		    count++;
		}
		t1.event = 0;
	    }
	    if (t2.event == 1) {//reset
		TIMER_2HZ_RESET(); //clear timer flag
		BUTTON_RESET;
		Oven.State = reset;

	    }
	    if (check & BUTTON_EVENT_4UP) {//b4 quick press
		BUTTON_RESET;
		Oven.State = countdown;
	    }
	    break;
	case change:
	    if (t2.event == 1) { //long press and hold
		if (Oven.input == time) {
		    Oven.input = temp;
		} else {
		    Oven.input = time;
		}
		BUTTON_RESET;
	    } else if (check & BUTTON_EVENT_3UP) { //reset button counter< long press && button event 3 up
		if (Oven.CookMode == broil) {
		    Oven.CookMode = bake;
		} else {
		    Oven.CookMode++;
		}
		BUTTON_RESET;
	    }
	    Oven.State = start;
	    break;
	}
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    while (1);
}

void __ISR(_TIMER_1_VECTOR, ipl4auto) TimerInterrupt2Hz(void)//.05 timer
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 4;
    if (t1.counter == 1) {
	t1.event = ON;
	t1.counter = 0;
    } else {
	t1.counter++;
    }

}

void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) //button hold down
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    if (t2.counter == LONG_PRESS) {
	t2.event = 1;
    } else {
	t2.counter++;
    }

}

void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) //button events
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    check = ButtonsCheckEvents(); //refresh check variable
}

void DrawOven(int state)
{
    int i, top, bottom, j;
    for (i = 0; i < 32; i += 8) {
	OledDrawChar(0, i, '|');
	OledDrawChar(45, i, '|');
    }
    if (state == ON) {
	top = 0x01;
	bottom = 0x03;
    } else {
	top = 0x02;
	bottom = 0x04;
    }
    for (j = 4; j <= 7 * 6; j += 6) {

	OledDrawChar(j, 0, top);
	OledDrawChar(j, 15, '-');
	OledDrawChar(j, 24, bottom);
    }


}

void DrawInfo(int time)
{
    char a[100], b[100];
    switch (Oven.CookMode) {
    case 0:
	OledDrawString("          Mode: bake\n");
	break;
    case 1:
	OledDrawString("          Mode: toast\n");
	break;
    case 2:
	OledDrawString("          Mode: broil\n");
	break;
    }
    if (time % 60 < 10) {
	sprintf(a, "\n          Time: %d:0%1d\n", time / 60, time % 60);
    } else {
	sprintf(a, "\n          Time: %d:%d\n", time / 60, time % 60);
    }
    OledDrawString(a);
    sprintf(b, "\n\n          Temp: %d %d %cF\n", Oven.State, t3.event, 0xF8);
    OledDrawString(b);
}
