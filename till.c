//
// Created by Ashley Eatly on 16/05/2023.
//

#include "product.h"
#include "trie.h"
#include "till.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <sys/stat.h>
#include <unistd.h>
#define SINGLE_PARTITION printf("==============================================================================\n");
#define DOUBLE_PARTITION printf("==============================================================================\n\n");



int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("please enter the name amd path of the file you want to run\n");
        exit(1);
    }
    char *pFilename = argv[1];
    printf(" %s %s \n", argv[1],pFilename);

    if (!file_exists(pFilename)) {
        printf(" Please enter the name of the file on command line to run\n");
        exit(1);
    }

    //  Task1
    task1();
    //  Task2
    task2();
    //  Task3
    task3();
    //  Task4
    task4();

    //  Task3 and 5
    unsigned int num_items;
    product_t* pProducts = task3and5(pFilename, &num_items);


    task4after3(pProducts, num_items);

    task6(pProducts, num_items);

    // clear all products stored in memory
    printf("=========================================================================\n");
    printf("Cleaning up removing all products\n");
    printf("=========================================================================\n\n");
    clear_products(pProducts, num_items);
    printf("=========================================================================\n");
    printf("Cleaning up removing all products complete\n");
    printf("=========================================================================\n\n");

    return EXIT_SUCCESS;


}

bool file_exists(const char *filename)
{
    return (bool)access(filename, F_OK) == 0;
}

void task1(void) {
    // Coursework 1 Task 1
    // See product.h
    printf("=========================================================================\n");
    printf("Task 1 is to define the product struct\n");
    printf("this can be achieved by examining the struct and its typedef in product.h\n");
    printf("=========================================================================\n\n");
}

void task2(void){
    // Coursework 1 Task 2 - Superceded by Task 5
    // See load_products in product.c
    printf("=========================================================================\n");
    printf("Task 2 has been supeceeded by Task 5 and Task 5 will be earlier in order\n");
    printf("=========================================================================\n\n");
}

void task3(void) {
    // Coursework 1 Task 3 Printing Products comes after Task 5 now
    // See pretty_print in product.c
    printf("=========================================================================\n");
    printf("Task 3 will be illustrated after examples of Task 5\n");
    printf("=========================================================================\n\n");

}

void task4(void) {
    // Coursework 1 Task 4 Comes after Task 5 now
    // See float calculate_score(product_t *pProd, unsigned long *product_code); etc. in product.c
    printf("=========================================================================\n");
    printf("Task 4 has been supeceeded by Task 5\n");
    printf("=========================================================================\n\n");

}

product_t* task3and5(char* pFilename, unsigned int* num_items) {
    // Coursework 1 Task 5 - Improved file reader

    // The method returns the number of lines (items) in the file as a passback value.
    // as well as returnoing a pointer to the products 'collection' allocated in memory
    // this can either point to an array of products - may even by one
    // otherwise it returns NULL

    printf("=========================================================================\n");
    printf("Task 5 replaces Task2\n");
    printf("This includes Task3 to prove reading of products from file\n");
    printf("=========================================================================\n\n");

    product_t *pProducts = load_products(pFilename, num_items);
    if (pProducts) {
        printf("=========================================================================\n");
        printf(" File %s contains %d Items (products) \n",pFilename, *num_items);
        printf("=========================================================================\n\n");
        printf("The columns are:\n");
        printf("1: Product Code - stored as an unsigned int (size max 9 characters)\n");
        printf("   Range 100_000_000 to 999_999_999\n");
        printf("2: Stock Quantity - stored as an unsigned int (size max 6 characters)\n");
        printf("   Range 0 to 500_000\n");
        printf("3: Price Per Unit - stored as a float (size max 8 characters  inc 2 decimal places)\n");
        printf("   Range 0.01 to 10_000.00\n");
        printf("4: discount - as percentage stored as an unsigned int  (size max 3 characters)\n");
        printf("   Range 0 to 100\n");
        printf("5: product name - stored as a string\n");
        printf("   no size\n");
        printf("=========================================================================\n\n");
        if (*num_items > 20) {
            printf(" We will print a maximum of 20 products from start of file for illustration\n");
            printf("===========================================================================\n\n");
            pretty_print(pProducts, 20);
        } else {
            pretty_print(pProducts, *num_items);
        }
        printf("=========================================================================\n\n");
    }
    return pProducts;
}

