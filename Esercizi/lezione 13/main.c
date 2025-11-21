#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "c_timer.h"
#include "matmat.h"

double *instanceMatrix(int LD, double *A);
double *initializeMatrixToZero(int R, int C, int LD, double *A);
double *fillMatrix(int R, int C, int LD, double *A);
void printMatrix(int R, int C, int LD, double *A);

void printMatmat(int ldA, int ldB, int ldC,
                 double *A, double *B, double *C,
                 int N1, int N2, int N3);

void calculateAllMatmatAndPrintAllExecTimes(int ldA, int ldB, int ldC,
                                            double *A, double *B, double *C,
                                            int N1, int N2, int N3, int dbA, int dbB, int dbC);

int main()
{
    /*         srand(time(NULL)); */
    int matrixDimensions[6] = {256, 512, 768, 1024, 1280, 1536};
    int i, j, N1, N2, N3;
    int ldA = 2000, ldB = 2000, ldC = 2000;
    int dbA = 4, dbB = 4, dbC = 4;
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
        calculateAllMatmatAndPrintAllExecTimes(ldA, ldB, ldC, A, B, C, N1, N2, N3, dbA, dbB, dbC);
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
                                            int N1, int N2, int N3, int dbA, int dbB, int dbC)
{
    double t1, t2, exec_time, Gflops, Nflops = 2.0 * N1 * N2 * N3, exponent = pow(10, 9);
    ;

    t1 = get_cur_time();
    matmatijk(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("1 - matmatijk execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatkji(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("2 - matmatkji execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatikj(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("3 - matmatikj execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatjik(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("4 - matmatjik execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatkij(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("5 - matmatkij execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatjki(ldA, ldB, ldC, A, B, C, N1, N2, N3);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("6 - matmatjki execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);

    t1 = get_cur_time();
    matmatblock(ldA, ldB, ldC, A, B, C, N1, N2, N3, dbA, dbB, dbC);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    Gflops = Nflops / exec_time / exponent;
    printf("7 - matmatblock execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);
}