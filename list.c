#include "shared.h"

List* initList(int size) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        perror("Failed to allocate memory for list");
        exit(EXIT_FAILURE);
    }
    
    list->items = (ListNode**)calloc(size, sizeof(ListNode*));
    if (!list->items) {
        free(list);
        perror("Failed to allocate memory for items");
        exit(EXIT_FAILURE);
    }
    
    list->max_size = size;
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
    
    for (int i = 0; i < list->max_size; i++) {
        ListNode* current = list->items[i];
        while (current) {
            ListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(list->items);
    free(list);
}