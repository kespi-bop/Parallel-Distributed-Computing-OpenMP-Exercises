#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int *instanceArray(int N, int *A);
int *fillArray(int N, int *A);
void printArray(int N, int *A);

int main(int argc, char *argv[])
{
    /*         srand(time(NULL)); */
    int i, myid, token, NP, stot, N = 40, sum = 0, *A;
    MPI_Status status;

    A = instanceArray(N, A);
    A = fillArray(N, A);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &NP);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // faccio stampare solo una volta
    if (myid == 0)
    {
        printArray(N, A);
    }

    for (i = myid * N/NP; i < myid * N/NP + N/NP; i++)
    {
        sum = sum + A[i];
    }
    printf("\nil processo %d ha calcolato [%d]\n", myid, sum);
    stot = sum;
    token = sum;
    for (i = 0; i < NP - 1; i++)
    {
        MPI_Send(&token, 1, MPI_INT, (myid + NP + 1) % NP, 10, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, (myid + NP - 1) % NP, 10, MPI_COMM_WORLD, &status);
        stot = stot + token;
    }
    printf("\nil processo %d ha come somma totale {[%d]}", myid, stot);

    MPI_Finalize();

    printf("\n\n");
    free(A);
    return 0;
}

int *instanceArray(int LD, int *A)
{
    A = (int *)malloc(LD * sizeof(int));
    return A;
}

int *fillArray(int N, int *A)
{
    int i;

    for (i = 0; i < N; i++)
    {
        A[i] = (int)(rand() % 100);
    }

    return A;
}

void printArray(int N, int *A)
{
    int i;
    printf("\nArray di dimensione %d:\n\n", N);
    printf("[");
    for (i = 0; i < N; i++)
    {

        printf("%d ", A[i]);
    }
    printf("\b]");
}