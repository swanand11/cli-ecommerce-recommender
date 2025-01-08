#include "shared.h"

void mainMenu() {
    int choice;
    do {
        printf("\nMain Menu:\n");
        printf("1) Search Product\n");
        printf("2) Cart\n");
        printf("3) Wishlist\n");
        printf("4) Placed Orders\n");
        printf("5) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char pid[20];
                printf("Enter Product ID to search: ");
                scanf("%s", pid);
                recommend_products(pid);
                printf("\nWould you like to add this product to cart? (Y/N): ");
                char add;
                scanf(" %c", &add);
                if (add == 'Y' || add == 'y') {
                    Product* product = NULL;
                    for (int i = 0; i < MAX_PRODUCTS; i++) {
                        if (strcmp(products[i].pid, pid) == 0) {
                            product = &products[i];
                            break;
                        }
                    }
                    if (product) {
                        addToCart(product);
                    }
                }
                break;
            }
            case 2:
                cartMenu();
                break;
            case 3:
                wishlistMenu();
                break;
            case 4:
                placedOrdersMenu();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void cartMenu() {
    int choice;
    do {
        printf("\nCart Menu:\n");
        printf("1) View Cart\n");
        printf("2) Remove From Cart\n");
        printf("3) Place Order\n");
        printf("4) Add to Wishlist\n");
        printf("5) Placed Orders\n");
        printf("6) Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCart();
                break;
            case 2: {
                char pid[20];
                printf("Enter Product ID to remove: ");
                scanf("%s", pid);
                Product* product = NULL;
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (strcmp(products[i].pid, pid) == 0) {
                        product = &products[i];
                        break;
                    }
                }
                if (product) {
                    removeFromCart(product);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 3:
                placeOrder();
                break;
            case 4: {
                char pid[20];
                printf("Enter Product ID to add to wishlist: ");
                scanf("%s", pid);
                Product* product = NULL;
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (strcmp(products[i].pid, pid) == 0) {
                        product = &products[i];
                        break;
                    }
                }
                if (product) {
                    addToWishlist(product);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 5:
                placedOrdersMenu();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void wishlistMenu() {
    int choice;
    do {
        printf("\nWishlist Menu:\n");
        printf("1) View Wishlist\n");
        printf("2) Remove from Wishlist\n");
        printf("3) Add to Cart\n");
        printf("4) Go to Cart\n");
        printf("5) Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayWishlist();
                break;
            case 2: {
                char pid[20];
                printf("Enter Product ID to remove: ");
                scanf("%s", pid);
                Product* product = NULL;
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (strcmp(products[i].pid, pid) == 0) {
                        product = &products[i];
                        break;
                    }
                }
                if (product) {
                    removeFromWishlist(product);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 3: {
                char pid[20];
                printf("Enter Product ID to add to cart: ");
                scanf("%s", pid);
                Product* product = NULL;
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (strcmp(products[i].pid, pid) == 0) {
                        product = &products[i];
                        break;
                    }
                }
                if (product) {
                    moveToCart(product);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 4:
                cartMenu();
                return;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void placedOrdersMenu() {
    printf("Placed Orders:\n");
    // Implement the logic to display placed orders
}

