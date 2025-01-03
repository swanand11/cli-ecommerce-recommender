#include "Recommender.h"
#include<stdio.h>
#define MAX_CART_SIZE 10

struct OrderListItem{
    struct Product product; 
    int quantity;
    struct OrderListItem* next;
};
// struct OrderListItem* head=NULL;

struct OrderList {
    struct OrderListItem *cart[MAX_CART_SIZE];
};

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

void insert(OrderList *hashTable, const Product *key) {
    unsigned int index = hash(key);
    Product *newNode = createNode(key);

    if (!hashTable->cart[index]) {
        hashTable->cart[index] = newNode;
    } 
    else {
        OrderListItem *current = hashTable->cart[index];
        while (current) {
            if (comparePID(&current->product->pid, key->pid)) {
                // Update the value if the key already exists
                current->quantity++;
                free(newNode);
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode; // Add the new node to the chain
    }
}

int get(struct OrderList *hashTable, struct Product *key) {
    unsigned int index = hash(key);
    struct OrderList *current = hashTable->cart[index];
    while (current != NULL) {
        if (strcmp(current->product, key) == 0) {
            return current->quantity;
        }
        current = current->next;
    }
    return -1; // Key not found
}

void addItem(struct OrderListItem *item){
    if(get(cart,item) == -1){
        insert(item);
    }
    else
        item->quantity++;
}
void removeItem(struct OrderListItem *item){
    if(item->quantity == 1){
        printf("Removed from cart");
        item->quantity = 0;
    }
    if(item->quantity == 0){
        printf("Item not in cart");
    }
    // TO CART CLI
}

// DO CLI 
// Multiply quantity*price, display only if quantity>0
void display(){
    
}

