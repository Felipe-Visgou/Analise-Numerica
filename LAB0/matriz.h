// Fun��o Cria Matriz
double** mat_cria(int m, int n);
// Fun��o Libera a Matriz
void mat_libera(int m, double** A);
// Fun��o Transposta da Matriz
void mat_transposta(int m, int n, double** A, double** T);
// Fun��o Multiplica��o de Vetor x Matriz
void mat_multv(int m, int n, double** A, double* v, double* w);
// Func�o multiplica��o de Matriz x Matriz
void mat_multm(int m, int n, int q, double** A, double** B, double** C);