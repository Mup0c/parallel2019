#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <omp.h>


int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    std::vector<std::vector<int> > a(N, std::vector<int>(N, 2));
    std::vector<std::vector<int> > b(N, std::vector<int>(N, 2));
    std::vector<std::vector<int> > prod(N, std::vector<int>(N, 0));

    double start_time, end_time, one_threaded_run_time;
    int num, count;




for (int threads = 1; threads <= 17; threads++){
    omp_set_num_threads(threads);
    start_time = omp_get_wtime();
#pragma omp parallel private (num)
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();
        if (num == 0)
            printf("Всего нитей: %d\n", count);
#pragma omp for
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    prod[i][j] += a[i][k] * b[k][j];
                }
            }
        }

    }
    /*
    printf("\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf(" %d ", prod[i][j]);
        }
        printf("\n");
    } */
    end_time = omp_get_wtime();
    if (threads == 1) {
        one_threaded_run_time = end_time - start_time;
    }
    double time = end_time - start_time;
    printf("Время вычисления %d потоков: %lf\n", threads, time);
    printf("Эффективность: %lf%%\n\n", threads, one_threaded_run_time/time*100);
}

    for (int threads = 1; threads <= 17; threads++){
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
#pragma omp parallel private (num)
        {
            count = omp_get_num_threads();
            num = omp_get_thread_num();
            if (num == 0)
                printf("Всего нитей: %d\n", count);
#pragma omp for
            for (int j = 0; j < N; ++j) {
                for (int i = 0; i < N; ++i) {
                    for (int k = 0; k < N; ++k) {
                        prod[i][j] += a[i][k] * b[k][j];
                    }
                }
            }

        }
        /*
        printf("\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf(" %d ", prod[i][j]);
            }
            printf("\n");
        } */
        end_time = omp_get_wtime();
        if (threads == 1) {
            one_threaded_run_time = end_time - start_time;
        }
        double time = end_time - start_time;
        printf("Время вычисления %d потоков (поменяны строки и столбцы): %lf\n", threads, time);
        printf("Эффективность: %lf%%\n\n", threads, one_threaded_run_time/time*100);
    }


    for (int threads = 1; threads <= 17; threads++){
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
#pragma omp parallel private (num)
        {
            count = omp_get_num_threads();
            num = omp_get_thread_num();
            if (num == 0)
                printf("Всего нитей: %d\n", count);
#pragma omp for
            for (int k = 0; k < N; ++k) {
                for (int j = 0; j < N; ++j) {
                    for (int i = 0; i < N; ++i) {
                        prod[i][j] += a[i][k] * b[k][j];
                    }
                }
            }

        }
        /*
        printf("\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf(" %d ", prod[i][j]);
            }
            printf("\n");
        } */
        end_time = omp_get_wtime();
        if (threads == 1) {
            one_threaded_run_time = end_time - start_time;
        }
        double time = end_time - start_time;
        printf("Время вычисления %d потоков (поменяны циклы): %lf\n", threads, time);
        printf("Эффективность: %lf%%\n\n", threads, one_threaded_run_time/time*100);
    }


}