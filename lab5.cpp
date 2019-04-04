#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <omp.h>

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    std::vector<int> a (N, 2);
    std::vector<int> b (N, 2);
    double start_time, end_time;
    int prod, num, count, local_prod;

//1
    start_time = omp_get_wtime();
    prod = 0;
    for (int i = 0; i < N; ++i) {
        prod += a[i] * b[i];
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 1 поток: %lf\n", end_time-start_time);
    printf("Произведение: %d\n", prod);



//2
    omp_set_num_threads(2);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 2 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);

//3
    omp_set_num_threads(3);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 3 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);

//4
    omp_set_num_threads(4);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 4 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);
//5
    omp_set_num_threads(5);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 5 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);


//8
    omp_set_num_threads(8);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 8 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);

//16
    omp_set_num_threads(16);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 16 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);

    //27
    omp_set_num_threads(27);
    prod = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_prod,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_prod = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_prod += a[i] * b[i];
            //printf("%d, thread %d\n", i, num);
        }
#pragma omp atomic
        prod += local_prod;
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 27 поток: %lf\n", end_time - start_time);
    printf("Произведение: %d\n", prod);
}