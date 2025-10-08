#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int setMatrixDimensionInput();
int setNumberOfThreadsInput();
double *fillMatrix(double *A, int N);
void printMatrix(double *A, int N);

double maxsum(int N, int LD, double *A, int NT);

int main()
{
    srand(time(NULL));
    double t1, t2, R;
    double *A;
    int N = setMatrixDimensionInput();
    int NT = setNumberOfThreadsInput();
    A = fillMatrix(A, N);

/*     printMatrix(A, N); */

    t1 = omp_get_wtime();
    R = maxsum(N, N, A, NT);
    t2 = omp_get_wtime();
    double exec_time = t2 - t1;

    printf("\nIl valore massimo tra le sommatorie delle radici quadrate delle righe e’: %f\n", R);

    printf("\nil tempo di esecuzione e’ %f secondi.\n ", exec_time);

    free(A);
    return 0;
}

int setMatrixDimensionInput()
{
    int N;
    printf("\nInserisci la dimensione della matrice quadrata (N x N): ");
    scanf("%d", &N);
    return N;
}

int setNumberOfThreadsInput()
{
    int NT;
    printf("\nInserisci il numero di threads da utilizzare: ");
    scanf("%d", &NT);
    return NT;
}

double *fillMatrix(double *A, int N)
{
    A = (double *)malloc(N * N * sizeof(double));
    for (int i = 0; i < N * N; i++)
    {
        A[i] = rand() % 100;
    }
    return A;
}

void printMatrix(double *A, int N)
{
    printf("\nMatrice A:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.2f ", A[i * N + j]);
        }
        printf("\n");
    }
}

double maxsum(int N, int LD, double *A, int NT)
{
    int id, start, end, i, j;
    double sum, maxRow;
    double Max = 0;

    omp_set_num_threads(NT);

#pragma omp parallel private(id, start, end, sum, i, j, maxRow)
    {
        id = omp_get_thread_num();
        start = id * N / NT;
        end = start + N / NT;
        maxRow = 0;

        for (i = start; i < end; i++)
        {
            sum = 0;
            for (j = 0; j < LD; j++)
            {
                sum = sum + sqrt(A[i * LD + j]);
            }
/*             printf("Thread %d: somma riga %d = %f\n", id, i, sum); */
            if (sum > maxRow)
            {
                maxRow = sum;
            }
        }

#pragma omp critical
        {
            if (maxRow > Max)
            {
                Max = maxRow;
            }
        }
    }
    return Max;
}
