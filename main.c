#include "shared.h"

int main() {
    HashMap hashmap;
    init_hashmap(&hashmap);
    load_products("data.csv", &hashmap);

    initCart();
    initWishlist();

    Product* p1 = search(&hashmap, "PID1");
    Product* p2 = search(&hashmap, "PID2");
    
    if (p1 && p2) {
        printf("\nTesting Cart:\n");
        addToCart(p1);
        addToCart(p1);
        addToCart(p2);
        
        printf("\nCart Contents:\n");
        for (int i = 0; i < Cart->max_size; i++) {
            ListNode* current = Cart->items[i];
            while (current) {
                printf("PID: %s, Name: %s, Quantity: %d\n", 
                    current->product.pid,
                    current->product.name,
                    current->quantity);
                current = current->next;
            }
        }

        printf("\nTesting Wishlist:\n");
        addToWishlist(p2);
        
        printf("\nWishlist Contents:\n");
        for (int i = 0; i < WL->max_size; i++) {
            ListNode* current = WL->items[i];
            while (current) {
                printf("PID: %s, Name: %s\n", 
                    current->product.pid,
                    current->product.name);
                current = current->next;
            }
        }

        printf("\nTesting Recommendations:\n");
        recommend_products("PID1", &hashmap);
    }

    freeList(Cart);
    freeList(WL);
    return 0;
}