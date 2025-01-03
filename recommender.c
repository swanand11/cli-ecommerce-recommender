#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_PRODUCTS 1000
#define MAX_NAME_LENGTH 200
#define MAX_CATEGORY_LENGTH 100
#define MAX_ORDERS 50
#define MAX_ORDER_LENGTH 10
#define MIN_RATING 2.0
#define HASHMAP_SIZE 1009  
typedef struct {
    char pid[20];
    char name[MAX_NAME_LENGTH];
    float price;
    char category[MAX_CATEGORY_LENGTH];
    float rating;
    float rec_probability;
} Product;

typedef struct HashNode {
    char key[20];  
    Product value;
    struct HashNode* next;
} HashNode;

// Structure for HashMap
typedef struct {
    HashNode* table[HASHMAP_SIZE];
} HashMap;

// Structure to store order information
typedef struct {
    char product_names[MAX_ORDER_LENGTH][MAX_NAME_LENGTH];
    int item_count;
} Order;

// Global variables
Product products[MAX_PRODUCTS];
int product_count = 0;
Order orders[MAX_ORDERS];
int order_count = 0;

// Function to trim whitespace
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

unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key++;
    }
    return hash_value % HASHMAP_SIZE;
}

// Function to initialize hashmap
void init_hashmap(HashMap* hashmap) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        hashmap->table[i] = NULL;
    }
}

// Function to insert product into the hashmap
void insert(HashMap* hashmap, const char* key, Product* value) {
    unsigned int index = hash(key);
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(new_node->key, key);
    new_node->value = *value;
    new_node->next = hashmap->table[index];
    hashmap->table[index] = new_node;
}

// Function to search for a product by its PID in the hashmap
Product* search(HashMap* hashmap, const char* key) {
    unsigned int index = hash(key);
    HashNode* current = hashmap->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return &current->value;
        }
        current = current->next;
    }
    return NULL;  
}

// Function to load products from CSV and insert them into hashmap
void load_products(const char* filename, HashMap* hashmap) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file) && product_count < MAX_PRODUCTS) {
        Product* p = &products[product_count];

        // Parse PID
        char* token = strtok(line, ",");
        if (token) strncpy(p->pid, token, sizeof(p->pid) - 1);

        // Parse name
        token = strtok(NULL, ",");
        if (token) {
            strncpy(p->name, token, sizeof(p->name) - 1);
            trim(p->name);
        }

        // Parse price
        token = strtok(NULL, ",");
        if (token) p->price = atof(token);

        // Parse category
        token = strtok(NULL, ",");
        if (token) strncpy(p->category, token, sizeof(p->category) - 1);

        // Parse rating
        token = strtok(NULL, ",");
        if (token) p->rating = atof(token);

        p->rec_probability = 0.5; // Default value

        insert(hashmap, p->pid, p);  // Insert product into hashmap

        product_count++;
    }
    fclose(file);
    printf("Loaded %d products successfully.\n", product_count);
}

// Function to search products using hashmap
void search_products(const char* query, HashMap* hashmap) {
    printf("\nSearch results for '%s':\n", query);
    printf("%-10s %-50s %-10s %-20s %-7s\n", "PID", "Name", "Price", "Category", "Rating");
    printf("--------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        Product* p = &products[i];
        if (strstr(p->name, query) || strstr(p->category, query)) {
            printf("%-10s %-50s ₹%-9.2f %-20s %.1f\n", p->pid, p->name, p->price, p->category, p->rating);
            found++;
        }
    }

    if (!found) {
        printf("No products found matching '%s'\n", query);
    }
}

// Function to calculate recommendation score based on order history
float calculate_order_based_score(const char* product_name) {
    int appearance_count = 0;

    for (int i = 0; i < order_count; i++) {
        for (int j = 0; j < orders[i].item_count; j++) {
            if (strcmp(orders[i].product_names[j], product_name) == 0) {
                appearance_count++;
                break;
            }
        }
    }

    return (float)appearance_count / order_count;
}

// Function to calculate recommendation score
float calculate_recommendation_score(Product* product) {
    float order_score = calculate_order_based_score(product->name);
    return (0.4 * product->rating / 5.0 +
            0.4 * order_score +
            0.2 * (product->price < 1000 ? 0.8 : 0.6));
}

// Function to recommend products based on the category and hashmap
void recommend_products(const char* product_id, HashMap* hashmap) {
    Product* current_product = search(hashmap, product_id);

    if (!current_product) {
        printf("Product ID not found.\n");
        return;
    }

    printf("\nRecommendations based on: %s - %s\n", current_product->pid, current_product->name);
    printf("\nTop 5 Recommended Products:\n");
    printf("%-10s %-50s %-10s %-7s\n", "PID", "Name", "Price", "Rating");
    printf("--------------------------------------------------------------------------------\n");

    // Create recommendations based on the category
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].pid, current_product->pid) != 0 &&
            strstr(products[i].category, current_product->category)) {
            printf("%-10s %-50s ₹%-9.2f %.1f\n", products[i].pid, products[i].name, products[i].price, products[i].rating);
        }
    }
}

// Function to view order history
void view_order_history() {
    if (order_count == 0) {
        printf("\nNo orders found.\n");
        return;
    }

    printf("\nOrder History (Most Recent First):\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = order_count - 1; i >= 0; i--) {
        printf("Order %d:\n", order_count - i);
        for (int j = 0; j < orders[i].item_count; j++) {
            printf("  %d. %s\n", j + 1, orders[i].product_names[j]);
        }
        printf("--------------------------------------------------------------------------------\n");
    }
}

// Function to save new order
void save_order(char **product_names, int count) {
    if (count <= 0) return;

    // First, verify all products exist
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < product_count; j++) {
            if (strcmp(products[j].name, product_names[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Product not found: %s\n", product_names[i]);
            return;
        }
    }

    // Add to orders array
    if (order_count >= MAX_ORDERS) {
        // Remove oldest order
        for (int i = 0; i < MAX_ORDERS - 1; i++) {
            orders[i] = orders[i + 1];
        }
        order_count--;
    }

    Order *new_order = &orders[order_count];
    new_order->item_count = 0;

    for (int i = 0; i < count && i < MAX_ORDER_LENGTH; i++) {
        strcpy(new_order->product_names[i], product_names[i]);
        new_order->item_count++;
    }

    order_count++;
    printf("Order placed successfully!\n");
}

// Function to display the main menu
void display_menu() {
    printf("\n-----------------------------\n");
    printf("Product Recommendation System\n");
    printf("-----------------------------\n");
    printf("1. Search products\n");
    printf("2. Get product recommendations\n");
    printf("3. View order history\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
}

// Main function
int main() {
    HashMap hashmap;
    init_hashmap(&hashmap);

    load_products("data.csv", &hashmap);  // Load products and insert into hashmap

    char choice;
    char search_query[MAX_NAME_LENGTH];
    char product_id[20];

    do {
        display_menu();
        scanf(" %c", &choice);
        getchar(); 

        switch (choice) {
            case '1':
                printf("\nEnter Product ID (e.g., PID1): ");
                fgets(product_id, sizeof(product_id), stdin);
                product_id[strcspn(product_id, "\n")] = 0;
                recommend_products(product_id, &hashmap);
                break;

            case '3':
                view_order_history();
                break;

            case '4':
                printf("\nThank you for using the Product Recommendation System!\n");
                break;

            default:
                printf("\nInvalid option. Please try again.\n");
        }
    } while (choice != '4');

    return 0;
}
