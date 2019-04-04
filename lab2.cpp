#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int count = 0;
#pragma omp parallel reduction (+: count)
    {
        count++;
        printf("Текущее значение count: %d\n", count);
    }
    printf("Число нитей: %d\n", count);


    int A[1000], i, n;
    int sum = 0;
/* Заполним исходные массивы */
    for (i=0; i<1000; i++){
        A[i]=1;
    }
#pragma omp parallel shared(A) private(i, n) reduction (+: sum)
    {
/* Получим номер текущей нити */
        n=omp_get_thread_num();
#pragma omp for
        for (i=0; i<1000; i++)
        {
            sum += A[i];
            printf("Нить %d сложила элементы с номером %d\n", n, i);
        }
    }
    printf("%d\n",sum);

    sum = 0;
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < 1000; ++i)
#pragma omp atomic
            sum += A[i];
    }
    printf("%d\n",sum);

    sum = 0;
#pragma omp parallel
    {

        #pragma omp for
        for (int i = 0; i < 1000; ++i)
            #pragma omp critical
                    sum += A[i];

    }
    printf("%d\n",sum);
}


