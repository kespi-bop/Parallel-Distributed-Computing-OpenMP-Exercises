#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int NT, id, i, A, SUM;
    SUM = 0;
    NT = 4;
    omp_lock_t lock;
    omp_init_lock(&lock);
    omp_set_num_threads(NT);

#pragma omp parallel private(id, i, A)
    {
        id = omp_get_thread_num();

        A = 1 - 2 * (id % 2);

        for (i = 0; i < 100000; i++)
        {
#pragma omp critical
            {
                SUM = SUM + A;
            }
/* #pragma omp atomic 
                SUM = SUM + A;
usata per operazioni atomiche molto semplici, cioè un'unica operazione su una variabile,
qundi in questo caso per esempio era meglio usare l'atomic */
        }
    }

    printf("La somma è: %d \n", SUM);
}