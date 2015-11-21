#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double erroSimpson(double ab, double accb);
double Simpson (double a, double b, double (*f) (double x))
{
	double h = (b-a);
	double fa = f(a), fb = f(b);
	double ff = 4*f((a+b)/2);
	double ret;
	ret = (h/6)*(fa+ff+fb);
	return ret;
}
double DoubleSimpson (double a, double b, double (*f) (double x))
{
	double c = (a+b)/2;
	double h = (c-a);
	double fa = f(a), fb = f(b), fc = f(c);
	double f1 = 4*f((a+c)/2), f2 = 4*f((c+b)/2);
	double ret1 = (h/6)*(fa+f1+fc);
	double ret2;
	h = (b-c);
	ret2 = (h/6)*(fc + f2 + fb);
	return ret1 + ret2;
}
double AdaptiveSimpson (double a, double b, double (*f) (double x), double tol)
{
	double ab, accb;
	double erro;
	double c = (a+b)/2;
	ab = Simpson(a, b, f);
	accb = DoubleSimpson(a,b,f);
	erro = erroSimpson(ab, accb);
	if(fabs(erro) < tol)
		return accb;
	else
		return AdaptiveSimpson(a, c, f, tol/2) + AdaptiveSimpson(c, b, f, tol/2);
}
double erroSimpson(double ab, double accb)
{
	double erro = ab - accb;
	erro = erro*(16/15);
	return erro;
}