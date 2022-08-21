#include <stdlib.h>

#include "htrie.h"
#include "pqueue.h"
#include "bit_buffer.h"


node *createNode(char val, int prio) {

    node *n = malloc(sizeof(node));
    n->val = val;
    n->prio = prio;
    n->left_child = NULL;
    n->right_child = NULL;

    return n;
}

node *pqToTrie(pqueue *pq) {

    while (!pqueue_is_empty(pq)) {
        node *first = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);
        if (pqueue_is_empty(pq)) {
            return first;
        }

        node *second = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);

        int totalPrio = first->prio + second->prio;
        node *trie = createNode(-1, totalPrio);
        trie->left_child = first;
        trie->right_child = second;
        pqueue_insert(pq, trie);
    }

    // If pqueue is empty from the start, then return node with no prio
    node *empty_trie = createNode(0, 0);
    return empty_trie;
}

bool leafNode(node *n) {

    if (n->left_child == NULL && n->right_child == NULL) {
        return true;
    }
    return false;
}

void killTrie(node *trie) {
    
    if (!leafNode(trie)) {
        killTrie(trie->left_child);
        killTrie(trie->right_child);
    }
    free(trie);
}