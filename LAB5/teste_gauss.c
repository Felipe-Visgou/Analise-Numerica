#include "matriz.h"
#include "gauss.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// funcao que imprime matrizes
void printm(int m, int n, double** A)
{
	int i, j;
	for(i = 0; i < m; i++)
	{
		printf("\n");
		for(j = 0; j < n; j++)
		{
			printf("%.2g ", A[i][j]);
		}
	}
}
void printv(int n, double* v)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("\n");
		printf("%.2g ", v[i]);
	}
}
// main
int main (void)
{
	double** A1 = mat_cria(3,3);
	double b1[3] = {3.0, 3.0, -6.0};
	double** A2 = mat_cria(6,6);
	double b2[6] = {2.5, 1.5, 1.0, 1.0, 1.5, 2.5};
	double** P;
	double* x1, *x2;
	// Preencher a matrize A1
	A1[0][0] = 1.0; A1[0][1] = 2.0; A1[0][2] = -1.0; // linha 0
	A1[1][0] = 2.0; A1[1][1] = 1.0; A1[1][2] = -2.0; // linha 1
	A1[2][0] = -3.0; A1[2][1] = 1.0; A1[2][2] = 1.0; // linha 2
	// Matriz A2
	A2[0][0] = 3.0; A2[0][1] = -1.0; A2[0][2] = 0; A2[0][3] = 0; A2[0][4] = 0; A2[0][5] = 0.5; // linha 0
	A2[1][0] = -1.0; A2[1][1] = 3.0; A2[1][2] = -1.0; A2[1][3] = 0; A2[1][4] = 0.5; A2[1][5] = 0; // linha 1
	A2[2][0] = 0; A2[2][1] = -1.0; A2[2][2] = 3.0; A2[2][3] = -1.0; A2[2][4] = 0; A2[2][5] = 0; // linha 2
	A2[3][0] = 0; A2[3][1] = 0; A2[3][2] = -1.0; A2[3][3] = 3.0; A2[3][4] = -1.0; A2[3][5] = 0; // linha 3
	A2[4][0] = 0; A2[4][1] = 0.5; A2[4][2] = 0; A2[4][3] = -1.0; A2[4][4] = 3.0; A2[4][5] = -1.0; // linha 4
	A2[5][0] = 0.5; A2[5][1] = 0; A2[5][2] = 0; A2[5][3] = 0; A2[5][4] = -1.0; A2[5][5] = 3.0; // linha 5
	printf(" A Matriz A1 \n");
	printm(3, 3, A1);
	printf("\n");
	printf("O vetor b1 \n");
	printv(3, b1);

	// Procedure A1
	P = fatoracao(3, A1);
	x1 = substituicao(3, A1, P, b1);

	printf(" vetor solucao de A1x = b1 \n");
	printv(3,x1);

	// Procedure A2
	P = fatoracao(6, A2);
	x2 = substituicao(6, A2, P, b2);

	printf(" vetor solucao de A2x = b2 \n");
	printv(6,x2);
	
	return 0;
	
}
