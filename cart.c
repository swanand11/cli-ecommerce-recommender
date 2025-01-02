#include "Recommender.h"
#include<stdio.h>

struct OrderList{
    struct Product product; 
    int quantity;
};

void addItem(struct OrderList *item){
    item->quantity++;
}
void removeItem(struct OrderList *item){
    if(item->quantity == 1){
        printf("Removed from cart");
        item->quantity = 0;
    }
    if(item->quantity == 0){
        printf("Item not in cart");
    }
    // TO CART CLI
}

// DO CLI 
// Multiply quantity*price, display only if quantity>0
void display(){
    
}

