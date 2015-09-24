#include <math.h>
#include <stdio.h>
#include "raiz.h"

double function(double x)
{
	return sin(x) - pow(x, 3);
}

double pv(double m)
{
	return -35 + ((9.8*m)/15)*(1 - exp((-15/m)*9)); // isolar o M
}
double g(double x)
{
	return sqrt(1.8*x + 2.5);
}
double f(double x)
{
	return - pow(x, 2) + 1.8*x +2.5;	
}
int main (void)
{
	double r;
	double x;
	/* Exercicio 2 */
	r = bissecao(0.5, 1.5, 6, function, &x);
	printf("%.6g \n", r);

		/* Exercicio 3 */
	/*
	Para determinar a massa do paraquedista, pede-se que a main
	fosse alterada para imprimir seu valor, pra isso eu adicionei 
	mais um parâmetro na função de bissecao que passa o valor do double 'c' 
	como referência pois pv(c) = 0 (aproximação) , portanto c é a massa do paraquedista
	*/
	r = bissecao(30, 60, 6, pv,&x);
	printf(" massa do paraquedista : %.6g \n", x);

	/* Exercicio 5 */
	/* f(x) = x^2 + 1.8*x + 2.5
		isolando o x de duas formas temos que:
		g(x) -x = 0
		g(x) = sqrt(-1.8*x - 2.5);

		Usando g(x) para o metodo do ponto fixo */
		
	x = pontofixo(5, 0.0005, g);

	printf(" Ponto fixo da f(x) : %g \n", x);

	printf(" f(x) = %g \n", f(x));
	return 0;
}