#include "recommender.h"
#include "cart.h"

#define MAX_WL_SIZE 20

struct WishListItem{
    struct Product product; 
    struct WishListItem* next;
};

struct Wishlist {
    struct WishListItem *wishlist[MAX_WL_SIZE];
}WL;

unsigned int hashWL(const struct Product *key) {
    unsigned int hash = 0;
    const char* ID = key->pid;
    while (*ID) {
        hash = (hash * 31) + *ID++; // Simple hash function
    }
    hash+= key->ID;
    return hash % MAX_WL_SIZE;
}

struct WishList *initWishList() {
    WishList *hashTable = (WishList *)malloc(sizeof(WishList));
    if (!hashTable) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_CART_SIZE; i++) {
        hashTable->wishlist[i] = NULL;
    }
    return hashTable;
}

WL=initWishList();

struct WishListItem *createWLNode(const struct Product prod){
    WishListItem *item= (*WishListItem)malloc(sizeof(WishListItem));
    if (!item) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    item->product= prod;
    item->next=NULL;
    return item;
}

int comparePIDWL(const WishListItem *key1, const WishListItem *key2) {
    return strcmp(key1->product->pid, key2->product->pid) == 0;
}

void addToWishlist(const Product *key) {
    unsigned int index = hashWL(key);
    struct WishListItem *newNode = createWLNode(key);

    if (!WL->wishlist[index]) {
        WL->wishlist[index] = newNode;
        printf("Added %s to wishlist", key->pid);
        return;
    } 
    else {
        WishListItem *current = WL->wishlist[index];
        while (current) {
            if (comparePIDWL(&current->product->pid, key->pid)) {
                printf("Product already in wishlist");
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode; // Add the new node to the chain
        printf("Added %s to wishlist", key->pid);
    }
}

void removeFromWishlist(const Product *key) {
    unsigned int index = hashWL(key);
    struct WishListItem *current = WL->wishlist[index];
    struct WishListItem *prev = NULL;

    while (current) {
        if (comparePIDWL(&current->product->pid, key->pid)) {
            if (prev) {
                prev->next = current->next;
            } else {
                WL->wishlist[index] = current->next;
            }
            free(current);
            printf("Removed %s from wishlist", key->pid);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product not found in wishlist");
}

moveToCart(const Product *key){
    addToCart(key);
    removeFromWishlist(key);
}

void displayWishlist() {
    if(WL==NULL){
        printf("Wishlist is Empty\n");
        return;
    }
    printf("Wishlist Contents:\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_WL_SIZE; i++) {
        struct WishListItem *current = WL->wishlist[i];
        while (current != NULL) {
            printf("Product ID: %s, Name: %s, Price: %.2f\n", 
                   current->product.pid, current->product.name, current->product.price);
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
}  