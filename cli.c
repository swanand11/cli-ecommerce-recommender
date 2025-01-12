#include "shared.h"

void mainMenu() {
    int choice;
    do {
        printf("\n==============================\n");
        printf("          Main Menu           \n");
        printf("==============================\n");
        printf("1) Search Product\n");
        printf("2) Cart\n");
        printf("3) Wishlist\n");
        printf("4) Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char pid[20];
                printf("Enter Product ID to search: ");
                scanf("%s", pid);
                recommend_products(pid);
                char option;
                printf("\n1. Add this product to cart? \n");
                printf("2. Add this product to wishlist? \n");
                printf("3. Go back to main menu? \n");
                printf("Enter your choice: ");
                scanf(" %c", &option);
                switch(option){
                    case '1':{
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
                    case '2':{
                            Product* product = NULL;
                            for (int i = 0; i < MAX_PRODUCTS; i++) {
                                if (strcmp(products[i].pid, pid) == 0) {
                                    product = &products[i];
                                    break;
                                }
                            }
                            if (product) {
                                addToWishlist(product);
                            }
                        }
                        break;
                    case '3':
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            }
            case 2:{
                cartMenu();
                break;
            }
            case 3:{
                wishlistMenu();
                break;
            }
            case 4:{
                printf("Exiting...\n");
                exit(1);
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void cartMenu() {
    int choice;
    do {
        printf("\n==============================\n");
        printf("          Cart Menu           \n");
        printf("==============================\n");
        printf("1) View Cart\n");
        printf("2) Remove From Cart\n");
        printf("3) Move to Wishlist\n");
        printf("4) Place Order\n");
        printf("5) Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCart();
                break;
            case 2: {
                displayCart();
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
            case 3: {
                displayCart();
                char pid[20];
                printf("Enter Product ID to move to wishlist: ");
                scanf("%s", pid);
                Product* product = NULL;
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (strcmp(products[i].pid, pid) == 0) {
                        product = &products[i];
                        break;
                    }
                }
                if (product) {
                    moveToWishlist(product);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 4:{
                placeOrder();
                break;
            } 
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void wishlistMenu() {
    int choice;
    do {
        printf("\n==============================\n");
        printf("        Wishlist Menu         \n");
        printf("==============================\n");
        printf("1) View Wishlist\n");
        printf("2) Remove from Wishlist\n");
        printf("3) Move to Cart\n");
        printf("4) Go to Cart\n");
        printf("5) Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayWishlist();
                break;
            case 2: {
                displayWishlist();
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
                displayWishlist();
                char pid[20];
                printf("Enter Product ID to move to cart: ");
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
            case 4:{
                cartMenu();
                break;
            }
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}