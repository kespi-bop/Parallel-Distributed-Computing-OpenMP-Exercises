#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "c_timer.h"
#include "matmatthread.h"

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

void calculateMatmatthreadAndPrintExecTime(double *ExecTime, int ldA, int ldB, int ldC, double *A, double *B, double *C, int N1, int N2, int N3, int dbA, int dbB, int dbC, int NTROW, int NTCOL);

void calculateAndPrintSpeedUp(double ExecTime[2][4], double SpeedUp[2][4], int numbersOfThreadsRow[4], int numbersOfThreadsCol[4]);
void calculateAndPrintEfficiency(double SpeedUp[2][4]);

int main()
{
    /*         srand(time(NULL)); */
    int matrixDimensions[6] = {256, 512, 768, 1024, 1280, 1536};
    int matmatthreadsMatrixDimensions[2] = {1024, 2048};
    int numbersOfThreadsRow[4] = {1, 1, 2, 2};
    int numbersOfThreadsCol[4] = {1, 2, 2, 4};
    double execTime[2][4];
    double SpeedUp[2][4];
    int i, j, N1, N2, N3;
    int ldA = 3000, ldB = 3000, ldC = 3000;
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

        /*         printf("\n\nTempo di esecuzione per matrice C[%d x %d]:\n", N1, N3);
                calculateAllMatmatAndPrintAllExecTimes(ldA, ldB, ldC, A, B, C, N1, N2, N3, dbA, dbB, dbC); */
    }

    printf("\n\n");

    for (i = 0; i < 2; i++)
    {
        N1 = matmatthreadsMatrixDimensions[i];
        N2 = matmatthreadsMatrixDimensions[i];
        N3 = matmatthreadsMatrixDimensions[i];

        printf("\n\nTempo di esecuzione per matrice C[%d x %d]:\n", N1, N3);
        for (j = 0; j < 4; j++)
        {
            printf("\nNTrow: %d, NTcol: %d\n", numbersOfThreadsRow[j], numbersOfThreadsCol[j]);
            calculateMatmatthreadAndPrintExecTime(&execTime[i][j], ldA, ldB, ldC, A, B, C, N1, N2, N3, dbA, dbB, dbC, numbersOfThreadsRow[j], numbersOfThreadsCol[j]);
        }
    }

    calculateAndPrintSpeedUp(execTime, SpeedUp, numbersOfThreadsRow, numbersOfThreadsCol);

    calculateAndPrintEfficiency(SpeedUp);

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

void calculateMatmatthreadAndPrintExecTime(double *ExecTime, int ldA, int ldB, int ldC, double *A, double *B, double *C, int N1, int N2, int N3, int dbA, int dbB, int dbC, int NTROW, int NTCOL)
{
    double t1, t2, exec_time, Gflops, Nflops = 2.0 * N1 * N2 * N3, exponent = pow(10, 9);

    t1 = get_cur_time();
    matmatthread(ldA, ldB, ldC, A, B, C, N1, N2, N3, dbA, dbB, dbC, NTROW, NTCOL);
    t2 = get_cur_time();
    exec_time = t2 - t1;
    *ExecTime = exec_time;
    Gflops = Nflops / exec_time / exponent;
    printf(" - matmatthread execution time: %.6f seconds [%.6f Gflops]\n", exec_time, Gflops);
    C = initializeMatrixToZero(N1, N3, ldC, C);
}

void calculateAndPrintSpeedUp(double ExecTime[2][4], double SpeedUp[2][4], int numbersOfThreadsRow[4], int numbersOfThreadsCol[4])
{
    int i, j;
    printf("\nMatrice degli SpeedUp (in secondi):\n");
    printf("Dimensione\\Threads\t1\t2\t4\t8\n");
    for (i = 0; i < 2; i++)
    {
        printf("%d\t\t\t", (i + 1) * 1024);
        for (j = 0; j < 4; j++)
        {
            SpeedUp[i][j] = ExecTime[i][0] / ExecTime[i][j];
            printf("%.4f\t", SpeedUp[i][j]);
        }
        printf("\n");
    }
}

void calculateAndPrintEfficiency(double SpeedUp[2][4])
{
    int i, j;
    printf("\nMatrice delle Efficienze (in percentuale):\n");
    printf("Dimensione\\Threads\t1\t2\t4\t8\n");
    for (i = 0; i < 2; i++)
    {
        printf("%d\t\t\t", (i + 1) * 1024);
        for (j = 0; j < 4; j++)
        {
            printf("%.4f\t", (SpeedUp[i][j] / pow(2, j)));
        }
        printf("\n");
    }
}