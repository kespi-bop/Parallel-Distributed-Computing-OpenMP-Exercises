/* QUESTO ESERCIZIO RESTITUISCE VALORI CASUALI TRA -100000 E 100000,
E' UN ESEMPIO DI PROBLEMA DI CORSA CRITICA */

#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int NT, id, i, A, SUM;
    SUM = 0;
    NT = 4;
    omp_set_num_threads(NT);

#pragma omp parallel private(id, i, A)
    {
        id = omp_get_thread_num();

        A = 1 - 2 * (id % 2);

        for (i = 0; i < 100000; i++)
        {
            SUM = SUM + A;
        }
    }

    printf("La somma è: %d \n", SUM);
}