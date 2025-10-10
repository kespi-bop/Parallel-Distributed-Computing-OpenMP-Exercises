#include <math.h>
#include <omp.h>


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
            
            for (j = 0; j < N; j++)
            {
                sum = sum + sqrt(A[i * LD + j]);
            }

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