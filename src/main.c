#include "../include/functions.h"
#include "../include/stock.h"

int main(void) {
    int option;
    int searchKey;
    List table[SIZE];
    Node *foundItem;

    do {
        do {
            menu();
            printf("Choose an option from the menu: ");
            
            if (scanf(" %d", &option) != 1 || option < 0 || option > 9) {
                printf("Invalid option. Please enter a number between 0 and 9.\n");
                clear_buffer(); // This function will clear the input buffer
                option = -1; // Set to invalid option to trigger loop
            }
        } while (option < 0 || option > 9);

        switch (option) {
            case 1:
                insertInputs(table);
                break;
            case 2:
                printf("Enter barcode to search: ");
                
                // Checking if the input is a valid integer
                while (scanf("%d", &searchKey) != 1) {
                    printf("Error: Please enter a valid integer for the barcode!\n");
                    clear_buffer();
                }
                getchar(); // To consume the newline character
                
                foundItem = search(table, searchKey);
                if (foundItem != NULL) {
                    printf("Product found:\n");
                    printf("\tBarcode: %d\n", foundItem->input.barcode);
                    printf("\tProduct: %s\n", foundItem->input.productName);
                    printf("\tAmount: %d\n", foundItem->input.amount);
                } else {
                    printf("Product not found.\n");
                }
                break;
            case 3:
                printInputs(table);
                break;
            case 4:
            case 5:
            case 6: {
                char cpf_to_find[15];
                printf("Enter the patient's CPF to search: ");
                fgets(cpf_to_find, sizeof(cpf_to_find), stdin);
                cpf_to_find[strcspn(cpf_to_find, "\n")] = '\0';

                int index = find_patient_by_cpf(cpf_to_find);
                if (index != -1) {
                    printf("Patient found:\n");
                    // Print the patient's data
                } else {
                    printf("Patient not found. Do you want to register? (y/n): ");
                    char answer;
                    scanf(" %c", &answer);
                    if (answer == 'y' || answer == 'Y') {
                        register_patient();
                    }
                }
                break;
            }
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("The option entered is invalid...\n");
        }

    } while (option != 0);

    return 0;
}
