/*lo pseudocodice grezzo è sugli appunti random*/
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

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

matmatdist(MPI_Comm Gridcom, int LDA, int LDB, int LDC, double *A, double *B, double *C, int N1, int N2, int N3, int DB1, int DB2, int DB3, int NTROW, int NTCOL)
{
    int i, j, k, c, r, elementIndex, griddims[2], gridperiods[2], coord[2], rowdir[2], coldir[2], k1, k2, k3, a, b, rowInBlockA, colInBlockB, rowcolInBlockBA, dimBlockAtoSend, dimBlockBtoSend;
    double *Acol, *Brow, ptrA, ptrB;
    MPI_Comm rowcomm, colcomm;

    MPI_Cart_get(Gridcom, 2, griddims, gridperiods, coord);

    //creo canale di comunicazione per Bcast lungo la riga (quindi vario nelle colonne)
    rowdir[0] = 0;
    rowdir[1] = 1;

    MPI_Cart_sub(Gridcom, rowdir, &rowcomm);

    //creo canale di comunicazione per Bcast lungo la colonna (quindi vario nelle righe)
    coldir[0] = 1;
    coldir[1] = 0;

    MPI_Cart_sub(Gridcom, coldir, &colcomm);

    k1 = griddims[0];
    k3 = griddims[1];

    // calcolo del MCD tra k1 e k3
    a = k1;
    b = k3;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    // calcolo del mcm tra k1 e k3 per avere k2
    k2 = (k1 * k3) / a;

    // quante righe e col ci sono nei blocchi (necessario per poter calcolare la dimensione dei blocchi)
    rowInBlockA = N1 / k1;
    colInBlockB = N3 / k3;
    rowcolInBlockBA = N2 / k2;

    // dimensione dei blocchi da spedire
    dimBlockAtoSend = rowInBlockA * rowcolInBlockBA;
    dimBlockBtoSend = rowcolInBlockBA * colInBlockB;

    Acol = (double *)malloc(sizeof(double) * dimBlockAtoSend);
    Brow = (double *)malloc(sizeof(double) * dimBlockBtoSend);

    ptrA = A;
    ptrB = B;

    for (k = 0; k < k2; k++)
    {
        c = k % N3;
        r = k % N1;

        // preparo blocco A da spedire
        if (c == coord[1])
        {
            elementIndex = 0;
            for (i = 0; i < rowInBlockA; i++)
            {
                for (j = 0; j < rowcolInBlockBA; j++)
                {
                    Acol[elementIndex] = ptrA[i * LDA + j];
                    elementIndex++;
                }
            }
            ptrA = ptrA + rowcolInBlockBA;
        }

        // preparo blocco A da spedire
        if (r == coord[0])
        {
            elementIndex = 0;
            for (i = 0; i < rowcolInBlockBA; i++)
            {
                for (j = 0; j < colInBlockB; j++)
                {
                    Brow[elementIndex] = ptrB[i * LDB + j];
                    elementIndex++;
                }
            }
            ptrB = ptrB + (rowcolInBlockBA * LDB);
        }

        // Bcast A lungo la riga i
        MPI_Bcast(Acol, dimBlockAtoSend, MPI_DOUBLE, c, rowcomm);
        // Bcarst B lungo la colonna j
        MPI_Bcast(Brow, dimBlockBtoSend, MPI_DOUBLE, r, colcomm);

        // ricevo in blocco A e blocco B in Acol e Brow
        void matmatthread(rowcolInBlockBA, colInBlockB, LDC, Acol, Brow, C,
                          rowInBlockA, rowcolInBlockBA, colInBlockB, DB1, DB2, DB3, NTROW, NTCOL);
    }

    free(Acol);
    free(Brow);
}