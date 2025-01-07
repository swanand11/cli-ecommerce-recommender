#include "shared.h"

#define MAX_WL_SIZE 20

List* WL = NULL;

void initWishlist() {
    WL = initList(MAX_WL_SIZE);
}

void addToWishlist(const Product* prod) {
    unsigned int index = hashItem(prod, MAX_WL_SIZE);
    ListNode* newNode = createNode(*prod, 1);

    if (!WL->items[index]) {
        WL->items[index] = newNode;
    } else {
        ListNode* current = WL->items[index];
        while (current) {
            if (strcmp(current->product.pid, prod->pid) == 0) {
                free(newNode);
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode;
    }
}