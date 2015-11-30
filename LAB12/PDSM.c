/*#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void empty_array (double* a, int s){
	int i;

	for(i=0;i<s;i++)
		a[i] = 0;
}

void print_array (double* a, int s){
	int i;

	for (i=0;i<s;i++)
		printf("%f\n", a[i]);
	printf("\n");
}

double rowXcolumn (double *v, int s){
	int i;
	double d = 0;

	for(i=0;i<s;i++)
		d += v[i] * v[i];

	return d;
}

void Cholesky (int n, double* A){
	int i, j;
	double* u;

	u = (double*) malloc ((n-1)*sizeof(double));

	for (i=0;i<n;i++){
		A[i*n + i] = sqrt(A[i*n + i]);
		if ((i+1)<n){
			
			for (j=i+1;j<n;j++){
				u[j-i-1] = A[i*n + j] / A[i*n + i];
				A[i*n + j] = u[j-i-1];
			}
			for (j = (i+1)*n + (i+1);j<n*n;j++){
				if( ( j%( ( (j/n) )*n + ( j/n ) ) ) > ( (n-1) - ( j/n ) ) )
					A[j] = 0;
				else
					A[j] = A[j] - rowXcolumn(u, (n-1-i));
			}
			//print_array (A, 9);
			
		}

	}
	free(u);
}

void Mult (int n, double* M, double* v, double* r){
	int i, j;
	double aux;

	for(i=0;i<n;i++){
		for(j=0, aux=0;j<n;j++)
			aux += M[j + i*n] * v[j];

		r[i] = aux;
	}
}

double Dot (int n, double* v, double* w){
	int i;
	double d;

	for(i=0,d=0;i<n;i++)
		d += v[i]*w[i];

	return d;
}

void ConjugateGradient (int n, double* A, double* b, double* x){
	int i, j, flag=0;
	double alpha, beta, aux, *r, *d, *vaux;
	r = (double*) malloc (n*sizeof(double));
	d = (double*) malloc (n*sizeof(double));
	vaux = (double*) malloc (n*sizeof(double));

	Mult(n, A, x, vaux);
	for (i=0;i<n;i++){
		r[i] = b[i] - vaux[i];
		if ( (r[i] > 0.02) || (r[i] < -0.02) )
			flag = 1;
		d[i] = r[i];
	}
	printf("d0  &&&&&&&&&&&&&&&& \n");
	print_array(d,n);
	while (flag){
		Mult(n, A, d, vaux);
		printf("vaux = A*d0 \n");
		print_array(vaux,n);
		aux = Dot(n, r, r);
		printf("aux r*r %g\n", aux);
		alpha = aux / (Dot(n, d, vaux));
		for (j=0;j<n;j++){
			x[j] = x[j] + (alpha*d[j]);
			r[j] = r[j] - (alpha*vaux[j]);
		}
		printf("alpha %g \n", alpha);
		beta = (Dot(n, r, r)) / aux;
		for (j=0;j<n;j++)
			d[j] = r[j] + (beta*d[j]);

		//print_array (r, n);
		flag = 0;
		for (j=0;j<n;j++){
			if ( (r[j] > 0.02) || (r[j] < -0.02) ){
				flag = 1;
				continue;
			}
		}
			printf("AQUI VAUX\n");
			print_array (vaux, n);
			printf("AQUI r0\n");
			print_array (r, n);
			printf("AQUI x0\n");
			print_array (x, n);
			printf("AQUI d0\n");
			print_array (d, n);
	}

}

	
int main (void){
	double *A, *B, *bA, *bB, *x;

	A = (double*) malloc(9*sizeof(double));
	bA = (double*) malloc(3*sizeof(double));
	x = (double*) malloc(3*sizeof(double));
	B = (double*) malloc(9*sizeof(double));
	bB = (double*) malloc(3*sizeof(double));

	//Set A
	A[0] = 1;
	A[1] = -1;
	A[2] = 0;
	A[3] = -1;
	A[4] = 2;
	A[5] = 1;
	A[6] = 0;
	A[7] = 1;
	A[8] = 2;

	//Set bA
	bA[0] = 0;
	bA[1] = 2;
	bA[2] = 3;

	//Set B
	B[0] = 1;
	B[1] = -1;
	B[2] = 0;
	B[3] = -1;
	B[4] = 2;
	B[5] = 1;
	B[6] = 0;
	B[7] = 1;
	B[8] = 5;

	//Set bB
	bB[0] = 3;
	bB[1] = -3;
	bB[2] = 4;

	//Set x
	empty_array(x, 3); 

	ConjugateGradient(3, A, bA, x);
	print_array(x, 3);
	empty_array(x, 3);

	ConjugateGradient(3, B, bB, x);
	print_array(x, 3);

	Cholesky(3, A);
	print_array(A, 9);

	Cholesky(3, B);
	print_array(B, 9);

	return 0;
}*/