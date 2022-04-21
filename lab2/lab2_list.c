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
    SortedList_t *list;
    SortedListElement_t *eles;
    int iterationnum;
} threadParam;
int threadnum = 1;
int iterationnum = 1;
int opt_sync = 0; // none m s
pthread_mutex_t *pmutex;
bool *pspin = NULL;
int *access_allow = NULL;
void lockw_m()
{
    pthread_mutex_lock(pmutex);
    while (*access_allow < threadnum)
    {
        pthread_mutex_unlock(pmutex);
        sched_yield();
        pthread_mutex_lock(pmutex);
    }
    *access_allow -= threadnum;
    pthread_mutex_unlock(pmutex);
}
void unlockw_m()
{
    pthread_mutex_lock(pmutex);
    *access_allow += threadnum;
    pthread_mutex_unlock(pmutex);
}
void lockr_m()
{
    pthread_mutex_lock(pmutex);
    while (*access_allow < 1)
    {
        pthread_mutex_unlock(pmutex);
        sched_yield();
        pthread_mutex_lock(pmutex);
    }
    --*access_allow;
    pthread_mutex_unlock(pmutex);
}
void unlockr_m()
{
    pthread_mutex_lock(pmutex);
    ++*access_allow;
    pthread_mutex_unlock(pmutex);
}
void lockw_s()
{
    while (atomic_exchange(pspin, true))
        ;
    while (*access_allow < threadnum)
    {
        atomic_store(pspin, false);
        sched_yield();
        while (atomic_exchange(pspin, true))
            ;
    }
    *access_allow -= threadnum;
    atomic_store(pspin, false);
}
void unlockw_s()
{
    while (atomic_exchange(pspin, true))
        ;
    *access_allow += threadnum;
    atomic_store(pspin, false);
}
void lockr_s()
{
    while (atomic_exchange(pspin, true))
        ;
    while (*access_allow < 1)
    {
        atomic_store(pspin, false);
        sched_yield();
        while (atomic_exchange(pspin, true))
            ;
    }
    --*access_allow;
    atomic_store(pspin, false);
}
void unlockr_s()
{
    while (atomic_exchange(pspin, true))
        ;
    ++*access_allow;
    atomic_store(pspin, false);
}
void *func_thread(void *pparam)
{
    const threadParam *params = (const threadParam *)pparam;
    for (int i = 0; i < params->iterationnum; ++i)
        SortedList_insert(params->list, params->eles + i);
    SortedList_length(params->list);
    for (int i = 0; i < params->iterationnum; ++i)
        SortedList_delete(SortedList_lookup(params->list, params->eles[i].key));
    return NULL;
}
int main(int argc, char **argv)
{
    int chr = 1;
    struct option options[] = {
        {"threads", required_argument, NULL, 't'},
        {"iterations", required_argument, NULL, 'i'},
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
    access_allow = (int *)malloc(sizeof(int));
    *access_allow = threadnum;
    pthread_t *threads = (pthread_t *)malloc(threadnum * sizeof(pthread_t));
    SortedList_t *list = (SortedList_t *)malloc(sizeof(SortedList_t));
    threadParam *params = (threadParam *)malloc(threadnum * sizeof(threadParam));
    SortedListElement_t *eles = (SortedListElement_t *)malloc((size_t)threadnum * iterationnum * sizeof(SortedListElement_t));
    char *keys = (char *)malloc((size_t)threadnum * iterationnum * 32 * sizeof(char));
    list->prev = list;
    list->next = list;
    list->key = NULL;
    for (int i = 0; i < threadnum; ++i)
    {
        params[i].iterationnum = iterationnum;
        params[i].list = list;
        params[i].eles = eles + iterationnum * i;
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
            func_lockw = lockw_s;
            func_unlockw = unlockw_s;
            func_lockr = lockr_s;
            func_unlockr = unlockr_s;
            pspin = (bool *)malloc(sizeof(bool));
            *pspin = false;
            break;
        }
        clock_gettime(CLOCK_MONOTONIC, &time_begin);
        for (int i = 0; i < threadnum; ++i)
            pthread_create(threads + i, NULL, func_thread, params + i);
        for (int i = 0; i < threadnum; ++i)
            pthread_join(threads[i], NULL);
        clock_gettime(CLOCK_MONOTONIC, &time_end);

        if (SortedList_length(list))
            exit(2);

        unsigned long long total_nanosec = time_end.tv_sec - time_begin.tv_sec;
        total_nanosec *= 1000000000;
        total_nanosec += (time_end.tv_nsec - time_begin.tv_nsec);
        unsigned long long avg_nanosec = total_nanosec;
        avg_nanosec /= threadnum;
        avg_nanosec /= iterationnum;
        char *yielddesc[8] = {"-none", "-i", "-d", "-id", "-l", "-il", "-dl", "-idl"};
        char *syncdesc[4] = {"-none", "-m", "-s", "-c"};
        fprintf(csv, "list%s%s,%i,%i,1,%i,%llu,%llu\n",
                yielddesc[opt_yield], syncdesc[opt_sync], threadnum, iterationnum, threadnum * iterationnum * 3, total_nanosec, avg_nanosec);
    }
    free(pspin);
    free(keys);
    free(eles);
    free(params);
    free(list);
    free(threads);
    free(access_allow);
    fclose(csv);
    return 0;
}