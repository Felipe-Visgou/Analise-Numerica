#include <stdio.h>
#include <math.h>
#include "simpson.h"
#define PI 3.1415926535897932
double f1 (double x);
double f2 (double x);
double f3 (double x);
int main (void)
{
	double tol = 0.5 * pow(10.0, -5);
	printf(" \n Simpson Adaptativa \n ");
	printf(" Integral f1 [0,4] = %g \n", AdaptiveSimpson(0,4, f1, tol));
	printf(" Integral f2 [1,3] = %g \n", AdaptiveSimpson(1,3, f2, tol));
	printf(" Integral f3 [0,PI] = %g \n", AdaptiveSimpson(0,PI, f3, tol));
}
double f1 (double x)
{
	double a, b;
	a = sqrt(x*x + 9);
	b = x/a;
	return b;
}
double f2 (double x)
{
	double a, b;
	a = x*x;
	b = log(x);
	b *=a;
	return x*x*log(x);
}
double f3 (double x)
{
	double a, b;
	a = x*x;
	b = sin(x);
	b*=a;
	return b;
}