#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979323846
double fcos(double x);
double residuo(double x);
void calcula(double x);
void calcula (double x)
{
	double  fx;
	double r;
	fx = fcos(x);
	r = residuo(x);
	printf("  fcos : %g \n  residuo : %g \n", fx, r);
	printf("  cos(x): %g \n", cos(x));
	printf("  Erro Absoluto : %g \n", cos(x) - fcos(x));
	return ;
}

/* Fun��o main */
int main (void)
{
	printf("\n-> Aproximacao de cos(0) \n");
	calcula(0.0);
	printf("\n-> Aproximacao de cos(PI) \n");
	calcula(PI);
	printf("\n-> Aproximacao de cos(PI/4) \n");
	calcula(PI/4.0);
	printf("\n-> Aproximacao de cos(1) \n");
	calcula(1);
	/* Observa��o na aproxima��o de PI/2!
	*	Como a aproxima��o feita pela s�rie de taylor est� centrada em pi/2
	*	ao passar pi/2 como par�metro da fun��o fcos, o valor obtido � 0 devido
	*	ao valor de pi definido no programa, mas ao usa-lo como par�metro da fun��o cos
	*	da biblioteca C o valor de cos(PI/2) n�o � 0 mas � um valor pr�ximo, isso se deve 
	*	� acur�cia do valor de pi definido, o qual n�o � exato o suficiente*/
	printf("\n-> Aproximacao de cos(PI/2) \n");
	calcula(PI/2);
	return 0;
}


//3.141592653589793238462643383279502884197169399375105