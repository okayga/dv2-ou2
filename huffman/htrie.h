#ifndef HTRIE_H
#define HTRIE_H

#include "list.h"
#include "pqueue.h"
#include "bit_buffer.h"

typedef struct node {
    char val;
    int prio;
    struct node *left_child;
    struct node *right_child;
} node;

node *createNode(char val, int prio);

node *pqToTrie(pqueue *pq);

bool leafNode(node *n);

void killTrie(node *trie);

#endif