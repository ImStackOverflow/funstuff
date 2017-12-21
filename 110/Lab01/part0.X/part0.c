/*
 * File:   part0.c
 * Author: Gavin
 *
 * Created on January 11, 2016, 12:03 PM
 */

#include "xc.h"
#include "BOARD.h"

int main(void)
{
    BOARD_Init();
    printf("hello world\n");
    while (1);
    return 0;
}
