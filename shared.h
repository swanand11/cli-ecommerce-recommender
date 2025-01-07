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
    ListNode** items;
    int max_size;
} List;

// Function declarations
List* initList(int size);
ListNode* createNode(Product product, int quantity);
unsigned int hashItem(const Product* product, int size);
void freeList(List* list);

// Cart functions
void addToCart(const Product* prod);
void removeFromCart(const Product* prod);
void displayCart(void);
void placeOrder(void);

// Wishlist functions
void addToWishlist(const Product* prod);
void removeFromWishlist(const Product* prod);
void displayWishlist(void);
void moveToCart(const Product* prod);

// Recommender functions
void load_products(const char* filename);
void recommend_products(const char* product_id);
void save_order(List* cart);

extern List* Cart;
extern List* WL;

#endif