#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


double get_cur_time();

double maxsum(int N, int LD, double *A, int NT);

double *instanceMatrix(int LD, double *A);
double *fillMatrix(int N, int LD, double *A);
void printMatrix(int N, int LD, double *A);

int main()
{
    /*     srand(time(NULL)); */
    int i, j, N;
    int LD = 5600;
    double t1, t2, R, exec_time;
    double *A;
    int matrixDimension[7] = {800, 1600, 2400, 3200, 4000, 4800, 5600};
    int numThreads[4] = {1, 2, 4, 8};
    A = instanceMatrix(LD, A);

    for (i = 0; i < 7; i++)
    {
        N = matrixDimension[i];
        printf("\n--------- Esecuzione con matrice di dimensione %d x %d ---------\n", N, N);
        A = fillMatrix(N, LD, A);
        for (j = 0; j < 4; j++)
        {
            t1 = get_cur_time();
            R = maxsum(N, LD, A, numThreads[j]);
            t2 = get_cur_time();
            exec_time = t2 - t1;
            printf("\n - Con %d thread il tempo di esecuzione e’ %f secondi (R = %f) .\n ", numThreads[j], exec_time, R);
        }
    }
    printf("\n\n");

/*         printMatrix(N, LD, A); */

    free(A);
    return 0;
}

double *instanceMatrix(int LD, double *A)
{
    A = (double *)malloc(LD * LD * sizeof(double));
    return A;
}

double *fillMatrix(int N, int LD, double *A)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i * LD + j] = (double)(rand() % 100);
        }
    }
    return A;
}

void printMatrix(int N, int LD, double *A)
{
    int i, j;
    printf("\nMatrice di dimensione %d x %d:\n", N, N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%.2f ", A[i * LD + j]);
        }
        printf("\n");
    }
}


