#include <stdio.h>
#include <math.h>
#include "Brent.h"

double f1 (double x){
	return ( 4*cos(x) - exp(2*x) );
}

double f2 (double x){
	return ( (x/2) - tan(x) );
}

double f3 (double x){
	return ( 1 - ( x*log10(x+20) ) );
}

double f4 (double x){
	return ( pow(2, x) - 3*x );
}

double f5 (double x){
	return ( pow(x, 3) + x - 1 );
}

int main (void){
	printf("\n%f\n", brent(-1, 1, 3, &f1));
	printf("\n%f\n", brent(-1, 1, 3, &f2));
	printf("\n%f\n", brent(-1, 1, 3, &f3));
	printf("\n%f\n", brent(-1, 1, 3, &f4));
	printf("\n%f\n", brent(-1, 1, 3, &f5));
	return 0;
}