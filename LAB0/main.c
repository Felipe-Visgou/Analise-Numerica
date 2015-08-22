#include "matriz.h"
#include <stdio.h>
// Função auxiliar que imprime uma matriz MxN
void printm(int m, int n, double** A)
{
	int i, j;
	for(i = 0; i < m; i++)
	{
		printf("\n");
		for(j = 0; j < n; j++)
		{
			printf("%g ", A[i][j]);
		}
	}
}
int main (void)
{
	double** A = mat_cria(3,3);
	double** B = mat_cria(3,2);
	double** C = mat_cria(3,3);
	double** D = mat_cria(3,2);
	double v[3];
	double w[3];
	// Vetor v
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;
	// Matriz A
	A[0][0] = 0;
	A[0][1] = 1;
	A[0][2] = 2;
	A[1][0] = 0;
	A[1][1] = 1;
	A[1][2] = 2;
	A[2][0] = 0;
	A[2][1] = 1;
	A[2][2] = 2;
	// Matriz B
	B[0][0] = 0;
	B[0][1] = 1;
	B[1][0] = 0;
	B[1][1] = 1;
	B[2][0] = 0;
	B[2][1] = 1;
	// Imprime a matriz
	printm(3,3,A);
	mat_transposta(3,3, A, C);
	printf("\n\n");
	printm(3,3,C);
	printf("\n\n");
	mat_multv(3,3, A, v, w);
	printf("%g %g %g\n", w[0], w[1], w[2]);
	mat_multm(3,3,2, A, B, D);
	printm(3,2,D);
	mat_libera(3, A);
	mat_libera(3, B);
	mat_libera(3, C);
	mat_libera(3, D);
	return 0;
}