#include "shared.h"

List* Cart = NULL;

void addToCart(const Product* prod) {
    if (!Cart) Cart = initList(MAX_CART_SIZE);
    
    unsigned int index = hashItem(prod, MAX_CART_SIZE);
    ListNode* current = Cart->items[index];
    
    while (current) {
        if (strcmp(current->product.pid, prod->pid) == 0) {
            current->quantity++;
            printf("Added 1 quantity of %s to cart\n", prod->pid);
            return;
        }
        current = current->next;
    }
    
    ListNode* newNode = createNode(*prod, 1);
    newNode->next = Cart->items[index];
    Cart->items[index] = newNode;
    printf("Added %s to cart\n", prod->pid);
}

void removeFromCart(const Product* prod) {
    if (!Cart) return;
    
    unsigned int index = hashItem(prod, MAX_CART_SIZE);
    ListNode* current = Cart->items[index];
    ListNode* prev = NULL;
    
    while (current) {
        if (strcmp(current->product.pid, prod->pid) == 0) {
            if (current->quantity > 1) {
                current->quantity--;
                printf("Removed 1 quantity of %s from cart\n", prod->pid);
            } else {
                if (prev) prev->next = current->next;
                else Cart->items[index] = current->next;
                free(current);
                printf("Removed %s from cart\n", prod->pid);
            }
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product not found in cart\n");
}

void displayCart() {
    if (!Cart) {
        printf("Cart is Empty\n");
        return;
    }
    
    printf("Cart Contents:\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < Cart->max_size; i++) {
        ListNode* current = Cart->items[i];
        while (current) {
            printf("Product ID: %s, Name: %s, Quantity: %d, Total Price: %.2f\n",
                   current->product.pid, current->product.name,
                   current->quantity, current->quantity * current->product.price);
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
}

void placeOrder() {
    if (!Cart || !Cart->items) {
        printf("Cart is Empty\n");
        return;
    }
    
    printf("Confirm Order? (Y/N)\n");
    char c;
    scanf(" %c", &c);
    
    if (c == 'Y' || c == 'y') {
        save_order(Cart);
        printf("Order Placed Successfully\n");
        freeList(Cart);
        Cart = initList(MAX_CART_SIZE);
    }
}