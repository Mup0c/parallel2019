#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[]) {
//Задание 1
    printf("\n -check openmp support-\n");
#ifdef _OPENMP
    printf("OpenMP is supported!\n");
#endif

    printf("Последовательная область 1\n");
#pragma omp parallel
    {
        printf("Параллельная область\n");
    }
    printf("Последовательная область 2\n");

    int count, num;
//Задание 2
    printf("\n -threads num and IDs-\n");
#pragma omp parallel private(num)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0) {
            printf("Всего нитей: %d\n", count);
            printf("Нить номер %d\n", num);
        } else
            printf("Нить номер %d\n", num);
    }

//Обратный порядок
    printf("\n -sorted-\n");
    for (int i = count - 1; i >= 0; i--) {
#pragma omp parallel private(num)
        {
            count = omp_get_num_threads();
            num = omp_get_thread_num();
            if (num == i) {
                printf("Нить номер %d\n", num);
            }
        }
    }


//set num threads
    printf("\n -set num-\n");
    printf("\n -3-\n");
    for (int i = count - 1; i >= 0; i--) {
        omp_set_num_threads(2);
#pragma omp parallel num_threads(3) private(num)
        {
            count = omp_get_num_threads();
            num = omp_get_thread_num();
            if (num == i) {
                printf("Нить номер %d\n", num);
            }
        }
    }
    printf("\n -2-\n");
    for (int i = count - 1; i >= 0; i--) {
#pragma omp parallel private(num)
        {
            count = omp_get_num_threads();
            num = omp_get_thread_num();
            if (num == i) {
                printf("Нить номер %d\n", num);
            }
        }
    }

}