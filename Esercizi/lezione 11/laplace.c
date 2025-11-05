#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

void laplace(float *A, float *B, float *daprev, float *danext, int N, int LD, int Niter)
{

    int nproc, myid, i, j, iter;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    for (iter = 0; iter < Niter; iter++)
    {

        if (myid != 0)
        {
            for (j = 0; j < N; j++)
            {
                daprev[j] = A[j];
            }

            MPI_Send(daprev, N, MPI_FLOAT, myid - 1, iter, MPI_COMM_WORLD);
            MPI_Recv(daprev, N, MPI_FLOAT, myid - 1, iter, MPI_COMM_WORLD, &status);
        }

        if (myid != nproc - 1)
        {
            for (j = 0; j < N; j++)
            {
                danext[j] = A[(N / nproc - 1) * LD + j];
            }

            MPI_Send(danext, N, MPI_FLOAT, myid + 1, iter, MPI_COMM_WORLD);
            MPI_Recv(danext, N, MPI_FLOAT, myid + 1, iter, MPI_COMM_WORLD, &status);
        }

        if (myid != 0)
        {
            for (j = 1; j < N - 1; j++)
            {
                B[j] = (daprev[j] + A[1 * LD + j] + A[j - 1] + A[j + 1]) * 0.25;
            }
        }

        for (i = 1; i < N / nproc - 1; i++)
        {
            for (j = 1; j < N - 1; j++)
            {
                B[(i * LD) + j] = (A[(i + 1) * LD + j] + A[(i - 1) * LD + j] + A[(i * LD) + (j - 1)] + A[(i * LD) + (j + 1)]) * 0.25;
            }
        }

        if (myid != nproc - 1)
        {
            for (j = 1; j < N - 1; j++)
            {
                B[((N / nproc - 1) * LD) + j] = (danext[j] + A[((N / nproc - 1) - 1) * LD + j] + A[((N / nproc - 1) * LD) + (j - 1)] + A[((N / nproc - 1) * LD) + (j + 1)]) * 0.25;
            }
        }

        if (myid != 0)
        {
            for (j = 1; j < N - 1; j++)
            {
                A[j] = B[j];
            }
        }

        for (i = 1; i < N / nproc - 1; i++)
        {
            for (j = 1; j < N - 1; j++)
            {
                A[(i * LD) + j] = B[(i * LD) + j];
            }
        }

        if (myid != nproc - 1)
        {
            for (j = 1; j < N - 1; j++)
            {
                A[((N / nproc - 1) * LD) + j] = B[((N / nproc - 1) * LD) + j];
            }
        }
    }

    return;
}

void laplace_nb(float *A, float *B, float *daprev, float *danext,
                int N, int LD, int Niter)
{
}
