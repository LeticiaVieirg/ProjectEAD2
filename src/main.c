int main(void) {
    int option, serachKey;
    Inputs table[SIZE];
    Inputs *foundItem;

    initializeTable(table);

    do {
       void menu();
       printf("Escolha uma opção do menu acima:\n");
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
