#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
double _Y (double t );
double TimeToY1( double t0, double y0, double y1, double h, double (*f) (double t, double y));
struct sample {
	int n;		/* numero de amostras */
	double* y;	/* valores x das amostras*/
	double* x;	/* valores y das amostras */
};
double *deno;
typedef struct sample Sample;
Sample *s;
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
double RungeKutta(double t0, double t1, double h, double y0, double (*f) (double t, double y))
{
	double s1, s2, s3, s4;
	double i, p1, p2;
	for(i = t0; i <= t1; i = i+h )
	{
		s1 = h*f(i, y0);
		s2 = h*f(i + h/2, y0 + s1/2);
		s3 = h*f(i + h/2, y0 + s2/2);
		s4 = h*f(i + h, y0 + s3);
		p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
		y0 += p1;
	}
	return y0;
}
double f (double t, double y)
{
	return t*y + (t*t*t);
}
double f2(double t, double y)
{
	double a, b, r;
	r = sqrt((2*9.81)*(y+2));
	a = PI*0.25;
	b = 4*(LagrangeEval(s, deno, y));
	return (a/b)*r;
}

int main (void)
{
	double ret, h, t0 = 0, t1 = 2.4, y0 = -1, y1, t;
	double erro, x;
	double p;
	double *vy = (double*)malloc(sizeof(double)*7);
	double *vx = (double*)malloc(sizeof(double)*7);
	int i;
	s = (Sample*)malloc(sizeof(Sample));
	x = _Y(2.4);
	h = 0.1;
	printf("---------------- \n");
	printf("h = 0.1\n");
	ret = RungeKutta(t0, t1, h, y0, f);
	erro = (ret - x)/x;
	printf("y(2.4) = %g \n", ret);
	printf("erro relativo : %g \n", erro);
	printf("---------------- \n");
	h = 0.01;
	printf("h = 0.01 \n");
	ret = RungeKutta(t0, t1, h, y0, f);
	erro = (ret - x)/x;
	printf("y(2.4) = %g \n", ret);
	printf("erro relativo : %g \n", erro);
	printf("---------------- \n");
	h = 0.001;
	printf("h = 0.001 \n");
	ret = RungeKutta(t0, t1, h, y0, f);
	erro = (ret - x)/x;
	printf("y(2.4) = %g \n", ret);
	printf("erro relativo : %g \n \n \n", erro);
	printf("------TimeToY1------ \n");
	h = 0.1;
	t = TimeToY1(t0, y0, x, h, f);
	printf("Tempo necessario : %g \n", t);
	// letra b
	// definir os pontos da tabela A e seus valores de y na amostra
	s->n = 6;
	for(i = 6; i >= 0; i--)
		vx[i] = i;
	vy[6] = 0; vy[5] = 18; vy[4] =  32; vy[3] = 45; vy[2] = 67; vy[1] = 97; vy[0] = 117;
	s->x = vx;
	s->y = vy;
	deno = LagrangeCompute(s);
	// o tempo t0 = 0, queremos achar t1, y0 é a altura do reservatorio no t0, ou seja, 6, e y1 é a altura do reservatiorio no tempo final, ou seja, 0...
	t = TimeToY1(0, 0, 6, 0.1, f2);
	printf(" Tempo necessario para esvaziar %g \n", t);
	return 0;
}
double _Y (double t )
{
	double a, b;
	a = (t*t)/2;
	a = exp(a);
	return a - (t*t) - 2;
}
double TimeToY1( double t0, double y0, double y1, double h, double (*f) (double t, double y))
{
	double s1, s2, s3, s4;
	double i,j, p1, dt, yn, a, b;
	for(i = t0; y0 <= y1; i = i+h )
	{
		yn = y0;
		s1 = h*f(i, y0);
		s2 = h*f(i + h/2, y0 + s1/2);
		s3 = h*f(i + h/2, y0 + s2/2);
		s4 = h*f(i + h, y0 + s3);
		p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
		y0 += p1;
	}
	// interpol
	// regra de 3
	a = (y1 - yn)*h;
	b = (y0 - yn);
	dt = a/b;
	return (i - h) + dt;
}