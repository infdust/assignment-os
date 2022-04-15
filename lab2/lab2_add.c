#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <stdatomic.h>
typedef struct threadParam
{
    long long *pointer;
    int iterationnum;
} threadParam;
int threadnum = 1;
int iterationnum = 1;
int opt_sync = 0; // none m s c
bool opt_yield = false;
pthread_mutex_t *pmutex;
bool *pspin = NULL;
void add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    if (opt_yield)
        sched_yield();
    *pointer = sum;
}
void *threadfunc_none(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
        add(params->pointer, 1);
    for (int i = 0; i < params->iterationnum; ++i)
        add(params->pointer, -1);
    return NULL;
}
void *threadfunc_m(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
        pthread_mutex_lock(pmutex), add(params->pointer, 1), pthread_mutex_unlock(pmutex);
    for (int i = 0; i < params->iterationnum; ++i)
        pthread_mutex_lock(pmutex), add(params->pointer, -1), pthread_mutex_unlock(pmutex);
    return NULL;
}
void *threadfunc_s(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
    {
        while (atomic_exchange(pspin, true))
            ;
        add(params->pointer, 1);
        atomic_store(pspin, false);
    }
    for (int i = 0; i < params->iterationnum; ++i)
    {
        while (atomic_exchange(pspin, true))
            ;
        add(params->pointer, -1);
        atomic_store(pspin, false);
    }
    return NULL;
}
void *threadfunc_c(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
    {
        long long temp = *(params->pointer);
        if (opt_yield)
            sched_yield();
        while (!atomic_compare_exchange_strong(params->pointer, &temp, 1 + temp))
            if (opt_yield)
                sched_yield();
    }
    for (int i = 0; i < params->iterationnum; ++i)
    {
        long long temp = *(params->pointer);
        if (opt_yield)
            sched_yield();
        while (!atomic_compare_exchange_strong(params->pointer, &temp, -1 + temp))
            if (opt_yield)
                sched_yield();
    }
    return NULL;
}
int main(int argc, char **argv)
{
    int chr = 1;
    struct option options[] = {
        {"threads", required_argument, NULL, 't'},
        {"iterations", required_argument, NULL, 'i'},
        {"yield", no_argument, NULL, 'y'},
        {"sync", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0},
    };
    while ((chr = getopt_long(argc, argv, "", options, NULL)) != -1)
        switch (chr)
        {
        case 't':
            threadnum = atoi(optarg);
            break;
        case 'i':
            iterationnum = atoi(optarg);
            break;
        case 'y':
            opt_yield = true;
            break;
        case 's':
            if (false)
                ;
            else if (!strcmp(optarg, "m"))
                opt_sync = 1;
            else if (!strcmp(optarg, "s"))
                opt_sync = 2;
            else if (!strcmp(optarg, "c"))
                opt_sync = 3;
            break;
        case '?':
            fprintf(stderr,
                    "expected arguments:\n--input(=path)\n--output(=path)\n--segfault\n--catch\n--dump-core\n");
            exit(1);
            break;
        }
    struct timespec time_begin;
    struct timespec time_end;
    FILE *csv = fopen("lab2_add.csv", "a+");
    if (!csv)
        exit(1);
    pthread_t *threads = (pthread_t *)malloc(threadnum * sizeof(pthread_t));
    long long counter;
    threadParam *param = (threadParam *)malloc(sizeof(threadParam));
    param->pointer = &counter;
    param->iterationnum = iterationnum;
    {
        counter = 0;
        switch (opt_sync)
        {
        case 0: // none
            break;
        case 1: // m
        {
            int fd = open("/dev/zero", O_RDWR, 0);
            if (fd < 0)
                exit(1);
            pmutex = (pthread_mutex_t *)mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            close(fd);
            pthread_mutexattr_t attr;
            if (pthread_mutexattr_init(&attr) < 0)
                exit(1);
            if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) < 0)
                exit(1);
            if (pthread_mutex_init(pmutex, &attr) < 0)
                exit(1);
        }
        break;
        case 2: // s
            pspin = (bool *)malloc(sizeof(bool));
            *pspin = false;
            break;
        case 3: // c
            break;
        }
        void *(*funcs[])(void *) = {threadfunc_none, threadfunc_m, threadfunc_s, threadfunc_c};
        clock_gettime(CLOCK_MONOTONIC, &time_begin);
        for (int i = 0; i < threadnum; ++i)
            pthread_create(threads + i, NULL, funcs[opt_sync], param);
        for (int i = 0; i < threadnum; ++i)
            pthread_join(threads[i], NULL);

        clock_gettime(CLOCK_MONOTONIC, &time_end);

        unsigned long long total_iternum = threadnum;
        total_iternum *= iterationnum;
        total_iternum *= 2;
        unsigned long long total_nanosec = time_end.tv_sec - time_begin.tv_sec;
        total_nanosec *= 1000000000;
        total_nanosec += (time_end.tv_nsec - time_begin.tv_nsec);
        unsigned long long avg_nanosec = total_nanosec;
        avg_nanosec /= total_iternum;
        char *syncdesc[4] = {"-none", "-m", "-s", "-c"};
        fprintf(csv, "add%s%s, %i, %i, %llu, %llu, %llu, %lli\n",
                opt_yield ? "-yield" : "", syncdesc[opt_sync], threadnum, iterationnum, total_iternum, total_nanosec, avg_nanosec, counter);
    }
    free(pspin);
    free(param);
    free(threads);
    fclose(csv);
    return 0;
}