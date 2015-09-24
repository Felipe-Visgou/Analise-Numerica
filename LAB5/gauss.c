#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "matriz.h"

double** fatoracao( int n, double** A)
{
	int i, j, k, l, sum, lin, col, pivot, troca[4], t;
	double* temp, fator, p1, p2;
	double** P = mat_cria(n,n);
	/* inicializa a atriz permutação */
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			{
				if(i != j)
					P[i][j] = 0;
				else
					P[i][j] = 1;
			}
	}
	// pivotamento antes da substituição
	p1 = A[0][0]; p1 = modulo(p1);
	pivot = 0;
	for(i=1; i < n; i++)
	{
		p2 = A[i][0]; p2 = modulo(p2);
		if(p2 > p1)
		{
			pivot = i;
			p1 = p2;
		}
	}
	// armazena a troca no vetor de trocas
	troca[0] = i;

	// faz a troca na matriz A







}

double modulo(double a)
{
	if(a<0)
		a*=-1;
	return a;
}

	
