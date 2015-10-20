typedef struct sample Sample;
/* Chebyshev */
Sample* Chebyshev (int n, double a, double b, double (*f)(double x));
/*Lagrange Compute */
double* LagrangeCompute (Sample* s);
/* Lagrange Eval */
double LagrangeEval (Sample*s, double* den, double x);
/* Newton Compute */
double* NewtonCompute (Sample* s);
/* Newton Eval */
double NewtonEval (Sample* s, double* coef, double x);
