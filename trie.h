//
// Created by Ashley Eatly on 15/05/2023.
//
#ifndef CLIONPROJECTS_PRODUCT_H
#include "product.h"
#endif

#ifndef CLIONPROJECTS_TRIE_H
#define CLIONPROJECTS_TRIE_H
/**
 * The trie has a pointer to a product (it can be null)
 * The trie has children - which in this implementation is actually 10
 * could have been defined as trie_t children[10] or trie_t *children and
 * the 10 are allocated when a trie is created
 * 0,1,2,3,4,5,6,7,8,9
 * I know many have flags to state its a tree node but is this necessary
 */
#define TRIE_CHILDREN 10
#include <stdbool.h>

typedef struct  trie_node {
    struct trie_node *pChildrenTries[TRIE_CHILDREN];
    product_t  *pProduct;
} trie_t;

// Create an initialise a new trie structure and return a pointer to this trie
trie_t *new_trie(void);

// Insert the product based on product code in trie chain
void insert_product(trie_t *pRootTrie, product_t *pProduct);

// This is linked to the product in the trie will return NULL if not exists
product_t *get_product(trie_t *pRootTrie, unsigned int product_code);

// delete whole trie from memory
void free_trie(trie_t *trie);

// TODO We may want to delete a certain key from trie
//

#endif //CLIONPROJECTS_TRIE_H
