#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
#define G 9.80665
#define theta0 22.5
#define l 0.5
/* Método de Runge-Kutta*/
// y'(t) = f(t,y(t))
double RungeKutta(double t0, double t1, double h, double y0, double (*f) (double t, double y))
{
	double s1, s2, s3, s4, y1;
	double i, p1, p2, j;
	for(i = t0; i <= t1; i = i+h )
	{
		y1 = y0;
		s1 = h*f(i, y0);
		s2 = h*f(i + h/2, y0 + s1/2);
		s3 = h*f(i + h/2, y0 + s2/2);
		s4 = h*f(i + h, y0 + s3);
		p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
		y0 += p1;
		h = h/2;
		for(j = 0; j < 2; j++)
		{
			s1 = h*f(i, y1);
			s2 = h*f(i + h/2, y1 + s1/2);
			s3 = h*f(i + h/2, y1 + s2/2);
			s4 = h*f(i + h, y1 + s3);
			p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
			y1 += p1;
		}
		h *= 2;
		if(fabs(y1 - y0) >= pow(10.0,-5))
			h = h/2;
	}
	return y0;
}
double theta_T(double thetaI, double t, double length)
{
	double p;
	p = sqrt((G/length))*t;
	p = cos(p);
	p = thetaI*p;
	return p;
}
double v(double t, double theta)
{
	double a,b;
	a = -G/l;
	b = theta;
	return a*b;
}

double f(double t,double theta)
{
		double a,b,c;
	//return (-G/l)*theta;
	a = sqrt(G/l);
	b = sin(t*a);
	c = -theta0*a*b;
	return c;
	/*a = cos(theta) - cos(theta0);
	b = ((2*G)/l);
	c = a*b;
	return sqrt(c);*/
}
int main (void)
{
	FILE* fp1 = fopen("saida1(22.5).txt", "w");
	FILE* fp2 = fopen("saida2(22.5).txt", "w");
	FILE* fp3 = fopen("saida3.txt", "w");
	double i, result1, result2, result3, T, h = 0.1;
	T = 2*PI*(sqrt(l/G));
	printf("T : %g \n", T);
	// RUNGE-KUTTA
	//result1 = RungeKutta(0, T, 0.1, theta0, f);
	//result2 =  theta_T(0.1, T, lenght);
	//printf("resultado 1 (runge-kutta) = %g \n", result1);
	//printf("resultado 2   (analitico) = %g \n", result2);
	for(i = 0; i < T; i = i+0.05)	
	{
		fprintf(fp3,"%g\n", i);
		result1 = RungeKutta(0, i, h, theta0, f);
		fprintf(fp1,"%g\n", result1);
		fprintf(fp2,"%g\n", theta_T(theta0, i, l));
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
		return 0;
}

