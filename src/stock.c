#include "../include/stock.h"

void initializeTable(List table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = NULL;
    }
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertInputs(List table[]) {
    Inputs newInput;
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Error allocating memory...\n");
        free(newNode);
        return;
    }

    printf("Enter barcode: ");
    while (scanf("%d", &newInput.barcode) != 1) {
        printf("Error! Please, enter an integer value for the barcode.\n:");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    if (search(table, newInput.barcode) != NULL) {
        printf("Error: A product with this barcode already exists!\n");
        free(newNode);
        return;
    }

    printf("Enter product name: ");
    fgets(newInput.productName, 50, stdin);
    newInput.productName[strcspn(newInput.productName, "\n")] = '\0';

    printf("Enter amount: ");
    while (scanf("%d", &newInput.amount) != 1) {
        printf("Error! Please, enter an integer value for the amount.\n:");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    newNode->input = newInput;
    newNode->next = NULL;

    int id = hashFunction(newInput.barcode);

    newNode->next = table[id];
    table[id] = newNode;

    printFileTxt(table);
    printf("Input inserted successfully!\n");
}

Node* search(List table[], int key) {
    int id = hashFunction(key);
    Node* current = table[id];

    while (current != NULL) {
        if (current->input.barcode == key) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

void printInputs(List table[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("Hash: %d\n", i);
        if (table[i] != NULL) {
            Node* current = table[i];
            while (current != NULL) {
                printf("    Barcode: %d\n", current->input.barcode);
                printf("    Product: %s\n", current->input.productName);
                printf("    Amount: %d\n", current->input.amount);
                current = current->next;
                if (current != NULL) {
                    printf(" - - - - - - - - - - - - - - - - - - - - \n");
                }
            }
        } else {
            printf("NULL\n");
        }
        printf("----------------------------------------\n");
    }
}

void printFileTxt(List table[]) {
    FILE* file = fopen("bankStock.txt", "w");
    if (file == NULL) {
        printf("Error when creating/opening file!\n");
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        if (table[i] != NULL) {
            Node* current = table[i];
            while (current != NULL) {
                fprintf(file, "%d\n", current->input.barcode);
                fprintf(file, "%s\n", current->input.productName);
                fprintf(file, "%d\n", current->input.amount);
                current = current->next;
            }
        }
    }

    fclose(file);
    printf("Data successfully written to bankStock.txt!\n");
}

List* loadFromFile(List table[]) {
    FILE* file = fopen("bankStock.txt", "r");
    if (file == NULL) {
        printf("File not found. Initializing table with NULL values...\n");
        initializeTable(table);
        return table;
    }

    initializeTable(table);

    int barcode, amount;
    char productName[50];

    while (fscanf(file, "%d\n", &barcode) != EOF) {
        if (fgets(productName, sizeof(productName), file) != NULL) {
            productName[strcspn(productName, "\n")] = '\0';
        } else {
            printf("Error reading product name from file.\n");
            continue;
        }

        fscanf(file, "%d\n", &amount);

        Inputs newInput;
        Node* newNode = (Node*)malloc(sizeof(Node));

        if (newNode == NULL) {
            printf("Error allocating memory...\n");
            free(newNode);
            fclose(file);
            return table;
        }

        newInput.barcode = barcode;
        strcpy(newInput.productName, productName);
        newInput.amount = amount;

        newNode->input = newInput;
        newNode->next = NULL;

        int id = hashFunction(newInput.barcode);

        newNode->next = table[id];
        table[id] = newNode;
    }

    fclose(file);
    printf("Data successfully loaded from bankStock.txt!\n");

    return table;
}

DecrementResult* decrement(List table[], int* totalDecremented) {
    char input[50];
    int key, quantity;
    Node* foundItem;
    DecrementResult* results = malloc(10 * sizeof(DecrementResult));
    *totalDecremented = 0;

    while (1) {
        printf("Registered products:\n");
        printInputs(table);

        while (1) {
            printf("Enter the barcode of the input you want (or press Enter to select): ");
            fgets(input, sizeof(input), stdin);

            if (input[0] == '\n') {
                printf("Please enter an input and press enter.\n");
                continue;
            }

            if (sscanf(input, "%d", &key) != 1) {
                printf("Error! Please, enter an integer value in this field.\n");
            } else {
                foundItem = search(table, key);
                if (foundItem == NULL) {
                    printf("Product not found. Please, enter a valid barcode.\n");
                } else {
                    break; 
                }
            }
        }

        
        printf("Enter the quantity you want: ");
        while (scanf("%d", &quantity) != 1) {
            printf("Error! Please, enter an integer value in this field.\n:");
            while (getchar() != '\n');  
        }
        while (getchar() != '\n');  

        if (foundItem->input.amount >= quantity) {
            foundItem->input.amount -= quantity;

            strcpy(results[*totalDecremented].name, foundItem->input.productName);
            results[*totalDecremented].quantity = quantity;
            (*totalDecremented)++; 

            printFileTxt(table);
            printf("Decrement successful. New amount: %d\n", foundItem->input.amount);
        } else {
            printf("Error: Not enough quantity to decrement.\n");
        }

        break;
    }

    return results;
}

void increment(List table[]) {
    int key, quantity;
    Node* foundItem;

    printf("Registered products:\n");
    printInputs(table);

    printf("Enter the barcode of the input you want: ");
    while (scanf("%d", &key) != 1) {
        printf("Error! Please, enter an integer value in this field.\n:");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    foundItem = search(table, key);

    if (foundItem != NULL) {
        printf("Enter the quantity you want to add: ");
        while (scanf("%d", &quantity) != 1) {
            printf("Error! Please, enter an integer value in this field.\n:");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        foundItem->input.amount += quantity;
        printFileTxt(table);
        printf("Increment successful. New amount: %d\n", foundItem->input.amount);
    } else {
        printf("Product not found.\n");
    }
}

void removeInput(List table[]) {
    int key;
    int id;
    Node *current, *prev = NULL;

    printf("Enter the barcode of the product you want to remove: ");
    while (scanf("%d", &key) != 1) {
        printf("Error! Please, enter an integer value in this field.\n:");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    id = hashFunction(key);
    current = table[id];

    while (current != NULL) {
        if (current->input.barcode == key) {
            if (prev == NULL) {
                table[id] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printFileTxt(table);
            printf("Product removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Product not found.\n");
}

void editInput(List table[]) {
    int key;
    Node* foundItem;

    printf("Enter the barcode of the product you want to edit: ");
    while (scanf("%d", &key) != 1) {
        printf("Error! Please, enter an integer value in this field.\n:");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    foundItem = search(table, key);

    if (foundItem != NULL) {
        printf("Editing product with barcode %d:\n", key);

        printf("Enter new product name: ");
        fgets(foundItem->input.productName, 50, stdin);
        foundItem->input.productName[strcspn(foundItem->input.productName, "\n")] = '\0';

        printf("Enter new amount: ");
        while (scanf("%d", &foundItem->input.amount) != 1) {
            printf("Error: Please, enter an integer value for the amount!\n:");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printFileTxt(table);
        printf("Product updated successfully!\n");
    } else {
        printf("Product not found.\n");
    }
}