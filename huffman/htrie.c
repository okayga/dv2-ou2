#include <stdlib.h>

#include "htrie.h"
#include "pqueue.h"
#include "bit_buffer.h"

node *pqToTrie(pqueue *pq) {
    while (!pqueue_is_empty(pq)) {
        node *first_node = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);
        if (pqueue_is_empty(pq)) {
            return first_node;
        }

        node *second_node = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);

        node *trie = malloc(1*sizeof(node));
        trie->prio = (first_node->prio) + (second_node->prio);
        // All parent nodes (non-leaf nodes) are given -1
        trie->val = -1;
        trie->left_child = first_node;
        trie->right_child = second_node;
        pqueue_insert(pq, trie);
    }

    // If pqueue is empty from the start then return an empty node
    node *emptyTrie = malloc(1*sizeof(node));
    emptyTrie->prio = 0;
    emptyTrie->val = -1;
    
    return emptyTrie;
}

bool leafNode(node *n) {

    if (n->left_child == NULL && n->right_child == NULL) {
        return true;
    }
    return false;
}

void killTrie(node *trie) {
    
    if (leafNode(trie) == false) {
        killTrie(trie->left_child);
        killTrie(trie->right_child);
    }
    free(trie);
}