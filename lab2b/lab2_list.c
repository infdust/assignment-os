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
#include <sys/sem.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <stdatomic.h>
#include "SortedList.h"
typedef struct threadParam
{
    SortedList_t *lists;
    SortedListElement_t *eles;
    int iterationnum;
    unsigned long long *time_used;
} threadParam;
int threadnum = 1;
int iterationnum = 1;
int bucketnum = 1;
int opt_sync = 0; // none m s
pthread_mutex_t *pmutex[64];
bool *pspin[64];
int *access_allow[64];
unsigned long long *time_used[64];
void lockw_m(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    pthread_mutex_lock(pmutex[bucket]);
    while (access_allow[bucket][0] < threadnum)
    {
        pthread_mutex_unlock(pmutex[bucket]);
        sched_yield();
        pthread_mutex_lock(pmutex[bucket]);
    }
    access_allow[bucket][0] -= threadnum;
    pthread_mutex_unlock(pmutex[bucket]);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void unlockw_m(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    pthread_mutex_lock(pmutex[bucket]);
    access_allow[bucket][0] += threadnum;
    pthread_mutex_unlock(pmutex[bucket]);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void lockr_m(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    pthread_mutex_lock(pmutex[bucket]);
    while (access_allow[bucket][0] < 1)
    {
        pthread_mutex_unlock(pmutex[bucket]);
        sched_yield();
        pthread_mutex_lock(pmutex[bucket]);
    }
    --access_allow[bucket][0];
    pthread_mutex_unlock(pmutex[bucket]);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void unlockr_m(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    pthread_mutex_lock(pmutex[bucket]);
    ++access_allow[bucket][0];
    pthread_mutex_unlock(pmutex[bucket]);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void lockw_s(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    while (atomic_exchange(pspin[bucket], true))
        ;
    while (access_allow[bucket][0] < threadnum)
    {
        atomic_store(pspin[bucket], false);
        sched_yield();
        while (atomic_exchange(pspin[bucket], true))
            ;
    }
    access_allow[bucket][0] -= threadnum;
    atomic_store(pspin[bucket], false);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void unlockw_s(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    while (atomic_exchange(pspin[bucket], true))
        ;
    access_allow[bucket][0] += threadnum;
    atomic_store(pspin[bucket], false);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void lockr_s(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    while (atomic_exchange(pspin[bucket], true))
        ;
    while (access_allow[bucket][0] < 1)
    {
        atomic_store(pspin[bucket], false);
        sched_yield();
        while (atomic_exchange(pspin[bucket], true))
            ;
    }
    --access_allow[bucket][0];
    atomic_store(pspin[bucket], false);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void unlockr_s(unsigned long long *time_used, u_int64_t bucket)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used -= (1000000000ull * time.tv_sec + time.tv_nsec);
    bucket %= bucketnum;
    while (atomic_exchange(pspin[bucket], true))
        ;
    ++access_allow[bucket][0];
    atomic_store(pspin[bucket], false);
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (time_used)
        *time_used += (1000000000ull * time.tv_sec + time.tv_nsec);
}
void *func_thread(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
        SortedList_insert(params->time_used, params->lists + hash64(params->eles[i].key) % bucketnum, params->eles + i);
    for (int i = 0; i < bucketnum; ++i)
        SortedList_length(params->time_used, params->lists + i);
    for (int i = 0; i < params->iterationnum; ++i)
        SortedList_delete(params->time_used, SortedList_lookup(params->time_used, params->lists + hash64(params->eles[i].key) % bucketnum, params->eles[i].key));
    return NULL;
}
int main(int argc, char **argv)
{
    int chr = 1;
    struct option options[] = {
        {"threads", required_argument, NULL, 't'},
        {"iterations", required_argument, NULL, 'i'},
        {"lists", required_argument, NULL, 'l'},
        {"yield", required_argument, NULL, 'y'},
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
        case 'l':
            bucketnum = atoi(optarg);
            break;
        case 'y':
            if (false)
                ;
            else if (!strcmp(optarg, "i"))
                opt_yield = INSERT_YIELD;
            else if (!strcmp(optarg, "d"))
                opt_yield = DELETE_YIELD;
            else if (!strcmp(optarg, "l"))
                opt_yield = LOOKUP_YIELD;
            else if (!strcmp(optarg, "id"))
                opt_yield = INSERT_YIELD | DELETE_YIELD;
            else if (!strcmp(optarg, "il"))
                opt_yield = INSERT_YIELD | LOOKUP_YIELD;
            else if (!strcmp(optarg, "dl"))
                opt_yield = DELETE_YIELD | LOOKUP_YIELD;
            else if (!strcmp(optarg, "idl"))
                opt_yield = INSERT_YIELD | DELETE_YIELD | LOOKUP_YIELD;
            else
                exit(1);
            break;
        case 's':
            if (false)
                ;
            else if (!strcmp(optarg, "m"))
                opt_sync = 1;
            else if (!strcmp(optarg, "s"))
                opt_sync = 2;
            else
                exit(1);
            break;
        case '?':
            exit(1);
            break;
        }
    struct timespec time_begin;
    struct timespec time_end;
    FILE *csv = fopen("lab2_list.csv", "a+");
    if (!csv)
        exit(1);
    for (int i = 0; i < 64; ++i)
        access_allow[i] = (int *)malloc(sizeof(int)), access_allow[i][0] = threadnum;
    for (int i = 0; i < 64; ++i)
        time_used[i] = (unsigned long long *)malloc(sizeof(unsigned long long)), time_used[i][0] = 0;
    pthread_t *threads = (pthread_t *)malloc(threadnum * sizeof(pthread_t));
    SortedList_t *list = (SortedList_t *)malloc(bucketnum * sizeof(SortedList_t));
    threadParam *params = (threadParam *)malloc(threadnum * sizeof(threadParam));
    SortedListElement_t *eles = (SortedListElement_t *)malloc((u_int64_t)threadnum * iterationnum * sizeof(SortedListElement_t));
    char *keys = (char *)malloc((u_int64_t)threadnum * iterationnum * 32 * sizeof(char));
    for (int i = 0; i < bucketnum; ++i)
    {
        list[i].prev = list + i;
        list[i].next = list + i;
        list[i].key = (char *)i;
    }
    for (int i = 0; i < threadnum; ++i)
    {
        params[i].iterationnum = iterationnum;
        params[i].lists = list;
        params[i].eles = eles + iterationnum * i;
        params[i].time_used = time_used[i];
        for (int j = 0; j < iterationnum; ++j)
        {
            params[i].eles[j].prev = NULL;
            params[i].eles[j].next = NULL;
            unsigned long long key = i;
            key *= iterationnum;
            key += j;
            params[i].eles[j].key = keys + key * 32;
            key *= 0x0123456789abcdef;
            snprintf(params[i].eles[j].key, 32, "%llu", key);
        }
    }
    {
        switch (opt_sync)
        {
        case 0: // none
            break;
        case 1: // m
        {
            func_lockw = lockw_m;
            func_unlockw = unlockw_m;
            func_lockr = lockr_m;
            func_unlockr = unlockr_m;
            int fd = open("/dev/zero", O_RDWR, 0);
            if (fd < 0)
                exit(1);
            for (int i = 0; i < 64; ++i)
                pmutex[i] = (pthread_mutex_t *)mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            close(fd);
            pthread_mutexattr_t attr;
            if (pthread_mutexattr_init(&attr) < 0)
                exit(1);
            if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) < 0)
                exit(1);
            for (int i = 0; i < 64; ++i)
                if (pthread_mutex_init(pmutex[i], &attr) < 0)
                    exit(1);
        }
        break;
        case 2: // s
            func_lockw = lockw_s;
            func_unlockw = unlockw_s;
            func_lockr = lockr_s;
            func_unlockr = unlockr_s;
            for (int i = 0; i < 64; ++i)
                pspin[i] = (bool *)malloc(sizeof(bool));
            for (int i = 0; i < 64; ++i)
                pspin[i][0] = false;
            break;
        }
        clock_gettime(CLOCK_MONOTONIC, &time_begin);
        for (int i = 0; i < threadnum; ++i)
            pthread_create(threads + i, NULL, func_thread, params + i);
        for (int i = 0; i < threadnum; ++i)
            pthread_join(threads[i], NULL);
        clock_gettime(CLOCK_MONOTONIC, &time_end);

        for (int i = 0; i < bucketnum; ++i)
            if (SortedList_length(NULL, list + i))
                exit(2);

        unsigned long long total_nanosec = time_end.tv_sec - time_begin.tv_sec;
        total_nanosec *= 1000000000;
        total_nanosec += (time_end.tv_nsec - time_begin.tv_nsec);
        unsigned long long avg_nanosec = total_nanosec;
        avg_nanosec /= threadnum;
        avg_nanosec /= iterationnum;
        char *yielddesc[8] = {"-none", "-i", "-d", "-id", "-l", "-il", "-dl", "-idl"};
        char *syncdesc[4] = {"-none", "-m", "-s", "-c"};
        unsigned long long time_total = 0;
        for (int i = 0; i < 64; ++i)
            time_total += time_used[i][0];
        fprintf(csv, "list%s%s,%i,%i,%i,%i,%llu,%llu,%llu\n",
                yielddesc[opt_yield], syncdesc[opt_sync], threadnum, iterationnum, bucketnum, threadnum * iterationnum * 3, total_nanosec, avg_nanosec, time_total);
    }
    for (int i = 0; i < 64; ++i)
        free(time_used[i]);
    for (int i = 0; i < 64; ++i)
        free(pspin[i]);
    free(keys);
    free(eles);
    free(params);
    free(list);
    free(threads);
    for (int i = 0; i < 64; ++i)
        free(access_allow[i]);
    fclose(csv);
    return 0;
}