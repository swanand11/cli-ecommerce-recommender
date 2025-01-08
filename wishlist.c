#include "shared.h"

List* WL = NULL;

void addToWishlist(const Product* prod) {
    if (!WL) WL = initList();
    
    unsigned int index = hashItem(prod, MAX_WL_SIZE);
    ListNode* current = WL->items[index];
    
    while (current) {
        if (strcmp(current->product.pid, prod->pid) == 0) {
            printf("Product already in wishlist\n");
            return;
        }
        current = current->next;
    }
    
    ListNode* newNode = createNode(*prod, 1);
    newNode->next = WL->items[index];
    WL->items[index] = newNode;
    printf("Added %s to wishlist\n", prod->pid);
}

void removeFromWishlist(const Product* prod) {
    if (!WL) return;
    
    unsigned int index = hashItem(prod, MAX_WL_SIZE);
    ListNode* current = WL->items[index];
    ListNode* prev = NULL;
    
    while (current) {
        if (strcmp(current->product.pid, prod->pid) == 0) {
            if (prev) prev->next = current->next;
            else WL->items[index] = current->next;
            free(current);
            printf("Removed %s from wishlist\n", prod->pid);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product not found in wishlist\n");
}

void moveToCart(const Product* prod) {
    if (!WL) return;
    addToCart(prod);
    removeFromWishlist(prod);
}

void displayWishlist() {
    if (!WL) {
        printf("Wishlist is Empty\n");
        return;
    }
    
    printf("Wishlist Contents:\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        ListNode* current = WL->items[i];
        while (current) {
            printf("Product ID: %s, Name: %s, Price: %.2f\n",
                   current->product.pid, current->product.name, current->product.price);
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
}