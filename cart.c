#include "shared.h"
List* Cart=NULL;


void addToCart(const Product* prod) {
    if (!Cart) Cart = initList();
    
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
//add a function movetoWishList

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
                current = NULL;
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
    if (!Cart || !Cart->items) {
        printf("Cart is Empty\n");
        return;
    }
    
    float total = 0.0;
    printf("\nCart Contents:\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        ListNode* current = Cart->items[i];
        while (current) {
            float itemTotal = current->quantity * current->product.price;
            total += itemTotal;
            printf("Product ID: %s\nName: %s\nQuantity: %d\nPrice per item: %.2f\nTotal: %.2f\n\n",
                   current->product.pid, current->product.name,
                   current->quantity, current->product.price, itemTotal);
            current = current->next;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("Cart Total: %.2f\n", total);
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
        for (int i = 0; i < 10; i++) {
            Cart->items[i] = NULL;
        }
        //freeList(Cart);
    }
}
//THE FOLLOWING CODE ISN'T EXECUTING PROPERLY
void moveToWishlist(const Product* prod) {
    if(!Cart) return;
    addToWishlist(prod);
    removeFromCart(prod);
    printf("Do you wish to view Wishlist? (Y/N)\n");
    char c;
    scanf(" %c", &c);
    if (c == 'Y' || c == 'y') {
        displayWishlist();
    }
}
