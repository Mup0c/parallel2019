#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <omp.h>

int main(int argc, char *argv[]) {
    srand(time(0));
    int N = atoi(argv[1]);
    std::vector<int> a;
    int lcmax = 0;
    for (int i = 0; i < N; ++i) {
        a.push_back(int(std::rand()));
    }
    for (int i = 0; i < N; ++i) {
        lcmax = std::max(lcmax, a[i]);
    }
    double start_time, end_time;
    int max, num, count, local_max;
    printf("Максимум: %ld\n", lcmax);


//2
    omp_set_num_threads(2);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 2 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

    //4
    omp_set_num_threads(4);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 4 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

    //5
    omp_set_num_threads(5);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 5 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

    //8
    omp_set_num_threads(8);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 8 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

    //2
    omp_set_num_threads(16);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 16 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

    //27
    omp_set_num_threads(27);
    max = 0;
    start_time = omp_get_wtime();
#pragma omp parallel private(local_max,i)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
        local_max = 0;
#pragma omp for
        for (int i = 0; i < N; ++i) {
            local_max = std::max(local_max, a[i]);
        }
#pragma omp critical
        max = std::max(local_max, max);
    }
    end_time = omp_get_wtime();
    printf("Время вычисления 27 потока: %lf\n", end_time - start_time);
    printf("max: %d\n", max);

}