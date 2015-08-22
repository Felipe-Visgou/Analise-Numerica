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
	
	0.3 na base bin�ria � a d�zima 0.0100110011001... sua representa��o na m�quina �
	.001100110011001... x 2^-1 . J� o n�mero 2.3 tem sua representa��o na m�quina de
	.001001100110011... x 2^1 . A precis�o do n�mero 0.3 � maior que a precis�o do n�mero 2.3
	por isso quando subtrai-se os dois o resultado n�o � 0, pois o n�mero 0.3 � sutilmente mais preciso
	que o 2.3