#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

struct pr {
    double h;
    int for_cnt;
    int numi;
    double sum;
};

void* test_f(void *arg_func)
{
    struct pr* tmp = (struct pr*)(arg_func);    
    for (int i = 0; i < tmp->for_cnt; i++) {
        double x = tmp->h * ((double)(tmp->numi + i) + 0.5);
        x = (4.0 / (1.0 + x * x));
        tmp->sum += + x;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf (stderr, "Less of arguments\n");
        return 1;
    }
    struct timeval start_timer, end_timer;
    gettimeofday(&start_timer, NULL);

    int num_intervals = atoi(argv[1]), num_threads = atoi(argv[2]);
    struct pr arg_func[num_threads];
    int i = 0;
    for (i = 0; i < num_threads; i++) {
        arg_func[i].h = 1.0 / (double)num_intervals;
        arg_func[i].for_cnt = num_intervals / num_threads;
        arg_func[i].numi = i * arg_func[i].for_cnt;
        arg_func[i].sum = 0.0;
    }
    arg_func[num_threads - 1].for_cnt += num_intervals % num_threads;
    
    pthread_t thread[num_threads];
    for (i = 0; i < num_threads; i++) {
        int test = pthread_create(&thread[i], NULL, test_f, &arg_func[i]);
        assert(test == 0);
    }
    double ans = 0.0;
    for (int j = 0; j < num_threads; j++) {
        int status;
        pthread_join(thread[j], (void *) &status);
        ans += arg_func[j].sum;
    }

    double pi = 0.0;
    pi = arg_func[0].h * ans;
    
    printf("%f\n", pi);
    gettimeofday(&end_timer, NULL);

    printf("Elapsed time: %f\n", (double)(end_timer.tv_usec - start_timer.tv_usec) / 1000000.0 + end_timer.tv_sec - start_timer.tv_sec);

    return 0;
}