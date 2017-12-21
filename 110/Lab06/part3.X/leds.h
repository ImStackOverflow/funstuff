/* 
 * File:   leds.h
 * Author: Gavin
 *
 * Created on February 23, 2016, 3:36 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#include "BOARD.h"
#include <xc.h>


#define LEDS_INIT() do {TRISE = 0x00, LATE = 0x00;} while(0)
#define LEDS_GET() LATE
#define LEDS_SET(x) LATE = x

#endif	/* LEDS_H */

