#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matriz.h"

// Funcao de soma de matrizes
void mat_soma(int n, double** A, double** B, double** S);
// Funcao para imprimir a vetor
void printv(int n, double* v);

 // calcula a norma 2 de um vetor de n posições
double norma2(int n,double* v)
{
	int i;
	double soma = 0;
	for(i = 0; i < n; i++)
		soma += pow(v[i], 2);
	return sqrt(soma);
}

// Retorna a Matriz A invertida
double** inverse(int n,double **A)
{
	int i,j;
	double** I = mat_cria(n, n);
	// I = A^-1
	for(j = 0; j < n; j++)
	{
		for(i = 0; i < n; i++)
		{
			if(i == j)
				I[i][j] = 1/A[i][j];
			else
				I[i][j] = A[i][j];
		}
	}
	return I;
}

// Clona o conteudo do vetor source para o vetor dest
void * cloneVet(int n, double* source, double* dest)
{
	int i;
	for(i = 0; i < n; i++)
	{
		dest[i] = source[i];
	}
}

// Preenche as matrizes L(triangular inferior), D(diagonal) e U(triangular superior)
void LDU(int n, double** A, double** L, double** D, double** U)
{
	int i, j;
	for(j = 0; j < n; j++) // Lower
	{
		for(i = 0; i < n; i++)
		{
			if(i > j)
				L[i][j] = A[i][j];
			else
				L[i][j] = 0;
		}
	}
	for(j = 0; j < n; j++) // Upper
	{
		for(i = 0; i < n; i++)
		{
			if(i < j)
				U[i][j] = A[i][j];
			else
				U[i][j] = 0;
		}
	}
	for(j = 0; j < n; j++) // Diagonal
	{
		for(i = 0; i < n; i++)
		{
			if(i == j)
				D[i][j] = A[i][j];
			else
				D[i][j] = 0;
		}
	}
}
// Função para zerar um vetor
void zeraVet(int n, double* v)
{
	int i;
	for(i = 0; i < n; i++)
		v[i] = 0;
}
// Método Iterativo de Jacobi
int Jacobi (int n, double** A, double* b, double* x, double tol)
{
	double *vaux = (double*)malloc(n*sizeof(double));
	double *antes = (double*)malloc(n*sizeof(double)); // xk
	double *depois = (double*)malloc(n*sizeof(double));// xk+1
	double *diff = (double*)malloc(n*sizeof(double));// x[k] - x[k+1]
	double norma;
	int i;	
	int nit = 0;
	double ** D_i;
	double **soma = mat_cria(n,n);
	double **L = mat_cria(n,n), **D = mat_cria(n,n), **U = mat_cria(n,n);
	LDU(n, A,L,D,U); // constrói a matriz L D e U
	D_i = inverse(n, D);
	mat_soma(n, L, U, soma);
	zeraVet(3, x);
	for(i = 0; i < n; i++)
		vaux[i] = 0;
	do
	{
		nit++;

		// copia o vetor anterior
		cloneVet(n, x, antes);

		mat_multv(n,n,soma, x, vaux); // (L+U)x

		for(i = 0; i < n; i++)// b-(L+U)x
			vaux[i] = b[i]-vaux[i];

		mat_multv(n,n,D_i, vaux, x);// x = D^-1(b-(L+U)x

		// copia o vetor posterior a conta
		cloneVet(n, x, depois);

		for(i = 0; i < n; i++)// Xk - Xk+1
			diff[i] = antes[i] -depois[i];

		norma = norma2(n, diff);

	}while(norma > tol);
	free(diff);
	free(vaux);
	mat_libera(n, soma);
	free(depois);
	free(antes);
	free(D_i);
	return nit;
}

