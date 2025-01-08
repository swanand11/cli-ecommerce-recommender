#include "shared.h"
int main() {
    Cart = NULL;
    WL = NULL;
    load_products("data.csv");
    mainMenu();
    if (Cart) freeList(Cart);
    if (WL) freeList(WL);
    return 0;
}