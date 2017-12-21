#include "Ascii.h"
#include "BOARD.h"
#include "Oled.h"
#include "OledDriver.h"

int main (void){
    OledInit();
    OledDrawString("Hello World!\nI'm Working!\nYayyyyyyy!\n");
    OledUpdate();
    while(1);
}