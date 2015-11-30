#include <stdlib.h>
#include <stdio.h>
// Cria Matriz MxN
double** mat_cria(int m, int n)
{
	double** A;
	int i;
	A = (double**)malloc(m*sizeof(double*));
	for(i=0; i < m; i++)
	{
		A[i] = (double*)malloc(n*sizeof(double));
	}
	return A;
}

// Libera o espaço alocado pela matriz
void mat_libera(int m, double** A)
{
	int i;
	for(i=0; i < m; i++)
	{
		free(A[i]);
	}
	free(A);
}
// Transposta da matriz
void mat_transposta(int m, int n, double** A, double** T)
{
	int i, j;
	for(i=0; i < m; i++)
	{
		for(j=0;j < n; j++)
		{
			T[j][i] = A[i][j];
		}
	}
}
// Multiplicação de Vetor x Matriz
void mat_multv(int m, int n, double** A, double* v, double* w)
{
	int i, j;
	double aux;
	for(i = 0; i < n; i++)
		w[i] = 0;
	for(i=0;i<n;i++){
		for(j=0, aux=0;j<n;j++)
			aux += A[i][j] * v[j];

		w[i] = aux;
	}
}
// Multiplicação de Matrizes
void mat_multm(int m, int n, int q, double** A, double** B, double** C)
{
	int c, d, k;
	double sum = 0;
	for (c = 0; c < m; c++)
	{
		for (d = 0; d < q; d++)
		{
			for (k = 0; k < n; k++) 
			{
				sum = sum + A[c][k]*B[k][d];
			}

			C[c][d] = sum;
			sum = 0;
		}
	}
}