#include "htrie.h"
#include "pqueue.h"
#include "bit_buffer.h"


// Internal function for the priority queue. If the return value is > 0
// elem1 is larger, and if return value < 0 then elem2 is larger.
int lessThan(void *elem1, void *elem2) {
    return ((node *)elem1)->prio - ((node *)elem2)->prio;
}

node *createNode(char val, int prio) {

    node *n = calloc(1, sizeof(node));
    n->val = val;
    n->prio = prio;
    n->left_child = NULL;
    n->right_child = NULL;

    return n;
}

pqueue *freqtableToPq (freqtable *ft) {
    pqueue *pq = pqueue_empty(lessThan);
    node *e = malloc(sizeof(node));

    for (int i = 0; i < 256; i++) {
        e->val = ft[i].symbol;
        e->prio = ft[i].freq;
        pqueue_insert(pq, e);
    }

    return pq;
}

node *pqToTrie(pqueue *pq) {



    return trie;
}

bool leafNode(node *n) {
    if (n->left_child == NULL && n->right_child == NULL) {
        return true;
    }
    return false;
}

void killTrie(node *trie) {
    if (!isLeaf(trie)) {
        killTrie(trie->left_child);
        killTrie(trie->right_child);
    }
    free(trie);
}