/* ************************************************************************** */
/** calculator

  @Company
 apllied aeromatics

  @File Name
 lab2.c

  @Summary
 basic calculator

  @Description
 * calculator that has basic operations (*,+,-,/) as well as temperature converter,
 *absolute value function, mean function, rounding fuction, and tangent function
 * 
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

double temp(double n1, char c1);
double avg(double n1, double n2);
double tangent(double n1);
double round(double n1);

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double temp(double n1, char c1) {
    double answer1;
    if (c1 == 'c') { //check desired operation, convert to celcius
        answer1 = (n1 - 32)*5 / 9;
    } else { //convert to farenheight
        answer1 = (n1 * 9 / 5) + 32;
    }
    return answer1;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double avg(double n1, double n2) {
    double answer1;
    answer1 = (n1 + n2) / 2;
    return answer1;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees (Note: Your tangent 
 * function relies on a call from the tangent function of math.h which uses 
 * radians).
 ********************************************************************************/
double tangent(double n1) {
    double answer1;
    n1 = M_PI * n1 / 180; //convert into radians
    answer1 = tanf(n1); //take tangent
    return answer1;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/

double round(double n1) {
    double n2, answer1;
    int type = 0;
    if (n1 < 0) { //incase number is negative
        n1 *= -1;
        type = 1;
    }
    n2 = n1 + .5; //add on .5
    if ((int) n2 < ((int) n1 + 1)) { // if adding .5 is still too low to get to next int
        if (type == 0) {
            answer1 = n1; //return lowest rounding number
        } else {
            answer1 = n1*-1; //if number is negative
        }
    } else { //if number is .5< away from next int
        if (type == 0) {
            answer1 = n2; //return lowest rounding number
        } else {
            answer1 = n2*-1; //if number is negative
        }
    }
    return (int) answer1;
}

/*********************************************************************************
 * Begin main part of program
 ********************************************************************************/

int main(void) {
    BOARD_Init();
    int check;
    double num1, num2, answer;
    char operation, ignore;

    printf("Hello friend! This is my calculator program.\n");

    //get and check validity of operation 
    do {
        printf("Input an operation buddy (+,-,*,/,v,a,c,f,t,r): "); //get operand
        scanf("%c%c", &operation, &ignore);

        if (operation != '+' && operation != '-' && operation != '*'
                && operation != '/' && operation != 'v' && operation != 'a'
                && operation != 'c' && operation != 'f' && operation != 't' && operation != 'r') //make sure operand is valid
        {
            printf("\nHow about you input a valid operation buddy\n");
            check = 0;

        } else {
            check = 1;
        }
    } while (check == 0);



    printf("\n Please input the first number my boi: ");
    scanf("%lf%c", &num1, &ignore);

    if (operation != 'a' && operation != 'c' && operation != 'f'
            && operation != 't' && operation != 'r')//make sure second number needed
    {
        printf("\n input the second number friend: "); //get second number
        scanf("%lf%c", &num2, &ignore);
    }



    //decision making
    switch (operation) { //check which operation user wants

        case '+': //addition
            answer = num1 + num2;
            break;

        case '-': //subtraction
            answer = num1 - num2;
            break;

        case '/': //division
            if (num1 == 0 || num2 == 0) {
                answer = 0;
            } else {
                answer = num1 / num2;
            }
            break;

        case '*': //multiplication
            answer = num1 * num2;
            break;

        case'v': //average
            answer = avg(num1, num2);
            break;

        case'a': //absolute value
            answer = abs(num1);
            break;

        case'c': // convert to celcius
            answer = temp(num1, operation);
            break;

        case 'f': //convert to farenheight
            answer = temp(num1, operation);
            break;

        case't': //tangent
            answer = tangent(num1);
            break;

        case'r': //rounding
            answer = round(num1);
            break;

        default:
            break;

    }
    if (operation != 'a' && operation != 'c' && operation != 'f' && operation != 't' && operation != 'r') {
        printf("\nThe result of (%f %c %f) = %f \n", num1, operation, num2, answer);
    } else {
        printf("\nThe result of (%f %c) = %f \n", num1, operation, answer);
    }


    while (1); //program doesn't seem to start from top 
    //for (;;); still won't start from top
}