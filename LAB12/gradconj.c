#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"
void printm(int n, double ** A)
{
	int i,j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf(" %g ", A[i][j]);
		}
		printf("\n");
	}

}
void printv(int n, double * A)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf(" %g ", A[i]);
	}
	printf("\n");
}
void Cholesky (int n, double **A)
{
	int i,j, k = 0;
	double **R = mat_cria(n,n);
	double **ut = mat_cria(n,1);
	double **u = mat_cria(1,n);
	double **uut = mat_cria(n,n);
	for(i = 0; i < n; i++)
	{
		R[i][i] = sqrt(A[i][i]);

		for(k = i+1; k < n; k++)
			ut[k][0] = (1/R[i][i])*A[i][k];

		mat_transposta(n,1,ut, u);

		mat_multm(n,1,n,ut, u, uut);

		for(k = i+1; k < n; k++)
		{
			for(j = i+1; j < n; j++)
			{
				A[k][j] = A[k][j] - uut[k][j];
			}
		}
	}
}
void ConjugateGradient( int n, double** A, double* b, double* x)
{
	int i, j, k, stop;
	double aux1 = 0, aux2 = 0, aux3 = 0;
	double *vaux = (double*)malloc(n*sizeof(double));
	double *d0 = (double*)malloc(n*sizeof(double)), *r0 = (double*)malloc(n*sizeof(double));
	double a0,b0;
	mat_multv(n,n, A, x, vaux);
	for(i = 0; i < n; i++)
	{
		d0[i] = b[i] - vaux[i];
		r0[i] = b[i] - vaux[i];
	}
	do
	{
		stop = 0;
		aux1 = 0;aux2 = 0;aux3=0;
		mat_multv(n,n,A, d0, vaux);
		for(j = 0; j < n; j++)
		{
			aux2 +=d0[j]*vaux[j];
			aux1 += r0[j]*r0[j];
		}
		a0 = aux1/aux2;
		for(j = 0; j < n; j++)
		{
			x[j] = x[j] + a0*d0[j];
			r0[j] = r0[j] - a0*vaux[j];
			aux3 += r0[j]*r0[j];
		}

		b0 = aux3/aux1;

		for(j = 0; j < n; j++)
			d0[j] = r0[j] +b0*d0[j];

		for (j = 0; j < n; j++)
		{
			if ( (r0[j]<0.02) && (r0[j]>-0.02) )
				stop++;
		}
	}while(stop != n);
	free(r0);
	free(d0);
	free(vaux);
}
int main (void){
	double ** A0 = mat_cria(3,3);
	double *b0 = (double*)malloc(3*sizeof(double));
	double ** A1 = mat_cria(3,3);
	double *b1 = (double*)malloc(3*sizeof(double));
	double *x0 = (double*)malloc(3*sizeof(double));
	double *x1 = (double*)malloc(3*sizeof(double));

	A0[0][0] = 1;
	A0[0][1] = -1;
	A0[0][2] = 0;
	A0[1][0] = -1;
	A0[1][1] = 2;
	A0[1][2] = 1;
	A0[2][0] = 0;
	A0[2][1] = 1;
	A0[2][2] = 2;

	b0[0] = 0;
	b0[1] = 2;
	b0[2] = 3;

	A1[0][0] = 1;
	A1[0][1] = -1;
	A1[0][2] = 0;
	A1[1][0] = -1;
	A1[1][1] = 2;
	A1[1][2] = 1;
	A1[2][0] = 0;
	A1[2][1] = 1;
	A1[2][2] = 5;

	b1[0] = 3;
	b1[1] = -3;
	b1[2] = 4;


	printf("Vetor Solucao 1 \n");
	x0[0] = 0;x0[1] = 0;x0[2] = 0;
	ConjugateGradient(3, A0, b0, x0);
	printv(3, x0);

	printf("Matriz R1 \n");

	Cholesky(3, A0);
	printm(3, A0);

	printf("Vetor Solucao 2 \n");
	x1[0] = 0;x1[1] = 0;x1[2] = 0;
	ConjugateGradient(3, A1, b1, x1);
	printv(3, x1);

	printf("Matriz R2 \n");

	Cholesky(3, A1);
	printm(3, A1);

	free(A0);
	free(A1);
	free(b0);
	free(b1);
	free(x0);
	free(x1);
	return 0;
}