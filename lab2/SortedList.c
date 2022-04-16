#include "SortedList.h"
#include <string.h>
#include <sched.h>
#include <stdlib.h>
int opt_yield = 0;
void nulfunc() {}
void (*func_lockw)() = nulfunc;
void (*func_unlockw)() = nulfunc;
void (*func_lockr)() = nulfunc;
void (*func_unlockr)() = nulfunc;
void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
    func_lockw();
    if (opt_yield & INSERT_YIELD)
        sched_yield();
    SortedListElement_t *iterator = list->next;
    while (1)
    {
        if (iterator->key && strcmp(iterator->key, element->key) < 0)
            iterator = iterator->next;
        else
        {
            if (opt_yield & INSERT_YIELD)
                sched_yield();
            element->prev = iterator->prev;
            element->next = iterator;
            iterator->prev->next = element;
            iterator->prev = element;
            func_unlockw();
            return;
        }
    }
}
int SortedList_delete(SortedListElement_t *element)
{
    func_lockw();
    if (opt_yield & DELETE_YIELD)
        sched_yield();
    element->prev->next = element->next;
    element->next->prev = element->prev;
    func_unlockw();
    return 0;
}
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
    func_lockr();
    if (opt_yield & LOOKUP_YIELD)
        sched_yield();
    SortedListElement_t *iterator = list->next;
    while (1)
    {
        int cmp = iterator->key ? strcmp(iterator->key, key) : 1;
        if (cmp < 0)
            iterator = iterator->next;
        else if (cmp > 0)
        {
            func_unlockr();
            exit(2);
        }
        else
        {
            func_unlockr();
            return iterator;
        }
    }
}
int SortedList_length(SortedList_t *list)
{
    func_lockr();
    if (opt_yield & LOOKUP_YIELD)
        sched_yield();
    int len = 0;
    SortedListElement_t *iterator = list->next;
    SortedListElement_t *end = list;
    while (iterator != end)
    {
        ++len;
        iterator = iterator->next;
    }
    func_unlockr();
    return len;
}