// Coursework 1 Task 4
// finding the best product to buy based on an arbitrary formulae

void task4after3(product_t* pProducts,unsigned int num_items) {
    double pScore = 0.0;
    product_t *pValuableProduct = best_product(pProducts, num_items, &pScore);
    printf("=========================================================================\n");
    printf("The best score is %3.3f \n", pScore);
    printf("=========================================================================\n");
    printf("For Item:\n");
    pretty_print(pValuableProduct, 1);
    printf("=========================================================================\n\n");
}

void task6(product_t* pProducts, unsigned int num_items) {
    // Coureswork 1 - Task 6
    // The Trie structure is in trie.h and trie.c
    printf("=========================================================================\n");
    printf("Task 6 regarding Trie and various experiments\n");
    printf("Part one preparing the structure - examine trie.h and trie.c\n");
    printf("=========================================================================\n\n");

    // We need a Root Trie everything goes from here.
    trie_t *pRootTrie = new_trie();

    printf("=========================================================================\n");
    printf("Examining the trie.h and sizes stored in memory\n");
    printf("=========================================================================\n\n");
    printf("=========================================================================\n");
    printf("freeing the trie\n");
    printf("inserting all products into trie after creating a new trie root\n");
    printf("=========================================================================\n\n");

    for (int i = 0; i < num_items; i++) {
        insert_product(pRootTrie, &pProducts[i]);
    }

    printf("=========================================================================\n");
    printf("finding maximum 10 products in the trie\n");
    printf("these are the first 10 known products from collection (they will all be found of course)\n");
    printf("this is the first 10 items being searched in the trie\n");
    printf("=========================================================================\n\n");

    unsigned long product_code;

    product_t *pProduct;
    for (int i = 0; i < 10; i++) {
        product_code = pProducts[i].product_code;
        printf("searching for %lu\n", product_code);
        pProduct = get_product(pRootTrie, product_code);
        printf("found for %lu\n", product_code);
        pretty_print(pProduct, 1);
        printf("=========================================================================\n\n");
    }
    printf("=========================================================================\n");
    printf("Now looking for random product codes that may or may  ot exist\n");
    printf("=========================================================================\n\n");

    product_code = 123456789;
    printf("searching for %lu (it should not exist) \n", product_code);
    printf("=========================================================================\n");

    pProduct = get_product(pRootTrie, product_code);
    if (pProduct == NULL) {
        printf("%lu couldnt be found\n", product_code);
    } else {
        printf("%lu was found \n", product_code);
        pretty_print(pProduct, 1);
    }
    printf("=========================================================================\n\n");

    product_code = 2207647522;
    printf("searching for %lu (it should not exist) \n", product_code);

    pProduct = get_product(pRootTrie, product_code);
    if (!pProduct) {
        printf("%lu couldnt be found\n", product_code);
    } else {
        printf("%lu was found \n", product_code);
        pretty_print(pProduct, 1);
    }
    printf("=========================================================================\n\n");

    printf("=========================================================================\n");
    printf("Task to dispose of trie responsibly\n");
    printf("Do not attempt to access the root trie after this as it is likely to have\n");
    printf("unspecified behaviour\n");
    printf("=========================================================================\n\n");

    // Task Part 4 - Disposing of trie responsibly
    // note this is not removing the products from memory this should be done afterwards
    // when all is cleared

    free_trie(pRootTrie);
    pRootTrie = NULL;
    printf("Trie has been disposed and the pointer set to NULL %p\n", pRootTrie);
    printf("=========================================================================\n");

}