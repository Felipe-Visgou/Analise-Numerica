#include <math.h>
#include <stdio.h>
#include "raiz2.h"
double f(double x)
{
	return sin(x) - (x*x*x);
}
double fl(double x)
{
	return cos(x) - 3*(x*x);
}
int main (void)
{
	double raiz;
	int it;
	it = falsaposicao(0.5, 1.5, 6, f, &raiz);
	// falsa Posi��o
	printf(" Falsa Posicao \n");
	printf(" Numero de iteracoes : %d \n Valor da raiz %g \n", it, raiz);
	// newtonn raphson
	it = newtonraphson(1.5, 6, f, fl, &raiz);
	printf(" Newton Raphson \n");
	printf(" Numero de iteracoes : %d \n Valor da raiz %g \n", it, raiz);
	/* O m�todo de Newton Raphson conseguiu uma precis�o menor que a pedida em somente 5 itera��es, 
	j� o m�todo da falsa posi��o precisou de 22 itera��es*/
	return 0;
}
