#include <stdio.h>
int main (void)
{
	double a = 2.3, b = 2.0, c = 0.3;
	printf("2.3 - 2 - 0.3 = %.16g \n", a - b - c);
	return 0;
}
/*	0.3 x 2 = 0.6
	0.6 x 2 = 1.2
	0.2 x 2 = 0.4
	0.4 x 2 = 0.8
	0.8 x 2 = 1.6
	0.6 x 2 = 1.2
	0.2 x 2 = 0.4
	0.3 ->.0011001100110011001100110011001100110011001100110011... x 2^-2
	2.3 ->.0010011001100110011001100110011001100110011001100110... x 2^1

	___________________________________________________
	
	0.3 na base binária é a dízima 0.0100110011001... sua representação na máquina é
	.001100110011001... x 2^-1 . Já o número 2.3 tem sua representação na máquina de
	.001001100110011... x 2^1 . A precisão do número 0.3 é maior que a precisão do número 2.3
	por isso quando subtrai-se os dois o resultado não é 0, pois o número 0.3 é sutilmente mais preciso
	que o 2.3