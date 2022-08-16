#include "htrie.h"
#include "pqueue.h"
#include "bit_buffer.h"


// Internal function for the priority queue. If the return value is > 0
// elem1 is larger, and if return value < 0 then elem2 is larger.
int compareFunc(void *elem1, void *elem2) {
    return ((node *)elem1)->weight - ((node *)elem2)->weight;
}

node *createNode(int val, int weight) {

    node *n = calloc(1, sizeof(node));
    n->val = val;
    n->weight = weight;
    n->left_child = NULL;
    n->right_child = NULL;

    return n;
}

bool isLeaf(node *n) {
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