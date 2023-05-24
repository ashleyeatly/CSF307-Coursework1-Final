//
// Created by Ashley Eatly on 05/05/2023.
//

#ifndef COURSEWORK1_PRODUCT_H
#define COURSEWORK1_PRODUCT_H

/**
 *  unsigned int could be 2 or 4 bytes 0 - 65535 or 0 - 4,292.967,295
 *  unsigned long would be 0 - 4,292.967,295
 *
 */

/**
 * This struct contains the product details
 *     char *pProduct_name;         // is a pointer to a a char array that contains the unbounded product
 *                                  // name string
 *     unsigned int product_code;  //  code is range 100_000_000 to 999_999_999
 *                                  // unsigned long would be 0 - 4,292.967,295
 *                                  // note the table in  lecture 01 also has unigned int as 0 - 4,292.967,295
 *     unsigned int stock_quantity; //  quantity is in range 0 to 500_000
 *     float unit_price;            //  price_per_unit is in range 0.01 and 10_000.00
 *                                  //  we can store variable as a float but maybe use double for calculations
 *     float discount_percentage;   // in  the file it is as a float e.g 0.055 0.12
 *     // discount can only be in theory 0 - 100%  but usigned char would be unable to account for
 *     // 10.05% 10.5%
 */


typedef struct product {
    char *pProduct_name;
    unsigned int    product_code;
    unsigned int    stock_quantity;
    float   unit_price;
    float   discount_percentage;
} product_t;

product_t *load_products(char *pFilename, unsigned int *pNum_items);
double calculate_score(product_t prod);
void pretty_print(product_t *pProducts, unsigned int num_items);
void clear_products(product_t *pProd, unsigned int num_items);
void clear_product(product_t *pProd);
product_t *best_product(product_t *pProducts, unsigned int num_items,double * pScore);
#endif //COURSEWORK1_PRODUCT_H
