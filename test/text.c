#include "../include/stock.h"

int main(void) {
    int option, serachKey;
    List table[SIZE];
    Node *foundItem;

    loadFromFile(table);

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n\t4 - Decrementar\n\t5 - incrementar\n");
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
                    printf("\tBarcode: %d\n", foundItem->input.barcode);
                    printf("\tProduct: %s\n", foundItem->input.productName);
                    printf("\tAmount: %d\n", foundItem->input.amount);
                } else{
                    printf("Product not found.\n");
                }
                break;
            case 3:
                printInputs(table);
                break;
            case 4:
                decrement(table);
                break;
            case 5:
                increment(table);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Option entered is invalid...\n");
        }

    } while (option != 0);

    printFileTxt(table);

    return 0;
}