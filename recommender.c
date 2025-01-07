#include "shared.h"

#define MAX_ORDERS 50
#define MIN_RATING 2.0

typedef struct {
    Product* product;
    float score;
} Recommendation;

static Product products[MAX_PRODUCTS];
static int product_count = 0;
static List* orders = NULL;

static void trim(char* str) {
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

void load_products(const char* filename) {
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

        product_count++;
    }
    fclose(file);
}

static int compare_recommendations(const void* a, const void* b) {
    return ((Recommendation*)b)->score - ((Recommendation*)a)->score;
}

static float calculate_order_based_score(const char* product_name) {
    if (!orders) return 0;
    
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

static float calculate_recommendation_score(Product* product) {
    float order_score = calculate_order_based_score(product->name);
    float rating_score = product->rating / 5.0;
    float price_factor = product->price > 0 ? 1000.0 / (1000.0 + product->price) : 1.0;
    
    return (0.4 * rating_score) + (0.4 * order_score) + (0.2 * price_factor);
}

void recommend_products(const char* product_id) {
    Product* current_product = NULL;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].pid, product_id) == 0) {
            current_product = &products[i];
            break;
        }
    }

    if (!current_product) {
        printf("Product not found.\n");
        return;
    }

    Recommendation recommendations[MAX_PRODUCTS];
    int rec_count = 0;

    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].pid, current_product->pid) != 0 &&
            strcmp(products[i].category, current_product->category) == 0) {
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
    
    if (!orders) orders = initList(MAX_ORDERS);
    
    for (int i = 0; i < cart->max_size; i++) {
        ListNode* current = cart->items[i];
        while (current) {
            ListNode* newNode = createNode(current->product, current->quantity);
            unsigned int index = hashItem(&current->product, MAX_ORDERS);
            
            newNode->next = orders->items[index];
            orders->items[index] = newNode;
            current = current->next;
        }
    }
}