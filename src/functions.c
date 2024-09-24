#include "../include/functions.h"


void menuStock(List table[]) {
    int option;

    do {
        printf("\n=======================================\n");
        printf("               Stock area                \n");
        printf("=========================================\n");
        printf("[1] Register\n");
        printf("[2] Search\n");
        printf("[3] Print stock\n");
        printf("[4] Delete an item from stock\n");
        printf("[5] Edit stock item\n");
        printf("[6] Add more to stock\n");
        printf("[7] Return to main menu\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &option) != 1 || option < 1 || option > 7) {
            printf("Invalid option. Please enter a number between 1 and 7.\n");
            clear_buffer();
            option = -1;
        }

        switch(option) {
            case 1:
                insertInputs(table);  // Função para registrar item no estoque
                break;
            case 2: {
                int barcode;
                printf("Enter barcode to search: ");
                while (scanf("%d", &barcode) != 1) {
                    printf("Error! Please, enter an integer value in this field.\n:");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                Node* foundItem = search(table, barcode);
                if (foundItem) {
                    printf("Product found: %s, Amount: %d\n", foundItem->input.productName, foundItem->input.amount);
                } else {
                    printf("Product not found.\n");
                }
                break;
            }
            case 3:
                printInputs(table);  // Função para imprimir o estoque
                break;
            case 4: 
                removeInput(table);  // Função para deletar um item do estoque
                break;
            case 5:
                editInput(table);    // Função para editar um item do estoque
                break;
            case 6:
                increment(table);    // Função para adicionar mais ao estoque
                break;
            case 7:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 7);
}

void menuPatient(){
    NodePatient *root = NULL;
    const char *filename = "patients.dat";
    int option;
    char cpf[12];

    loadPatients(&root); // Load patients

    do {
        printf("\n=======================================\n");
        printf("              Patient area               \n");
        printf("=========================================\n");
        printf("[1] Search\n");
        printf("[2] Print patient\n");
        printf("[3] Edit patient\n");
        printf("[4] Return to main menu\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &option) != 1 || option < 1 || option > 4) {
            printf("Invalid option. Please enter a number between 1 and 4.\n");
            clear_buffer();
            option = -1;
        }

        switch(option) {
            case 1:
                printf("Enter CPF: ");
                scanf("%s", cpf);
                searchPatientByCPF(root, cpf);
                break;
            case 2:
                printInOrder(root);
                break;
            case 3:
            printf("Enter the CPF of the patient to edit: ");
            scanf("%s", cpf);
            editPatient(root, cpf);
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 4);
    FILE *file = fopen("PatientBank.txt", "w");
    fclose(file);
    savePatients(root);
    freeTree(root);
}

void menuConsultation(){
    int option;

    do {
        printf("\n=======================================\n");
        printf("            Consultation area            \n");
        printf("=========================================\n");
        printf("[1] Search\n");
        printf("[2] Print Consultation\n");
        printf("[3] Register consultation\n");
        printf("[4] Complete consultation\n");
        printf("[5] Edit consultation\n");
        printf("[6] Return to main menu\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &option) != 1 || option < 1 || option > 6) {
            printf("Invalid option. Please enter a number between 1 and 6.\n");
            clear_buffer();
            option = -1;
        }

        switch(option) {
            case 1:
                // Função para buscar consulta
                break;
            case 2:
                // Função para imprimir dados da consulta
                break;
            case 3:
                // Função para registrar nova consulta
                break;
            case 4:
                // Função para concluir consulta
                break;
            case 5:
                // Função para editar dados da consulta
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 6);
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer do teclado
}
