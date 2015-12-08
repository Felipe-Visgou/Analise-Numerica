#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
#define G 9.80665 /* aceleração da gravidade */
#define theta0 PI/8 /* Mudar o valor de theta0 AQUI para diferentes avalizações */
#define l 0.5 /* Comprimento da corda do pêndulo */
struct MC {
	double w; /* Velocidade */
	double s; /* Posição */
};
typedef struct MC mc;
double RungeKutta(double t0, double t1, double h, double y0, double w0, double (*f) (double y), mc * p) /* A estrutura passada por referência foi adicionada para armazenar cada estado da partícula */
{
	double s1, s2, s3, s4, y1, k1, k2, k3, k4, w1; /*k é a velocidade e s é a posição theta */
	double i, p1, p2, j;
	/* iteração de Runge-Kutta acoplada */
	for(i = t0; i <= t1; i = i+h )
	{
		/* Realiza um passo inteiro */
		y1 = y0;
		w1 = w0;
		s1 = h*w0;
		k1 = h*f(y0);
		s2 = h*(w0 + k1/2);
		k2 = h*f(y0 + s1/2);
		s3 = h*(w0 + k2/2);
		k3 = h*f(y0 + s2/2);
		s4 = h*(w0 + k3);
		k4 = h*f(y0 + s3);
		p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
		p2 = (1/6.0)*(k1 + 2*k2 + 2*k3 + k4);
		y0 +=p1;
		w0 +=p2;

		h = h/2;

		/* realiza dois meio-passos */
		for(j = 0; j < 2; j++)
		{
			s1 = h*w1;
			k1 = h*f(y1);
			s2 = h*(w1 + k1/2);
			k2 = h*f( y1 + s1/2);
			s3 = h*(w1 + k2/2);
			k3 = h*f( y1 + s2/2);
			s4 = h*(w1 + k3);
			k4 = h*f(y1 + s3);
			p1 = (1/6.0)*(s1 + 2*s2 + 2*s3 + s4);
			p2 = (1/6.0)*(k1 + 2*k2 + 2*k3 + k4);
			y1 += p1;
			w1 += p2;
		}
		h *= 2;
		/* se o erro for menor que 10^-5 o passo é diivido */
		if(fabs(y1 - y0) >= pow(10.0,-5))
			h = h/2;
	}
	/* atualiza a estrutura */
	p->s = y0; 
	p->w = w0; 
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
double f(double theta)
{
	double a;
	a = -(G/l)*sin(theta);
	return a;
}
int main (void)
{
	FILE* fp1 = fopen("saida1.txt", "w"); /* Valores de theta para o Runge-Kutta adaptativo */
	FILE* fp2 = fopen("saida2.txt", "w"); /* Valores da velocidade em cada ponto */
	FILE* fp3 = fopen("saida3.txt", "w"); /* Valores de theta para a solução analítica */
	FILE* fp4 = fopen("saida4.txt", "w"); /* passos feitos (período) */
	mc * particula = (mc*)malloc(sizeof(mc));
	double i=0, result1, T,v1, v2, h = 0.0001;
	int flag = 0;
	particula->s = 0;
	particula->w = 0;
	T = 2*PI*(sqrt(l/G));
	printf("T : %g \n", T);
	do	
	{
		v1 = particula->w; /* velocidade anterior */
		fprintf(fp4,"%g\n", i);
		result1 = RungeKutta(0, i, h, theta0, 0.0, f, particula);
		fprintf(fp1,"%g\n", particula->s);
		fprintf(fp2,"%g\n", particula->w);
		fprintf(fp3,"%g\n", theta_T(theta0, i, l));
		v2 = particula->w; /* Nova velocidade */
		i+=0.01;
		if(v1*v2<0) flag++; /* quando a velocidade trocar de sinal a flag é incrementada */
	}while(flag != 2); /* quando a velocidade trocar de sinal duas vezes então um período foi completo */
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	return 0;
}

