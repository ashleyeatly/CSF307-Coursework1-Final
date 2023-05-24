//
// Created by Ashley Eatly on 15/05/2023.
//
#include "trie.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>

/* Allocate a new empty trie.  */
trie_t *new_trie(void) {
    trie_t *pNode = NULL;

    pNode = (trie_t *)malloc(sizeof (trie_t));

    if (pNode) {
        for (int i=0; i < TRIE_CHILDREN; i++) {
            // make sure all the child trie nodes are pointing to NULL
            pNode->pChildrenTries[i] = NULL;
        }
        // and make sure that each pProduct is also pointing to NULL
        pNode->pProduct = NULL;
    }
    return pNode;
}


// Insert a single prouct pointer in the trie chain
void insert_product(trie_t *pRootTrie,product_t *pProduct) {
    trie_t *pCurrentTrie = pRootTrie;

    char buffer[100];
    sprintf(buffer,"%u\n",pProduct->product_code);
    unsigned int code_length = strlen(buffer);
    // ensure the index is available outside of the loop
    int index;
    for (int level = 0; level< code_length; level++) {
        index = buffer[level] - '0';

        trie_t *pNextTrie = pCurrentTrie->pChildrenTries[index];
        if (!(pCurrentTrie->pChildrenTries[index])) {   // its NULL
            // create  new trie to use
            pCurrentTrie->pChildrenTries[index] = new_trie();
        }
        pCurrentTrie = pCurrentTrie->pChildrenTries[index];
    }
    // Finally use the current trie to store pointer to the product
    pCurrentTrie ->pProduct = pProduct;
}

product_t *get_product(trie_t *pRootTrie, unsigned int product_code){
    trie_t *pCurrentTrie = pRootTrie;
    trie_t *pNextTrie = NULL;

    char buffer[100];
    sprintf(buffer,"%u\n",product_code);

    unsigned int code_length = strlen(buffer);
    for (int level = 0; level< code_length; level++) {
        int index = buffer[level] - '0';

        pNextTrie = pCurrentTrie->pChildrenTries[index];
        if (!(pCurrentTrie->pChildrenTries[index])) {
            return NULL;
        }
        pCurrentTrie = pNextTrie;
    }
    return pCurrentTrie->pProduct;
}

// Remove the trie from memory

void free_trie(trie_t *pTrie) {
    // move across all the possible children in each trie
    // but we need to go down the tree to delete the leaf node and move back up the nodes
    if (!pTrie) {
        return;
    }
    // move across all children
    for (int level = 0; level < TRIE_CHILDREN; level++) {
        if (pTrie->pChildrenTries[level]) {
            free_trie(pTrie->pChildrenTries[level]);
        }
    }
    // base case
    free(pTrie);
}

bool has_children(trie_t* pNode) {
    if (!pNode) {
        return false;
    }
    for (int i=0 ; i< TRIE_CHILDREN; i++) {
        if (pNode->pChildrenTries[i]) {
            return true;
        }
    }
    return false;
}
