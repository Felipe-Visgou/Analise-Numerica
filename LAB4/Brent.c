#include <stdlib.h>
#include <math.h>

double det (double* A){
	return (A[0]*A[4]*A[8]) + (A[1]*A[5]*A[6]) + (A[2]*A[3]*A[7]) - (A[2]*A[4]*A[6]) - (A[1]*A[3]*A[8]) - (A[0]*A[5]*A[7]);
}

double cramer_x (double* A, double* V){
	double ret;
	double* T;
	int i, j=0;

	T = (double*) malloc (9*sizeof(double));

	//Cria a Matriz Numerador para descobrir 'x' do metodo de Cramer
	for (i=0;i<9;i++){
		if( i==0 || i==3 || i==6 ){
			T[i] = V[j];
			j++;
		}
		else
			T[i] = A[i];
	}

	//Retorna o valor de xm, que eh o valor em que a parabola do IQI cruza o eixo x
	ret = ( det (T) / det (A) );
	free(T);
	return ret;
}


double brent (double x0, double x1, int p, double (*f) (double x)){
	int i;
	double xm, x2;
	double *A, *V;
	double a, b;
	a = f(x0);
	b = f(x1);
	if ( f(x0) > f(x1) ){
		x2 = x0;
		x0 = x1;
		x1 = x2;
	}
	if ( !((f(x0) * f(x1)) < 0) ){
		exit(0);
	}

	A = (double*) malloc(9*sizeof(double));
	V = (double*) malloc(3*sizeof(double));

	//Passo 1: Ponto Medio
	xm = (x0 + x1) / 2;

	//Passo 2: IQI
	for (i=0;i<3;i++){
		if(i==0)
			V[i] = xm;
		else if(i==1)
			V[i] = x0;
		else
			V[i] = x1;
	}

	for (i=0;i<9;i++){
		double y;
		if (i%9 < 3)
			y = f(xm);
		else if (i%9 < 6)
			y = f(x0);
		else
			y = f(x1);

		if (i%3 == 0)
			A[i] = pow(y, 2);
		else if (i%3 == 1)
			A[i] = y;
		else
			A[i] = 1;
	}

	x2 = cramer_x(A,V);
	free(A);
	free(V);

	if (f(x2) > 0){
		if (f(xm) > 0){
			if ((f(x2) < f(xm)) && ((x2 - x0) <= ((x1 - x0)/2))){
				if (f(x2) < pow(10, -p))
					return x2;
				else
					return brent(x0, x2, p, f);
			}
		}
		else{
			if ((f(x2) < ( (-1) * f(xm) )) && ((x2 - x0) <= ((x1 - x0)/2))){
				if (f(x2) < pow(10, -p))
					return x2;
				else
					return brent(x0, x2, p, f);
			}
		}
	}
	else if (f(x2) < 0){
		if (f(xm) > 0){
			if ((f(x2) > ( (-1) * f(xm) )) && ((x1 - x2) <= ((x1 - x0)/2))){
				if (f(x2) > ( (-1) * pow(10, -p) ))
					return x2;
				else
					return brent(x2, x1, p, f);
			}
		}
		else{
			if ((f(x2) > f(xm)) && ((x1 - x2) <= ((x1 - x0)/2))){
				if (f(x2) > ( (-1) * pow(10, -p) ))
					return x2;
				else
					return brent(x2, x1, p, f);
			}
		}
	}
	else if (f(x2) == 0)
		return x2;

	//Passo 3: Secante
	x2 = x1 - ((x1-x0)*f(x1)/(f(x1)-f(x0)));

	if (f(x2) > 0){
		if (f(xm) > 0){
			if ((f(x2) < f(xm)) && ((x2 - x0) <= ((x1 - x0)/2))){
				if (f(x2) < pow(10, -p))
					return x2;
				else
					return brent(x0, x2, p, f);
			}
		}
		else{
			if ((f(x2) < ( (-1) * f(xm) )) && ((x2 - x0) <= ((x1 - x0)/2))){
				if (f(x2) < pow(10, -p))
					return x2;
				else
					return brent(x0, x2, p, f);
			}
		}
	}
	else if (f(x2) < 0){
		if (f(xm) > 0){
			if ((f(x2) > ( (-1) * f(xm) )) && ((x1 - x2) <= ((x1 - x0)/2))){
				if (f(x2) > ( (-1) * pow(10, -p) ))
					return x2;
				else
					return brent(x2, x1, p, f);
			}
		}
		else{
			if ((f(x2) > f(xm)) && ((x1 - x2) <= ((x1 - x0)/2))){
				if (f(x2) > ( (-1) * pow(10, -p) ))
					return x2;
				else
					return brent(x2, x1, p, f);
			}
		}
	}
	else if (f(x2) == 0)
		return x2;

	//Passo 4: Bissecao
	if ( f(xm) == 0 )
		return xm;
	else if ( f(x0)*f(xm) < 0 )
		return brent(x0, xm, p, f);
	else
		return brent(xm, x1, p, f);
}