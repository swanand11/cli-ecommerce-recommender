#include "Recommender.h"
#include "wishlist.h"
#include<stdio.h>
#define MAX_CART_SIZE 10

struct OrderListItem{
    struct Product product; 
    int quantity;
    struct OrderListItem* next;
};

struct OrderList {
    struct OrderListItem *cart[MAX_CART_SIZE];
}Cart;

unsigned int hash(const struct Product *key) {
    unsigned int hash = 0;
    const char* ID = key->pid;
    while (*ID) {
        hash = (hash * 31) + *ID++; // Simple hash function
    }
    hash+= key->ID;
    return hash % MAX_CART_SIZE;
}

struct OrderList *initCart() {
    OrderList *hashTable = (OrderList *)malloc(sizeof(OrderList));
    if (!hashTable) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_CART_SIZE; i++) {
        hashTable->cart[i] = NULL;
    }
    return hashTable;
}

Cart=initCart();

struct OrderListItem *createNode(const struct Product prod){
    OrderListItem *item= (*OrderListItem)malloc(sizeof(OrderListItem));
    if (!item) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    item->product= prod;
    item->quantity=0;
    item->next=NULL;
    return item;
}

int comparePID(const OrderListItem *key1, const OrderListItem *key2) {
    return strcmp(key1->product->pid, key2->product->pid) == 0;
}

void addToCart(const Product *key) {
    unsigned int index = hash(key);
    struct OrderListItem *newNode = createNode(key);

    if (!Cart->cart[index]) {
        Cart->cart[index] = newNode;
    } 
    else {
        OrderListItem *current = Cart->cart[index];
        while (current) {
            if (comparePID(&current->product->pid, key->pid)) {
                // Update the value if the key already exists
                current->quantity++;
                free(newNode);
                printf("Added 1 quantity of %s to cart", key->pid);
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode; // Add the new node to the chain
        printf("Added %s to cart", key->pid);
    }
}

void removeFromCart(struct Product *key){
    unsigned int index = hash(key);
    struct OrderListItem *current = Cart->cart[index];
    struct OrderListItem *prev = NULL;
    while (current != NULL) {
        if (comparePID(&current->product->pid, key->pid) && current->quantity==1) {
            if (prev) {
                prev->next = current->next;
            } else {
                Cart->cart[index] = current->next;
            }
            free(current);
            printf("Deleted %s from cart\n", key->pid);
            return;
        }
        else if(comparePID(&current->product->pid, key->pid)) {
            current->quantity--;
            printf("Removed 1 quantity of %s from cart", key->pid);
            return; 
        }
        prev = current;
        current = current->next;
    }
    printf("Product not found in cart");
}

int get(struct Product *key) {
    unsigned int index = hash(key);
    struct OrderList *current = Cart->cart[index];
    while (current != NULL) {
        if (strcmp(current->product, key) == 0) {
            return current->quantity;
        }
        current = current->next;
    }
    return -1; // Key not found
}

void moveToWishlist(struct OrderListItem *item){
    addToWishlist(item->product);
    item->quantity=1;
    removeFromCart(item->product);
    // TO WISHLIST CLI
}

void displayCart() {
    if(Cart==NULL){
        printf("Cart is Empty\n");
        return;
    }
    printf("Cart Contents:\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_CART_SIZE; i++) {
        struct OrderListItem *current = Cart->cart[i];
        while (current != NULL) {
            if (current->quantity > 0) {
                printf("Product ID: %s, Name: %s, Quantity: %d, Total Price: %.2f\n", 
                       current->product.pid, current->quantity, 
                       current->quantity * current->product.price);
            }
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
}  

void freeCart() {
    for (int i = 0; i < MAX_CART_SIZE; i++) {
        struct OrderListItem *current = Cart->cart[i];
        while (current != NULL) {
            struct OrderListItem *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(Cart);
}

void PlaceOrder(){
    if(Cart==NULL){
        printf("Cart is Empty\n");
        return;
    }
    printf("Confirm Order? (Y/N)\n");
    char c;
    scanf("%c",&c);
    if(c=='N' || c=='n'){
        return;
    }
    else{
        for (int i = 0; i < MAX_CART_SIZE; i++) {
            struct OrderListItem *current = Cart->cart[i];
            while (current != NULL) {
                if (current->quantity > 0) {
                    save_order(current->product, current->quantity);
                }
                current = current->next;
            }
        }
        printf("Order Placed Successfully\n");
        freeCart();
        Cart=initCart();
    }
}

