/*
 * File:   part3.c
 * Author: Gavin
 *
 * Created on January 14, 2016, 4:12 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "CMATH.H"

int main(void) {

    //begin arctangent calculation

    //"the arctangent of 69 and 420 is:
    printf("the arctangent of 14 and 45 is: %f\n", (double) arctan(14, 45));


    //begin elucidian length calculation

    //"the elucidian length of 23,24,25,26 is: 
    printf("the elucidian length of 22,24,40,26 is: %f\n", (double) enorm(22, 24, 40, 26));


    return (0);
    while (1);

}
