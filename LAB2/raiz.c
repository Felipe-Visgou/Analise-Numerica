#include <math.h>
#include <stdio.h>

double bissecao (double a, double b, int p, double (*f) (double x), double* x)
{
	double fa = f(a), fb = f(b), fc, c;
	double erro = (b-a)/2;
	int i = 1;
	double precision = 0.5*(pow(10.0, -p));
	if(fa*fb >= 0)
		return -1;
	while(erro >= precision)
	{
		c = (b+a)/2;
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
	*x = c;
	return fc;
}

double pontofixo(double x0, double epsilon, double (*g)(double x))
{
	double x1;
	double erro;
	x1 = g(x0);
	erro = x1 - x0;
	if(erro < 0)
		erro *= -1;
	while(erro > epsilon)
	{
		x0 = x1;
		x1 = g(x1);
		erro = x1-x0;
		if(erro < 0)
			erro *= -1;
	}
	return x1;
}
