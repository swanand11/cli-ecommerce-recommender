#include "cli.c"

int main() {
    load_products("data.csv");
    mainMenu();
    /*load_products("data.csv");

    Product test_product1 = {
        .pid = "PID1",
        .name = "Test Product 1",
        .price = 100.0,
        .category = "Electronics",
        .rating = 4.5
    };

    Product test_product2 = {
        .pid = "PID2",
        .name = "Test Product 2",
        .price = 150.0,
        .category = "Electronics",
        .rating = 4.0
    };

    printf("\nTesting Cart:\n");
    addToCart(&test_product1);
    addToCart(&test_product1);
    addToCart(&test_product2);
    displayCart();

    printf("\nTesting Wishlist:\n");
    addToWishlist(&test_product2);
    displayWishlist();

    printf("\nTesting Recommendations:\n");
    recommend_products("PID3");

    if (Cart) freeList(Cart);
    if (WL) freeList(WL);
    */
    
    return 0;
}