#ifndef HTRIE_H
#define HTRIE_H

#include "list.h"
#include "pqueue.h"
#include "bit_buffer.h"
#include "freqtable.h"

typedef struct Node {
    int val;
    int weight;
    struct node *left_child;
    struct node *right_child;
} node;


node *createNode(int val, int weight);

node *pqToTrie(pqueue *pq);

bool isLeaf(node *n);

void killTrie(node *trie);

#endif