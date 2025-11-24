#include <omp.h>

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
    int k, j, i;
    for (k = 0; k < N2; k++)
    {
        for (j = 0; j < N3; j++)
        {
            for (i = 0; i < N1; i++)
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

void matmatblock(int ldA, int ldB, int ldC, double *A, double *B, double *C, int N1, int N2, int N3, int dbA, int dbB, int dbC)
{
    int ii, jj, kk;
    for (ii = 0; ii < N1 / dbA; ii++)
    {
        for (jj = 0; jj < N3 / dbC; jj++)
        {
            for (kk = 0; kk < N2 / dbB; kk++)
            {
                matmatikj(ldA, ldB, ldC, &A[(ii * ldA + kk) * dbA], &B[(kk * ldB + jj) * dbB], &C[(ii * ldC + jj) * dbC], dbA, dbB, dbC);
            }
        }
    }
}

void matmatthread(int ldA, int ldB, int ldC, double *A, double *B, double *C,
                  int N1, int N2, int N3, int dbA, int dbB, int dbC, int NTROW, int NTCOL)
{
    int id, IDi, IDj, starti, startj;
    int NT = NTROW * NTCOL;

    omp_set_num_threads(NT);

#pragma omp parallel private(id, IDi, IDj, starti, startj)
    {
        id = omp_get_thread_num();
        IDi = id / NTCOL;
        IDj = id % NTCOL;

        starti = IDi * (N1 / NTROW);
        startj = IDj * (N3 / NTCOL);

        matmatblock(ldA, ldB, ldC, &A[starti * ldA], &B[startj], &C[starti * ldC + startj], N1 / NTROW, N2, N3 / NTCOL, dbA, dbB, dbC);
    }
}