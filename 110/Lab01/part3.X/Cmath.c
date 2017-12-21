#include "CMATH.h"

//float abs(float x);
float enorm(float px, float py, float qx, float qy);
float arctan(float x, float y);

//absolute value function
/*
float abs(float x)
{
    if (x < 0) {
	x *= -1;
    } else {
    }
    return x;
}
 */

//elucidian length function

float enorm(float px, float py, float qx, float qy)
{
    float g, e, t, r, s, x, y;
    int i;
    x = (px - py);
    y = (qy - py);
    x = abs(x);
    y = abs(y);
    if (x > y) {
	g = x;
	e = y;
    } else {
	g = y;
	e = x;
    }
    for (i = 0; i < 2; i++) {
	t = e / g;
	r = t*t;
	s = r / (4.0 + r);
	g = g + 2 * s*g;
	e = e*s;
    }
    return g;
}

//arctangent function  

float arctan(float x, float y)
{
    float r, theta;
    y = abs(y);
    if (x > 0) {
	r = (x - y) / (x + y);
	theta = (0.1963 * (r * r * r) - 0.9817 * (r)+(3 * 3.14159)) / 4;
    } else {
	r = (x + y) / (x - y);
	theta = (0.1963 * (r * r * r) - 0.9817 * (r)+(3 * 3.14159)) / 4;
    }
    if (y < 0) {
	theta *= -1;
    }
    return theta;
}