#include "shared.h"
#include <math.h>
#include <ctype.h>
#include <float.h>

#define MAX_PRODUCTS 20000
#define MAX_ORDERS 50
#define MIN_RATING 2.0

typedef struct {
    Product* product;
    float score;
} Recommendation;

// typedef struct HashNode {
//     char key[20];
//     Product value;
//     struct HashNode* next;
// } HashNode;

// typedef struct {
//     HashNode* table[1009];
// } HashMap;

Product products[MAX_PRODUCTS];
int product_count = 0;
List* orders;

void trim(char* str) {
    char* start = str;
    while (isspace(*start)) start++;
    if (*start == 0) {
        *str = 0;
        return;
    }
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;
    *(end + 1) = 0;
    if (start != str)
        memmove(str, start, strlen(start) + 1);
}

void init_hashmap(HashMap* hashmap) {
    for (int i = 0; i < 1009; i++) {
        hashmap->table[i] = NULL;
    }
}

void insert(HashMap* hashmap, const char* key, Product* value) {
    unsigned int index = hashItem(value, 1009);
    HashNode* new_node = malloc(sizeof(HashNode));
    strcpy(new_node->key, key);
    new_node->value = *value;
    new_node->next = hashmap->table[index];
    hashmap->table[index] = new_node;
}

Product* search(HashMap* hashmap, const char* key) {
    unsigned int index = hashItem(&(Product){.pid = key}, 1009);
    HashNode* current = hashmap->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) return &current->value;
        current = current->next;
    }
    return NULL;
}

void load_products(const char* filename, HashMap* hashmap) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file) && product_count < MAX_PRODUCTS) {
        Product* p = &products[product_count];
        
        char* token = strtok(line, ",");
        if (token) strncpy(p->pid, token, sizeof(p->pid) - 1);
        
        token = strtok(NULL, ",");
        if (token) {
            strncpy(p->name, token, sizeof(p->name) - 1);
            trim(p->name);
        }
        
        token = strtok(NULL, ",");
        if (token) p->price = atof(token);
        
        token = strtok(NULL, ",");
        if (token) strncpy(p->category, token, sizeof(p->category) - 1);
        
        token = strtok(NULL, ",");
        if (token) p->rating = atof(token);

        insert(hashmap, p->pid, p);
        product_count++;
    }
    fclose(file);
}

int compare_recommendations(const void* a, const void* b) {
    return ((Recommendation*)b)->score - ((Recommendation*)a)->score;
}

float calculate_order_based_score(const char* product_name) {
    int appearances = 0;
    int total_orders = 0;
    
    for (int i = 0; i < orders->max_size; i++) {
        ListNode* current = orders->items[i];
        while (current) {
            if (strcmp(current->product.name, product_name) == 0) appearances++;
            total_orders++;
            current = current->next;
        }
    }
    
    return total_orders > 0 ? (float)appearances / total_orders : 0;
}

float calculate_recommendation_score(Product* product) {
    float order_score = calculate_order_based_score(product->name);
    float rating_score = product->rating / 5.0;
    float price_factor = product->price > 0 ? 1000.0 / (1000.0 + product->price) : 1.0;
    
    return (0.4 * rating_score) + (0.4 * order_score) + (0.2 * price_factor);
}

void recommend_products(const char* product_id, HashMap* hashmap) {
    Product* current_product = search(hashmap, product_id);
    if (!current_product) {
        printf("Product not found.\n");
        return;
    }

    Recommendation recommendations[MAX_PRODUCTS];
    int rec_count = 0;

    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].pid, current_product->pid) != 0 &&
            strstr(products[i].category, current_product->category)) {
            recommendations[rec_count].product = &products[i];
            recommendations[rec_count].score = calculate_recommendation_score(&products[i]);
            rec_count++;
        }
    }

    qsort(recommendations, rec_count, sizeof(Recommendation), compare_recommendations);

    printf("\nTop 5 Recommendations for %s:\n", current_product->name);
    printf("%-10s %-50s %-10s %-7s\n", "PID", "Name", "Price", "Rating");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < (rec_count < 5 ? rec_count : 5); i++) {
        Product* p = recommendations[i].product;
        printf("%-10s %-50s ₹%-9.2f %.1f\n", p->pid, p->name, p->price, p->rating);
    }
}

void save_order(List* cart) {
    if (!cart) return;
    
    orders = initList(MAX_ORDERS);
    for (int i = 0; i < cart->max_size; i++) {
        ListNode* current = cart->items[i];
        while (current) {
            ListNode* newNode = createNode(current->product, current->quantity);
            unsigned int index = hashItem(&current->product, MAX_ORDERS);
            
            if (!orders->items[index]) {
                orders->items[index] = newNode;
            } else {
                newNode->next = orders->items[index];
                orders->items[index] = newNode;
            }
            current = current->next;
        }
    }
}