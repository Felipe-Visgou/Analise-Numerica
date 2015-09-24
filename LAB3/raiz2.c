#include <math.h>
#include <stdio.h>

int falsaposicao( double a, double b, int p, double (*f)(double x), double * r)
{
	double fa = f(a), fb = f(b), fc, c;
	double erro = (b-a)/2;
	int i = 0;
	double precision = 0.5*(pow(10.0, -p));
	if(fa*fb >= 0)
		return -1;
	while(erro >= precision)
	{
		c = a - (fa*(b-a)/(fb-fa));
		fc = f(c);
		if(fc * fa > 0)
		{
			fa = fc;
			a = c;
		}
		else
		{
			fb = fc;
			b = c;
		}
		erro = (b-a)/pow(2.0, i);
		i++;
	}
	*r = c;
	return i;
}
int newtonraphson( double x0, int p, double (*f)(double x), double (*fl)(double x), double * r)
{ 

	double xi, fxi;
	double precisao = 0.5*(pow(10.0, -p));
	double fx = f(x0);
	int i = 0;
	if(fx < 0) fx= fx*-1;
	while(fx > precisao)
	{
		xi = x0 - (f(x0)/fl(x0));
		fx = f(xi);
		x0 = xi;
		i++;
		if(fx < 0) fx= fx*-1;
	}
	*r = x0;
	return i;
}

