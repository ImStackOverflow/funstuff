// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BOARD_Init();

    float fahr, celsius, kelvin;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    kelvin = lower;

    printf("     F   C \n"); //header
    while (fahr <= upper) { //spacing between operator
	celsius = (5.0 / 9.0)*(fahr - 32.0); //spacing between operators
	printf("%7.1f %04.0f\n", (double) fahr, (double) celsius); //spacing between variables
	fahr = fahr + step; //spacing between operator
    }

    printf("\n"); //newline
    printf("  K      F \n"); //header
    while (kelvin <= upper) {
	fahr = (kelvin - 273.0)*1.8000 + 32.0; //fahrenheight to kelvin
	printf("%03.3f %5.6f\n", (double) kelvin, (double) fahr); //print table of conversions
	kelvin = kelvin + step; //move up one increment
    }
}
