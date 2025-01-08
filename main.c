#include "shared.h"
int main() {
    Cart = NULL;
    WL = NULL;
    load_products("data.csv");
    mainMenu();
     if (Cart){
     freeList(Cart);
     Cart=NULL;
     }
     if (WL){ 
        freeList(WL);
        WL=NULL;
     }
    return 0;
}