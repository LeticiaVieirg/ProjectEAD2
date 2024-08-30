#include "../include/stock.h"

void initializeTable(List table[]) {
    for(int i = 0; i < SIZE; i++){
        table[i] = NULL;
    }
}

int hashFunction(int key) {
    return key % SIZE;
}

void printFileTxt(List table[]);
List *loadFromFile(List table[]);
Node *search(List table[], int key);

void insertInputs(List table[]) {
    Inputs newInput;
    Node* newNode = (Node*) malloc(sizeof(Node));

    if(newNode == NULL){
        printf("Error allocating memory...\n");
        free(newNode);
        return;
    }

    printf("Enter barcode: ");
    scanf("%d", &newInput.barcode);
    getchar();

    if (search(table, newInput.barcode) != NULL) {
        printf("Error: A product with this barcode already exists!\n");
        free(newNode);  // Free the memory since we are not going to use it
        return;
    }

    printf("Enter product name: ");
    fgets(newInput.productName, 50, stdin);
    newInput.productName[strcspn(newInput.productName, "\n")] = '\0';  // Remove newline character

    printf("Enter amount: ");
    scanf("%d", &newInput.amount);
    getchar();

    newNode->input = newInput;
    newNode->next = NULL;

    int id = hashFunction(newInput.barcode);

    newNode->next = table[id];
    table[id] = newNode;

    printf("Input inserted successfully!\n");
    
    printFileTxt(table);
}

Node *search(List table[], int key){
    int id = hashFunction(key);
    Node *current = table[id];

    while(current != NULL){
        if(current->input.barcode == key){
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
                if(current != NULL){
                    printf(" - - - - - - - - - - - - - - - - - - - - \n");
                }
            }
        } else {
            printf("NULL\n");
        }
        printf("----------------------------------------\n");
    }
}

void printFileTxt(List table[]){
    FILE *file = fopen("bankStock.txt", "w");
    if(file == NULL){
        printf("error when creating/opening file! \n");
        return;
    }

    for(int i = 0; i < SIZE; i++){
        if(table[i]  != NULL){
            Node *current = table[i];
            while (current != NULL){
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

List *loadFromFile(List table[]){
    FILE *file = fopen("bankStock.txt", "r");
    if(file == NULL){
        printf("File not found. Initializing table with NULL values...\n");
        initializeTable(table); // Initialize table with NULL values if file doesn't exist
        return table;
    }

    initializeTable(table); // Initialize table with NULL values

    int barcode, amount;
    char productName[50];

    while(fscanf(file, "%d\n", &barcode) != EOF) {
        // Use fgets to read the product name, making sure to handle the newline character
        if(fgets(productName, sizeof(productName), file) != NULL) {
            productName[strcspn(productName, "\n")] = '\0';  // Remove newline character from product name
        } else {
            printf("Error reading product name from file.\n");
            continue;  // Skip this entry and go to the next one
        }

        fscanf(file, "%d\n", &amount);

        Inputs newInput;
        Node* newNode = (Node*) malloc(sizeof(Node));

        if(newNode == NULL){
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

void decrement(List table[]){
    int key, quantity;
    Node* foundItem;

    printf("Registered products:\n");
    printInputs(table);
    
    printf("Enter the barcode of the input you want: ");
    scanf("%d", &key);

    foundItem = search(table, key);
    
    if (foundItem != NULL) {
        printf("Enter the quantity you want: ");
        scanf("%d", &quantity);  
        // Check if there is enough stock to decrement
        if (foundItem->input.amount >= quantity) {
            foundItem->input.amount -= quantity;
            printf("Decrement successful. New amount: %d\n", foundItem->input.amount);
        } else {
            printf("Error: Not enough quantity to decrement.\n");
        }
    } else {
        printf("Product not found.\n");
    }
}

void increment(List table[]) {
    int key, quantity;
    Node* foundItem;

    printf("Registered products:\n");
    printInputs(table);

    printf("Enter the barcode of the input you want: ");
    scanf("%d", &key);

    foundItem = search(table, key);

    if (foundItem != NULL) {
        printf("Enter the quantity you want to add: ");
        scanf("%d", &quantity);
        // Increment the quantity
        foundItem->input.amount += quantity;
        printf("Increment successful. New amount: %d\n", foundItem->input.amount);
    } else {
        printf("Product not found.\n");
    }
}

// int main(void) {
//     int option, serachKey;
//     List table[SIZE];
//     Node *foundItem;

//     loadFromFile(table);

//     do {
//         printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n\t4 - Decrementar\n\t5 - incrementar\n");
//         scanf("%d", &option);
//         getchar();

//         switch (option) {
//             case 1:
//                 insertInputs(table);
//                 break;
//             case 2:
//                 printf("Enter barcode to search: ");
//                 scanf("%d", &serachKey);
//                 getchar();

//                 foundItem = search(table, serachKey);
//                 if(foundItem != NULL){
//                     printf("Product found: \n");
//                     printf("\tBarcode: %d\n", foundItem->input.barcode);
//                     printf("\tProduct: %s\n", foundItem->input.productName);
//                     printf("\tAmount: %d\n", foundItem->input.amount);
//                 } else{
//                     printf("Product not found.\n");
//                 }
//                 break;
//             case 3:
//                 printInputs(table);
//                 break;
//             case 4:
//                 decrement(table);
//                 break;
//             case 5:
//                 increment(table);
//                 break;
//             case 0:
//                 printf("Exiting...\n");
//                 break;
//             default:
//                 printf("Option entered is invalid...\n");
//         }

//     } while (option != 0);

//     printFileTxt(table);

//     return 0;
// }