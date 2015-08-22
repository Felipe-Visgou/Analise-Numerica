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

/* Função main */
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
	/* Observação na aproximação de PI/2!
	*	Como a aproximação feita pela série de taylor está centrada em pi/2
	*	ao passar pi/2 como parâmetro da função fcos, o valor obtido é 0 devido
	*	ao valor de pi definido no programa, mas ao usa-lo como parâmetro da função cos
	*	da biblioteca C o valor de cos(PI/2) não é 0 mas é um valor próximo, isso se deve 
	*	à acurácia do valor de pi definido, o qual não é exato o suficiente*/
	printf("\n-> Aproximacao de cos(PI/2) \n");
	calcula(PI/2);
	return 0;
}


//3.141592653589793238462643383279502884197169399375105