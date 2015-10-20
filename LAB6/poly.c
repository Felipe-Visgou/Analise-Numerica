#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poly.h"
#define PI 3.141592653589793

struct sample {
	int n;		/* numero de amostras */
	double* y;	/* valores x das amostras*/
	double* x;	/* valores y das amostras */
};

/* Funções auxiliares */

/* diferença de newton */
double diff (Sample* s, int i, int j)
{
	if(i == j)
	{
		return s->y[i];
	}
	else
	{
		return (diff(s,i+1, j) - diff(s,i, j-1))/(s->y[j] - s->y[i]);
	}
}
Sample* Chebyshev(int n, double a, double b, double (*f)(double x))
{
	int k;
	double bpa,bma;
	Sample *s = (Sample*)malloc(sizeof(Sample));
	double *x =(double*)malloc((n-1)*sizeof(double)) , *y = (double*)malloc((n-1)*sizeof(double));
	bma=0.5*(b-a);
	bpa=0.5*(b+a);
	for (k=0;k<n;k++)
	{
		x[k]=cos(PI*(k+0.5)/n);
		y[k]=(*f)(x[k]*bma+bpa);
	}
	s->n = n;
	s->x = x;
	s->y = y;
	return s;
}
double* LagrangeCompute (Sample* s)
{
	double* den = (double*)malloc((s->n)*sizeof(double));
	int i, j;
	for(i = 0; i < s->n; i ++)
	{
		den[i] = 1;
		for(j = 0; j < s->n; j++)
		{
			if(i != j)
				den[i] *= s->x[i] - s->x[j];
		}
	}
	return den;
}
double LagrangeEval (Sample*s, double* den, double x)
{
	int i, j;
	double p = 0;
	double* Lk = (double*)malloc(s->n * sizeof(double));
	double* num = (double*)malloc((s->n)*sizeof(double));
	for(i = 0; i < s->n; i ++)
	{
		num[i] = 1;
		for(j = 0; j < s->n; j++)
		{
			if(i != j)
				num[i] *=  x - s->x[j];
		}
	}
	/* Lk(x) */
	for(i = 0; i < s->n; i++)
		Lk[i] = num[i] / den[i];
	/* Pn-1(x) */
	for(i = 0; i < s->n; i++)
		p +=s->y[i]*Lk[i];
	return p;
}
double* NewtonCompute (Sample* s)
{
	double* b = (double*)malloc(s->n * sizeof(double));
	int i, j;
	for( i = 0; i < s->n; i++)
	{
		for(j = 0; j < s->n; j++)
				b[i] = diff(s, i, j);
	}
	return b;
}
double NewtonEval (Sample* s, double* coef, double x)
{
	double p = 0, mult, paux;
	int i, j;
	for(i = 0; i < s->n; i++)
	{
		mult = 1;
		for(j = 0; j < i; j++)
		{
			mult*=(x-s->x[j]);
		}
		paux = coef[i] * mult;
		p +=paux;
	}
	return p;
}