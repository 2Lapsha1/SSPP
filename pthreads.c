#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

static double sum = 0.0;

struct pr {
    double h;
    int numi;
    int for_cnt;
};

void* test_f(void *arg_func)
{
    struct pr* tmp = (struct pr*)(arg_func);    
    for (int i = 0; i < tmp->for_cnt; i++) {
        double x = tmp->h * ((double)(tmp->numi + i) + 0.5);
        sum += (4.0 / (1.0 + x * x));
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    struct timeval start_timer, end_timer;
    gettimeofday(&start_timer, NULL);

    pthread_t thread;
    
    int num_intervals = atoi(argv[1]), num_threads = atoi(argv[2]);
    struct pr arg_func = {1.0 / (double)num_intervals, 0, num_intervals / num_threads};
    int i = 0;
    for (i = 0; i < num_threads; i++) {
        arg_func.numi = i * arg_func.for_cnt;
        int test = pthread_create(&thread, NULL, test_f, &arg_func);
        assert(test == 0);
        int status;
        pthread_join(thread, (void *) &status);
    }
    arg_func.for_cnt = num_intervals % num_threads;
    for (int j = 0; j < arg_func.for_cnt; j++) {
        double x = arg_func.h * (j + i * (num_intervals / num_threads) + 0.5);
        sum += (4.0 / (1.0 + x * x));
    }
    double pi = 0.0;
    pi = arg_func.h * sum;
    
    printf("%f\n", pi);
    gettimeofday(&end_timer, NULL);

    printf("Elapsed time: %f\n", (double)(end_timer.tv_usec - start_timer.tv_usec) / 1000000.0 + end_timer.tv_sec - start_timer.tv_sec);

    return 0;
}
