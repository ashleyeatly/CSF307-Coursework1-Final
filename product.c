//
// Created by Ashley Eatly on 21/05/2023.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include "product.h"

void clear_products(product_t *pProd,unsigned int num_items) {
    for (int i = 0; i< num_items; i++) {
        clear_product(&pProd[i]);
    }
}

void clear_product(product_t *pProd) {
    if (!pProd) {
        if (!(pProd->pProduct_name)) {
            free(pProd->pProduct_name);
        }
        free(pProd);
    }
}

product_t *load_products(char* pFilename, unsigned int* pNum_items) {
    FILE *in_file= NULL;
    int number_lines = 0;
    int count = 0;
    product_t *pProducts_org = NULL;

    in_file  = fopen(pFilename, "r"); // read only

    if (in_file == NULL) {
        printf("Error! Could not open file %s\n",pFilename);
        fclose(in_file);
        exit(1); // must include stdlib.h
    }
    if (in_file) {

        fscanf(in_file, "%u\n",&number_lines);

        product_t *pProducts= (product_t*)malloc( number_lines * sizeof(product_t) );

        if ( pProducts == NULL ) {
            fprintf(stderr, "Error - unable to allocate required memory\n");
            return pProducts;
        }
        pProducts_org = pProducts;
        while(!feof(in_file) && number_lines--) {
            count++;
            char product_name[1000];
            fscanf(in_file, "%u %d %f %f %s\n", &pProducts->product_code, &pProducts->stock_quantity, &pProducts->unit_price,
                   &pProducts->discount_percentage, product_name);
            pProducts->pProduct_name = (char*) malloc(sizeof(char)*(strlen(product_name)+1));
            strcpy(pProducts->pProduct_name,product_name);
            pProducts++;
        }
    }
    fclose(in_file);
    *pNum_items = count;
    return pProducts_org;
}

void pretty_print(product_t *pProducts, unsigned int num_items) {

    for (int i=0; i<num_items; i++) {
        printf("%-10u %-6u %-9.2f %-3d %s \n",pProducts[i].product_code, pProducts[i].stock_quantity, pProducts[i].unit_price,
               (int)round((double)(pProducts[i].discount_percentage)*100.0) , pProducts[i].pProduct_name);
    }
}

double calculate_score(product_t prod){
    double score = (sqrt((double)prod.unit_price) * (double)((double)prod.discount_percentage)/100.0)/(double)(prod.stock_quantity);
    return score;
}

product_t *best_product(product_t *pProducts, unsigned int num_items,double * pScore) {
    double best_score = 0.0;
    unsigned int best_item = 0;
    for (int i = 0; i < num_items; i++) {
        double current_score = calculate_score(pProducts[i]);
        if (current_score >= best_score) {
            best_score = current_score;
            best_item = i;
        }
    }
    *pScore = best_score;
    return &pProducts[best_item];
}