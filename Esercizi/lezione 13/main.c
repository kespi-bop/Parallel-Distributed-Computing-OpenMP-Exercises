#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "c_timer.h"

double *instanceMatrix(int LD, double *A);
double *initializeMatrixToZero(int R, int C, int LD, double *A);
double *fillMatrix(int R, int C, int LD, double *A);
void printMatrix(int R, int C, int LD, double *A);

void matmatijk(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatkji(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatikj(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatjik(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatkij(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatkji(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void printMatmat(int ldA, int ldB, int ldC,
                 double *A, double *B, double *C,
                 int N1, int N2, int N3);

void calculateAllMatmatAndPrintAllExecTimes(int ldA, int ldB, int ldC,
                                            double *A, double *B, double *C,
                                            int N1, int N2, int N3);

int main()
{
    /*         srand(time(NULL)); */
    int matrixDimensions[6] = {256, 512, 768, 1024, 1280, 1536};
    int i, j, N1, N2, N3;
    int ldA = 2000, ldB = 2000, ldC = 2000;
    double *A, *B, *C;

    A = instanceMatrix(ldA, A);
    B = instanceMatrix(ldB, B);
    C = instanceMatrix(ldC, C);

    A = fillMatrix(1536, 1536, ldA, A);
    B = fillMatrix(1536, 1536, ldB, B);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    for (i = 0; i < 6; i++)
    {
        N1 = matrixDimensions[i];
        N2 = matrixDimensions[i];
        N3 = matrixDimensions[i];

        printf("\n\nTempo di esecuzione per matrice C[%d x %d]:\n", N1, N3);
        calculateAllMatmatAndPrintAllExecTimes(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    }

    /* printMatmat(ldA, ldB, ldC, A, B, C, N1, N2, N3); */

    printf("\n\n");
    free(A);
    free(B);
    free(C);
    return 0;
}

double *instanceMatrix(int LD, double *A)
{
    A = (double *)malloc(LD * LD * sizeof(double));
    return A;
}

double *initializeMatrixToZero(int R, int C, int LD, double *A)
{
    int i, j;
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            A[i * LD + j] = 0.;
        }
    }
    return A;
}

double *fillMatrix(int R, int C, int LD, double *A)
{
    int i, j;
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            A[i * LD + j] = (double)(rand() % 100);
        }
    }
    return A;
}

void printMatrix(int R, int C, int LD, double *A)
{
    int i, j;
    printf("\nMatrice di dimensione %d x %d:\n", R, C);
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("%.2f ", A[i * LD + j]);
        }
        printf("\n");
    }
}

void matmatijk(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int i, j, k;
    for (i = 0; i < N1; i++)
    {
        for (j = 0; j < N3; j++)
        {
            for (k = 0; k < N2; k++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void matmatkji(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int k, i, j;
    for (k = 0; k < N2; k++)
    {
        for (i = 0; i < N1; i++)
        {
            for (j = 0; j < N3; j++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void matmatikj(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int i, k, j;
    for (i = 0; i < N1; i++)
    {
        for (k = 0; k < N2; k++)
        {
            for (j = 0; j < N3; j++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void matmatjik(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int j, i, k;
    for (j = 0; j < N3; j++)
    {
        for (i = 0; i < N1; i++)
        {
            for (k = 0; k < N2; k++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void matmatkij(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int k, i, j;
    for (k = 0; k < N2; k++)
    {
        for (i = 0; i < N1; i++)
        {
            for (j = 0; j < N3; j++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void matmatjki(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3)
{
    int j, k, i;
    for (j = 0; j < N3; j++)
    {
        for (k = 0; k < N2; k++)
        {
            for (i = 0; i < N1; i++)
            {
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
            }
        }
    }
}

void printMatmat(int ldA, int ldB, int ldC,
                 double *A, double *B, double *C,
                 int N1, int N2, int N3)
{
    matmatijk(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    matmatkji(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    matmatikj(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    matmatjik(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    matmatkij(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    matmatjki(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    printMatrix(N1, N3, ldC, C);
    C = initializeMatrixToZero(N1, N3, ldC, C);
}

void calculateAllMatmatAndPrintAllExecTimes(int ldA, int ldB, int ldC,
                                            double *A, double *B, double *C,
                                            int N1, int N2, int N3)
{
    double t1, t2, exec_time;

    t1 = get_cur_time();
    matmatijk(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("1 - matmatijk execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatkji(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("2 - matmatkji execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatikj(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("3 - matmatikj execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatjik(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("4 - matmatjik execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatkij(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("5 - matmatkij execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatjki(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    printf("6 - matmatjki execution time: %.6f seconds\n", exec_time);
    C = initializeMatrixToZero(N1, N3, ldC, C);
}