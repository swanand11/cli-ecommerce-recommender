#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
#define MAX_PRODUCTS 20000
#define MAX_LINE_LENGTH 8192

struct Product {
    char pid[MAX_STRING_LENGTH];
    char product_name[MAX_STRING_LENGTH];
    float retail_price;
    char simplified_categories[MAX_STRING_LENGTH];
    float rating;
};

void trim(char *str) {
    if (str == NULL) return;
    
    char *start = str;
    char *end = str + strlen(str) - 1;
    
    while(*start == ' ' || *start == '"') start++;
    while(end > start && (*end == ' ' || *end == '"' || *end == '\n')) end--;
    
    *(end + 1) = '\0';
    
    if(start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

// Function to read products from CSV file
int read_products(const char* filename, struct Product* products, int max_products) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'.\n", filename);
        return -1;
    }

    int product_count = 0;
    char line[MAX_LINE_LENGTH];
    char line_copy[MAX_LINE_LENGTH];
    char *token;

    // Skip header line
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: File is empty or cannot read header line.\n");
        fclose(file);
        return -1;
    }

    // Read data lines
    while (fgets(line, sizeof(line), file) && product_count < max_products) {
        // Check if line was too long and got truncated
        if (line[strlen(line) - 1] != '\n' && !feof(file)) {
            printf("Warning: Line %d is too long and may be truncated\n", product_count + 2);
            // Clear the rest of the line
            int ch;
            while ((ch = fgetc(file)) != EOF && ch != '\n');
        }
        
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';
        
        // PID
        token = strtok(line_copy, ",");
        if (token == NULL) {
            printf("Error: Invalid format in line %d - missing PID\n", product_count + 2);
            continue;
        }
        trim(token);
        strncpy(products[product_count].pid, token, MAX_STRING_LENGTH - 1);
        products[product_count].pid[MAX_STRING_LENGTH - 1] = '\0';
        
        // Product name
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Error: Invalid format in line %d - missing product name\n", product_count + 2);
            continue;
        }
        trim(token);
        strncpy(products[product_count].product_name, token, MAX_STRING_LENGTH - 1);
        products[product_count].product_name[MAX_STRING_LENGTH - 1] = '\0';
        
        // Retail price
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Error: Invalid format in line %d - missing retail price\n", product_count + 2);
            continue;
        }
        products[product_count].retail_price = atof(token);
        
        // Categories
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Error: Invalid format in line %d - missing categories\n", product_count + 2);
            continue;
        }
        trim(token);
        strncpy(products[product_count].simplified_categories, token, MAX_STRING_LENGTH - 1);
        products[product_count].simplified_categories[MAX_STRING_LENGTH - 1] = '\0';
        
        // Rating
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Error: Invalid format in line %d - missing rating\n", product_count + 2);
            continue;
        }
        products[product_count].rating = atof(token);
        
        product_count++;
    }

    fclose(file);
    return product_count;
}

int main() {
    struct Product *products = malloc(MAX_PRODUCTS * sizeof(struct Product));
    if (products == NULL) {
        printf("Error: Unable to allocate memory for products.\n");
        return 1;
    }

    int product_count = read_products("data.csv", products, MAX_PRODUCTS);
    
    if (product_count <= 0) {
        printf("Error: No valid products were read from the file.\n");
        free(products);
        return 1;
    }

    // Print the first few products to verify data
    printf("First %d products loaded:\n", (product_count < 3 ? product_count : 3));
    for (int i = 0; i < (product_count < 3 ? product_count : 3); i++) {
        printf("\nProduct %d:\n", i + 1);
        printf("PID: %s\n", products[i].pid);
        printf("Name: %s\n", products[i].product_name);
        printf("Price: %.2f\n", products[i].retail_price);
        printf("Category: %s\n", products[i].simplified_categories);
        printf("Rating: %.1f\n", products[i].rating);
    }

    printf("\nTotal products loaded: %d\n", product_count);

    free(products);
    return 0;
}
