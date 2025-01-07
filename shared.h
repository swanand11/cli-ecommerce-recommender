#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_CART_SIZE 10
#define MAX_WL_SIZE 20
#define HASHMAP_SIZE 1009
#define MAX_PRODUCTS 20000

typedef struct Product {
    char pid[20];
    char name[200];
    float price;
    char category[100];
    float rating;
} Product;

typedef struct ListNode {
    Product product;
    int quantity;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* items[20];
    int max_size;
} List;

typedef struct HashNode {
    char key[20];
    Product value;
    struct HashNode* next;
} HashNode;

typedef struct HashMap {
    HashNode* table[HASHMAP_SIZE];
} HashMap;

// Function declarations
void init_hashmap(HashMap* hashmap);
void load_products(const char* filename, HashMap* hashmap);
Product* search(HashMap* hashmap, const char* key);
void recommend_products(const char* product_id, HashMap* hashmap);
void initCart(void);
void addToCart(const Product* prod);
void initWishlist(void);
void addToWishlist(const Product* prod);
void freeList(List* list);

extern List* Cart;
extern List* WL;

#endif