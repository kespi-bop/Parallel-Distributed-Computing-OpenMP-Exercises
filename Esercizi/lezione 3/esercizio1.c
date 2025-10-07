#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int NT, N, id, i, start, end, A[100], sum;
    NT = 4;
    N = 100;
    omp_set_num_threads(NT);

#pragma omp parallel private(id, i, start, end)
    {
        id = omp_get_thread_num();
        start = id * N / 4;
        end = start + N / 4;

        for (i = start; i < end; i++)
        {
            A[i] = 1 + rand() % 100;
        }

        start = id * N / 4;
        printf("\n\nThread %d ha aggiunto: \n", id);
        for (i = start; i < end; i++)
        {
            printf("%d, ", A[i]);
        }
    }

#pragma omp parallel private(id, i, start, end, sum)
    {
        id = omp_get_thread_num();
        start = id * N / 4;
        end = start + N / 4;
        sum = 0;

        for (i = start; i < end; i++)
        {
            sum = sum + A[i];
        }

        printf("\n\n");
        printf("sum of thread %d of %d: ", id, NT);
        printf("%d\n", sum);
    }
}