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
        node *node = createNode(-1, totalPrio);
        trienode->left_child = first;
        trienode->right_child = second;
        pqueue_insert(pq, trienode);
    }
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