// Método Iterativo de Gauss-Seidel
int GaussSeidel (int n, double** A, double* b, double* x, double tol)
{
	double *vaux = (double*)malloc(n*sizeof(double));
	double *Lx = (double*)malloc(n*sizeof(double)); //Lx[k+1]
	double *Ux = (double*)malloc(n*sizeof(double));//Ux[k]
	double *antes = (double*)malloc(n*sizeof(double)); // x[k]
	double *depois = (double*)malloc(n*sizeof(double));// x[k+1]
	double *diff = (double*)malloc(n*sizeof(double));// x[k] - x[k+1]
	double norma;
	int i;	
	int nit = 0;
	double ** D_i;
	double **soma = mat_cria(n,n);
	double **L = mat_cria(n,n), **D = mat_cria(n,n), **U = mat_cria(n,n);
	LDU(n, A,L,D,U); // constrói a matriz L D e U
	D_i = inverse(n, D);
	mat_soma(n, L, U, soma);
	zeraVet(n, x);
	zeraVet(n, vaux);
	// primeira iteração: depois = x = antes
	for(i = 0; i < n; i++)
		depois[i] = x[i];
	do
	{
		nit++;

		// copia o vetor anterior
		cloneVet(n, x, antes);

		mat_multv(n,n,U, antes, Ux); // Ux(k)
		mat_multv(n,n,L, depois, Lx); // Lx(k)

		for(i = 0; i < n; i++)// Ux[k] + Lx[k+1]
			vaux[i] = Ux[i] + Lx[i];

		for(i = 0; i < n; i++)// b - (Ux[k] + Lx[k+1])
			vaux[i] = b[i] - vaux[i];

		mat_multv(n,n,D_i, vaux, x);// x = D^-1(b-(Ux[k] + Lx[k+1]))

		// copia o vetor posterior a conta
		cloneVet(n, x, depois);

		for(i = 0; i < n; i++)// Xk - Xk+1
			diff[i] = antes[i] -depois[i];

		norma = norma2(n, diff);

	}while(norma > tol);
	free(diff);
	free(vaux);
	mat_libera(n, soma);
	free(depois);
	free(antes);
	free(D_i);
	free(Lx);
	free(Ux);
	return nit;
}

// Método Iterativo de Gauss-Seidel com sobre-relaxamento
int SOR (int n, double** A, double* b, double* x, double tol, double w)
{
	double *vaux = (double*)malloc(n*sizeof(double));
	double *Lx = (double*)malloc(n*sizeof(double)); //Lx[k+1]
	double *Ux = (double*)malloc(n*sizeof(double));//Ux[k]
	double *antes = (double*)malloc(n*sizeof(double)); // x[k]
	double *depois = (double*)malloc(n*sizeof(double));// x[k+1]
	double *diff = (double*)malloc(n*sizeof(double));// x[k] - x[k+1]
	double *wxk = (double*)malloc(n*sizeof(double));//(1-w)*x[k]
	double *wxk1 = (double*)malloc(n*sizeof(double));// w*x[k+1]
	double norma;
	int i;	
	int nit = 0;
	double ** D_i;
	double **soma = mat_cria(n,n);
	double **L = mat_cria(n,n), **D = mat_cria(n,n), **U = mat_cria(n,n);
	LDU(n, A,L,D,U); // constrói a matriz L D e U
	D_i = inverse(n, D);
	mat_soma(n, L, U, soma);
	zeraVet(n, x);
	zeraVet(n, vaux);
	zeraVet(n, wxk);
	zeraVet(n, wxk1);
	// primeira iteração: depois = x = antes
	for(i = 0; i < n; i++)
		depois[i] = x[i];
	do
	{
		nit++;

		// copia o vetor anterior
		cloneVet(n, x, antes);

		mat_multv(n,n,U, antes, Ux); // Ux(k)
		mat_multv(n,n,L, depois, Lx); // Lx(k)

		for(i = 0; i < n; i++)// Ux[k] + Lx[k+1]
			vaux[i] = Ux[i] + Lx[i];

		for(i = 0; i < n; i++)// b - (Ux[k] + Lx[k+1])
			vaux[i] = b[i] - vaux[i];

		mat_multv(n,n,D_i, vaux, x);// x = D^-1(b-(Ux[k] + Lx[k+1]))

		// copia o vetor depois do calculo
		cloneVet(n, x, depois);

		for(i = 0; i < n; i++)// Xk - Xk+1
			diff[i] = antes[i] -depois[i];

		norma = norma2(n, diff);
		for(i = 0; i < n; i++)
		{
			wxk[i] = (1-w)*antes[i];
			wxk1[i] = w*depois[i];
			x[i] = wxk[i] + wxk1[i];
		}

	}while(norma > tol);
	free(diff);
	free(vaux);
	mat_libera(n, soma);
	free(depois);
	free(antes);
	free(D_i);	
	free(Lx);
	free(Ux);
	free(wxk);
	free(wxk1);
	return nit;
}

