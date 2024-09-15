#include "../include/functions.h"
#include "../include/stock.h"

int main(void) {
    int option, serachKey;
    List table[SIZE];
    Node *foundItem;

    initializeTable(table);
//depois le,=mbrar de chamar as funcoes corretas nos case
    do {
        menu();
        printf("Escolha uma opcao do menu acima:\n");
        while (scanf("%d", &option) != 1) {
            printf("Erro: Please, enter an integer value for the option!\n:");
            while (getchar() != '\n');
        }
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
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Opcao informada é inválida...\n");
        }

    } while (option != 0);

    return 0;
}
