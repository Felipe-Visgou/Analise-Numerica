#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void derivada(double (*f) (double x), double valor)
{
	int i;
	double h, fl1, fl2, erro, E;
	for( i = 1; i <=12; i++)
	{
		printf(" %d ---------------------- \n", i);
		h = pow(10.0, -i);
		fl1 = (f(valor + h) - f(valor - h))/(2*h); // derivada aproximada
		fl2 = -1/(pow((1+valor), 2)); // derivada analitica
		erro = fl1 - fl2;
		E = ((h*h)/6)*(-6/(pow((2.0), 4))) + (2.220446*(pow(10.0, -16)))/h;
		printf("h = %g \n", h);
		printf("Derivada aproximada %g  \nDerivada analitica %g \n \nerro encontrado %g \nerro teorico %g \n", fl1, fl2, erro, E);

	}
}


double f (double x)
{
	return 1/(1+x);
}
int main (void)
{
	derivada(f, 1);
	return 0;
}
