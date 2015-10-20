#include "poly.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592653589793
int main (void)
{
	Sample *s;
	double l1, l2, l3, n1, n2, n3;
	double erro_0, erro_1, erro_2;
	double *l, *coef;
	// a)
	s = Chebyshev(6, 0, PI/2, cos);
	erro_0 = (pow(((PI/2 - 0)/2), 6))/pow(2.0, 5)*(cos(0.0))/(5*4*3*2); // avaliado em x = 0
	erro_1 = (pow(((PI/2 - 0)/2), 6))/pow(2.0, 5)*(cos(PI/4))/(5*4*3*2);// avaliado em x = PI/4
	erro_2 = (pow(((PI/2 - 0)/2), 6))/pow(2.0, 5)*(cos(PI/2))/(5*4*3*2);// avaliado em x = PI/2
	// b)
	l = LagrangeCompute(s);
	// c)
	coef = NewtonCompute(s);
	// d)
	n1 = NewtonEval(s, coef, 0);
	l1 = LagrangeEval(s, l, 0);
	n2 = NewtonEval(s, coef, PI/4);
	l2 = LagrangeEval(s, l, PI/4);
	n3 = NewtonEval(s, coef, PI/2);
	l3 = LagrangeEval(s, l, PI/2);
	printf(" Lagrange - cos(0) \n");
	printf( "erro_0 = %g \n erro_atual = %g \n", erro_0, l1 - cos(0.0));
	printf("----------------------------- \n");
	printf(" Lagrange - cos(PI/4) \n");
	printf( "erro_1 = %g \n erro_atual = %g \n", erro_1, l2 - cos(PI/4));
	printf("----------------------------- \n");
	printf(" Lagrange - cos(PI/2) \n");
	printf( "erro_2 = %g \n erro_atual = %g \n", erro_2, l3 - cos(PI/2));
	printf("----------------------------- \n");
	printf("\n \n ");
	printf(" Newton - cos(0) \n");
	printf( "erro_0 = %g \n erro_atual = %g \n", erro_0, n1 - cos(0.0));
	printf("----------------------------- \n");
	printf(" Newton - cos(PI/4) \n");
	printf( "erro_1 = %g \n erro_atual = %g \n", erro_1, n2 - cos(PI/4));
	printf("----------------------------- \n");
	printf(" Newton - cos(PI/2) \n");
	printf( "erro_2 = %g \n erro_atual = %g \n", erro_2, n3 - cos(PI/2));
	printf("----------------------------- \n");
	return 0;
}