#include <stdlib.h>

// Cria Matriz MxN
double** mat_cria(int m, int n)
{
	double** A;
	int i, j;
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
	for(i = 0; i < m; i++)
		w[i] = 0;
	for(j = 0; j < n; j++)
	{
		for(i = 0; i < m; i++)
		{
			w[i] += v[i] * A[i][j];
		}
	}
}
// Multiplicação de Matrizes
void mat_multm(int m, int n, int q, double** A, double** B, double** C)
{
	int i, j;
	for(i = 0; i < m; i ++)
	{
		for(j = 0; j < q; j++)
		{
			C[i][j] = 0;
		}
	}
	for(j = 0; j < q; j++)
	{
		for(i = 0; i < n; i++)
		{
			C[i][j] += A[i][j] * B[i][j];
		}
	}
}

