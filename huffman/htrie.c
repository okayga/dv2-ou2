
#include <stdio.h>
#include <stdlib.h>

#include "htrie.h"
#include "pqueue.h"
#include "bit_buffer.h"

node *pqToTrie(pqueue *pq) {

    while (pqueue_is_empty(pq) == false) {
        node *first_node = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);

        // If pqueue is empty, the first node is the largest. Return it
        if (pqueue_is_empty(pq)) {
            return first_node;
        }
        node *second_node = pqueue_inspect_first(pq);
        pqueue_delete_first(pq);
        
        node *trie;
        trie = calloc(1, sizeof(node));
        trie->prio = first_node->prio+second_node->prio;
        // All parent nodes (non-leaf nodes) are given #
        trie->val = -1;
        trie->left_child = first_node;
        trie->right_child = second_node;
        pqueue_insert(pq, trie);
    }

        // If pqueue is empty from the start then return an empty node
    
      node *trie;
      trie = calloc(1, sizeof(node));
      trie->prio = 0;
      trie->val = -1;
      return trie;
}

bool leafNode(node *n) {

    if ( n->val >= 0 &&  n->val <= 255) {
        if (n->left_child == NULL && n->right_child == NULL) {
          return true;
        }
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

void printTrie(node *trie, int level) {

    printf("Node on level %d has prio %d and value %d\n", level, trie->prio,
    (int)trie->val);

    if (trie->left_child != NULL) {
      printTrie(trie->left_child, level+1);
    }
    if (trie->right_child != NULL) {
      printTrie(trie->right_child, level+1);
    }
}
