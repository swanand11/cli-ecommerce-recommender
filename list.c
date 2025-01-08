#include "shared.h"
List* initList() {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        perror("Failed to allocate memory for list");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 10; i++) {
        list->items[i] = NULL;
    }
    return list;
}
ListNode* createNode(Product product, int quantity) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->product = product;
    node->quantity = quantity;
    node->next = NULL;
    return node;
}

unsigned int hashItem(const Product* product, int size) {
    unsigned int hash = 0;
    const char* str = product->pid;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash % size;
}

void freeList(List* list) {
    if (!list) return;
    
    for (int i = 0; i < 10; i++) {
        ListNode* current = list->items[i];
        while (current) {
            ListNode* temp = current;
            current = current->next;
            free(temp);
            temp=NULL;
        }
        list->items[i]=NULL;
    }
    free(list);
    list=NULL;
}