// teste
int main(void)
{
	double**A0 = mat_cria(2,2), ** A1, *x0, *x1;
	double* b0, *b1;
	int iter, i;
	double tol = pow(10.0, -7);
	x0 = (double*)malloc(2*sizeof(double));
	b0 = (double*)malloc(2*sizeof(double));
	// valores de A e b
	A0[0][0] = 3.0;
	A0[0][1] = 1.0;
	A0[1][0] = 1.0;
	A0[1][1] = 2.0;
	
	b0[0] = 5;
	b0[1] = 5;

	//Jacobi
	iter = Jacobi(2, A0, b0, x0, tol);
	printf("Exemplo 1 (Jacobi): numero de iteracoes = %d \n", iter);
	printv(2, x0);

	// Gauss-Seidel
	iter = GaussSeidel(2, A0, b0, x0, tol);
	printf("Exemplo 1 (Gauss-Seidel): numero de iteracoes = %d \n", iter);
	printv(2, x0);

	// Sobre-Relaxamento
	iter = SOR(2, A0, b0, x0, tol, 1.1);
	printf("Exemplo 1 (SOR): numero de iteracoes = %d \n", iter);
	printv(2, x0);

	mat_libera(2, A0);

	A1 = mat_cria(6,6);
	x1 = (double*)malloc(6*sizeof(double));
	b1 = (double*)malloc(6*sizeof(double));
	// valores de A e b
	A1[0][0] = 3.0;
	A1[0][1] = -1.0;
	A1[0][2] = 0.0;
	A1[0][3] = 0.0;
	A1[0][4] = 0.0;
	A1[0][5] = 0.5;
	A1[1][0] = -1.0;
	A1[1][1] = 3.0;
	A1[1][2] = -1.0;
	A1[1][3] = 0.0;
	A1[1][4] = 0.5;
	A1[1][5] = 0.0;
	A1[2][0] = 0.0;
	A1[2][1] = -1.0;
	A1[2][2] = 3.0;
	A1[2][3] = -1.0;
	A1[2][4] = 0.0;
	A1[2][5] = 0.0;
	A1[3][0] = 0.0;
	A1[3][1] = 0.0;
	A1[3][2] = -1.0;
	A1[3][3] = 3.0;
	A1[3][4] = -1.0;
	A1[3][5] = 0.0;
	A1[4][0] = 0.0;
	A1[4][1] = 0.5;
	A1[4][2] = 0.0;
	A1[4][3] = -1.0;
	A1[4][4] = 3.0;
	A1[4][5] = -1.0;
	A1[5][0] = 0.5;
	A1[5][1] = 0.0;
	A1[5][2] = 0.0;
	A1[5][3] = 0.0;
	A1[5][4] = -1.0;
	A1[5][5] = 3.0;

	b1[0] = 2.5;
	b1[1] = 1.5;
	b1[2] = 1.0;
	b1[3] = 1.0;
	b1[4] = 1.5;
	b1[5] = 2.5;

	//Jacobi
	iter = Jacobi(6, A1, b1, x1, tol);
	printf("Exemplo 2 (Jacobi): numero de iteracoes = %d \n", iter);
	printv(6, x1);

	// Gauss-Seidel
	iter = GaussSeidel(6, A1, b1, x1, tol);
	printf("Exemplo 2 (Gauss-Seidel): numero de iteracoes = %d \n", iter);
	printv(6, x1);

	// Sobre-Relaxamento
	iter = SOR(2, A1, b1, x1, tol, 1.1);
	printf("Exemplo 2 (SOR): numero de iteracoes = %d \n", iter);
	printv(6, x1);

	mat_libera(6, A1);
	free(b0);
	free(b1);
	return 0;

}
/* Soma matriz */
void mat_soma(int n, double** A, double** B, double** S)
{
	int i, j;
	double soma = 0;
	for(j = 0; j < n; j++)
	{
		for(i = 0; i < n; i++)
		{
			S[i][j] = A[i][j] + B[i][j];
		}
	}
}
/* Imprime vetor */
void printv(int n, double* v)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%g ", v[i]);
	}
	printf("\n");
}