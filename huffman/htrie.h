#ifndef HTRIE_H
#define HTRIE_H

#include "list.h"
#include "pqueue.h"
#include "bit_buffer.h"
#include "freqtable.h"

typedef struct Node {
    char val;
    int prio;
    node *left_child;
    node *right_child;
} node;

node *createNode(int val, int prio);

node *pqToTrie(pqueue *pq);

bool isLeaf(node *n);

void killTrie(node *trie);

#endif