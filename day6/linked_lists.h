#ifndef LL_ALT_H
#define LL_ALT_H

#include "common.h"
#include <assert.h>

typedef int DATA;
typedef struct node {
    DATA data;
    int next, prev;
} NODE;
typedef struct {
    int head, tail, free;
    unsigned int length, capacity;
    NODE *elements;
} LIST;

int init_list(LIST *l, int n);
int insert(LIST *l, unsigned int index, DATA d);
int delete(LIST *l, unsigned int index, DATA *d);
int find_index_of(LIST *l, DATA d);
int find_value_at(LIST *l, unsigned int index, DATA *d);
void print_list(LIST *l);
void print_list_reverse(LIST *l);
void free_list(LIST *l);
int insert_at_end(LIST *l, DATA d);
int delete_at_end(LIST *l, DATA *d);

#endif /* LL_ALT_H */
