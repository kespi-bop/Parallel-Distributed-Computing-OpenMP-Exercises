#include <stdlib.h>
#include <stdio.h>

void fillMatrixWithoutBorders(int N, double A[N][N]);
void printMatrix(int N, double A[N][N]);
void calculateInternalElements(int N, double A[N][N], double B[N][N]);

int main(void)
{
    int N = 10;
    double A[N][N], B[N][N];

    fillMatrixWithoutBorders(N, A);
    printMatrix(N, A);
    calculateInternalElements(N, A, B);
    printMatrix(N, B);

    return 0;
}

void fillMatrixWithoutBorders(int N, double A[N][N])
{
    int i, j;

    // inizializzo la matrice a 0 (opzionale, per chiarezza)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = 0.0;

    for (i = 0; i < N; i++)
    {
        A[0][i] = (double)i;             // bordo superiore
        A[i][0] = (double)i;             // bordo sinistro
        A[N - 1][N - 1 - i] = (double)i; // bordo inferiore
        A[N - 1 - i][N - 1] = (double)i; // bordo destro
    }
}

void printMatrix(int N, double A[N][N])
{
    int i, j;
    printf("\nMatrice di dimensione %d x %d:\n", N, N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%.2f ", A[i][j]);
        printf("\n");
    }
}

void calculateInternalElements(int N, double A[N][N], double B[N][N])
{

    int i, j;

    // inizializzo la matrice a 0 (opzionale, per chiarezza)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            B[i][j] = 0.0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}