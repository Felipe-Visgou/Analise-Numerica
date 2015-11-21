#include <math.h>
#include <stdio.h>
#define PI 3.141592653589793238
double integralPontoMedio(double a, double b, double (*f) (double x), int m);
double integralSimpson(double a, double b, double (*f) (double x), int m);
double f1 (double x);
double f2 (double x);
double f3 (double x);
/*int main (void)
{
	double I1, I2, I3;
	printf("Integral: \n");
	// m = 16
	I1 = integralSimpson(0, 4, f1, 16);
	I2 = integralSimpson(1, 3, f2, 16);
	I3 = integralSimpson(0, PI, f3, 16);
	printf(" Regra de Simpson ( M = 16 )\n");
	printf("f3 : %g \n", I1);
	printf("f2 : %g \n", I2);
	printf("f3 : %g \n", I3);
	I1 = integralPontoMedio(0, 4, f1, 16);
	I2 = integralPontoMedio(1, 3, f2, 16);
	I3 = integralPontoMedio(0, PI, f3, 16);
	printf(" Regra do Ponto Medio ( M = 16 ) \n");
	printf("f3 : %g \n", I1);
	printf("f2 : %g \n", I2);
	printf("f3 : %g \n", I3);
	// m = 32
	I1 = integralSimpson(0, 4, f1, 32);
	I2 = integralSimpson(1, 3, f2, 32);
	I3 = integralSimpson(0, PI, f3, 32);
	printf(" Regra de Simpson ( M = 32 )\n");
	printf("f3 : %g \n", I1);
	printf("f2 : %g \n", I2);
	printf("f3 : %g \n", I3);
	I1 = integralPontoMedio(0, 4, f1, 32);
	I2 = integralPontoMedio(1, 3, f2, 32);
	I3 = integralPontoMedio(0, PI, f3, 32);
	printf(" Regra do Ponto Medio ( M = 32 ) \n");
	printf("f3 : %g \n", I1);
	printf("f2 : %g \n", I2);
	printf("f3 : %g \n", I3);
	return 0;
}*/
double integralPontoMedio(double a, double b, double (*f) (double x), int m)
{
	int i;
	double h = (b-a);
	double sum = 0;
	double x1, x0;
	h = h/m;
	for(i = 1; i <= m; i++)
	{
		x1 = a+ h*i;
		x0 = a+h*(i-1);
		sum+=f((x1 + x0)/2);
	}
	return h*sum;
}
double integralSimpson(double a, double b, double (*f) (double x), int m)
{
	int i;
	double sumimpar = 0, sumpar = 0;
	//double h = (b-a)/(2*m);
	double h = (b-a);
	double x0, x1;
	h /= 2*m;
	for(i = 1; i <= m; i++)
	{
		x0 = a+h*2*(i-1);
		sumimpar+=f(x0);
	}
	for(i = 1; i < m; i++)
	{
		x1 = a+h*2*i;
		sumpar+= f(x1);
	}
	return (h/3)*(f(a) + f(b) + 4*sumimpar + 2*sumpar);
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