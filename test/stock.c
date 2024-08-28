#include <stdio.h>
#include <string.h>

// Defining hash table size
#define SIZE 13
// 599

typedef struct {
    int amount;
    int barcode;
    char productName[50];
} Inputs;

void initializeTable(Inputs table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].amount = 0;
        table[i].barcode = 0;
        strcpy(table[i].productName, "");
    }
}

int hashFunction(int key) {
    return key % SIZE;
}

void insertInputs(Inputs table[]) {
    Inputs newInput;

    printf("Enter barcode: ");
    scanf("%d", &newInput.barcode);
    getchar();

    printf("Enter product name: ");
    fgets(newInput.productName, 50, stdin);
    newInput.productName[strcspn(newInput.productName, "\n")] = '\0';  // Remove newline character

    printf("Enter amount: ");
    scanf("%d", &newInput.amount);
    getchar();

    int id = hashFunction(newInput.barcode);
    table[id] = newInput;

    printf("Input inserted successfully!\n");
}

Inputs *search(Inputs table[], int key){
    int id = hashFunction(key);
    int startId = id;
    while(table[id].barcode != 0){
        if(table[id].barcode == key){
            return &table[id];
        }
        id = (id + 1) % SIZE;
        if(id == startId){
            break;
        }
    }
    return NULL;
}

void printInputs(Inputs table[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("Hash: %d\n", i);
        if (table[i].amount > 0) {
            printf("    Barcode: %d\n", table[i].barcode);
            printf("    Product: %s\n", table[i].productName);
            printf("    Amount: %d\n", table[i].amount);
        } else {
            printf("    NULL\n");
        }
        printf("----------------------------------------\n");
    }
}


int main(void) {
    int option, serachKey;
    Inputs table[SIZE];
    Inputs *foundItem;

    initializeTable(table);

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                insertInputs(table);
                break;
            case 2:
                printf("Enter barcode to search: ");
                scanf("%d", &serachKey);
                getchar();

                foundItem = search(table, serachKey);
                if(foundItem != NULL){
                    printf("Product found: \n");
                    printf("\tBarcode: %d\n", foundItem->barcode);
                    printf("\tProduct: %s\n", foundItem->productName);
                    printf("\tAmount: %d\n", foundItem->amount);
                } else{
                    printf("Product not found.\n");
                }
                break;
            case 3:
                printInputs(table);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Opção informada é inválida...\n");
        }

    } while (option != 0);

    return 0;
}
