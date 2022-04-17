#include "SortedList.h"
#include <string.h>
#include <sched.h>
#include <stdlib.h>
int opt_yield = 0;
void nulfunc(u_int64_t a) {}
void (*func_lockw)(u_int64_t) = nulfunc;
void (*func_unlockw)(u_int64_t) = nulfunc;
void (*func_lockr)(u_int64_t) = nulfunc;
void (*func_unlockr)(u_int64_t) = nulfunc;
u_int64_t hash64(const char *key)
{
    u_int64_t ans = 0;
    for (int i = strlen(key) - 1; i >= 0; --i)
    {
        ans *= 131;
        ans += key[i];
    }
    return ans;
}
void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
    func_lockw((u_int64_t)list->key);
    if (opt_yield & INSERT_YIELD)
        sched_yield();
    SortedListElement_t *iterator = list->next;
    while (1)
    {
        if (iterator != list && strcmp(iterator->key, element->key) < 0)
            iterator = iterator->next;
        else
        {
            if (opt_yield & INSERT_YIELD)
                sched_yield();
            element->prev = iterator->prev;
            element->next = iterator;
            iterator->prev->next = element;
            iterator->prev = element;
            func_unlockw((u_int64_t)list->key);
            return;
        }
    }
}
int SortedList_delete(SortedListElement_t *element)
{
    u_int64_t hash = hash64(element->key);
    func_lockw(hash);
    if (opt_yield & DELETE_YIELD)
        sched_yield();
    element->prev->next = element->next;
    element->next->prev = element->prev;
    func_unlockw(hash);
    return 0;
}
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
    func_lockr((u_int64_t)list->key);
    if (opt_yield & LOOKUP_YIELD)
        sched_yield();
    SortedListElement_t *iterator = list->next;
    while (1)
    {
        int cmp = iterator != list ? strcmp(iterator->key, key) : 1;
        if (cmp < 0)
            iterator = iterator->next;
        else if (cmp > 0)
        {
            func_unlockr((u_int64_t)list->key);
            exit(2);
        }
        else
        {
            func_unlockr((u_int64_t)list->key);
            return iterator;
        }
    }
}
int SortedList_length(SortedList_t *list)
{
    func_lockr((u_int64_t)list->key);
    if (opt_yield & LOOKUP_YIELD)
        sched_yield();
    int len = 0;
    SortedListElement_t *iterator = list->next;
    while (iterator != list)
    {
        ++len;
        iterator = iterator->next;
    }
    func_unlockr((u_int64_t)list->key);
    return len;
}