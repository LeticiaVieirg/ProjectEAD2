#include "../include/functions.h"


void menuStock(List table[]) {
    int option;

    do {
        system(CLEAR);
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
                insertInputs(table);
                printf("\nPressione Enter para continuar...");
                getchar(); 
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
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }
            case 3:
                printInputs(table);
                getchar(); 
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4: 
                removeInput(table); 
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 5:
                editInput(table);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 6:
                increment(table);
                printf("\nPressione Enter para continuar...");
                getchar();
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
    int option;
    char cpf[12]; 
    char name[100];
    int age;

    loadPatients(&root); 

    do {
        system(CLEAR);
        printf("\n=======================================\n");
        printf("              Patient area               \n");
        printf("=========================================\n");
        printf("[1] Search\n");
        printf("[2] Print patient\n");
        printf("[3] Edit patient\n");
        printf("[4] Add patient\n");
        printf("[5] Return to main menu\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &option) != 1 || option < 1 || option > 5) {
            printf("Invalid option. Please enter a number between 1 and 5.\n");
            clear_buffer();
            option = -1;
        }

        switch(option) {
            case 1:
                do {
                    printf("Enter CPF (numbers only): ");
                    scanf("%s", cpf);
                    
                    if (!isOnlyNumbers(cpf)) {
                        system(CLEAR);
                        printf("Invalid CPF! Enter numbers only.\n");
                        clear_buffer();
                    }
                } while (!isOnlyNumbers(cpf)); 
                system(CLEAR);
                searchPatientByCPF(root, cpf);
                getchar();
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 2:
                system(CLEAR);
                printInOrder(root);
                getchar();
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 3:
                do{
                    printf("Enter the CPF of the patient to edit: ");
                    scanf("%s", cpf);

                    if (!isOnlyNumbers(cpf)) {
                        system(CLEAR);
                        printf("Invalid CPF! Enter numbers only.\n");
                        clear_buffer();
                    }
                } while (!isOnlyNumbers(cpf));
                system(CLEAR);
                editPatient(root, cpf);
                printf("\nPressione Enter para continuar...");
                getchar();
                getchar();
                break;
            case 4:
                getchar(); 
                do {
                    printf("Enter the patient's name: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = 0; 

                    if (!isOnlyLetters(name)) {
                        system(CLEAR);
                        printf("Invalid name! Enter letters only.\n");
                    }
                } while (!isOnlyLetters(name));

                do{
                    printf("Enter the patient's CPF: ");
                    scanf("%s", cpf);

                    if (!isOnlyNumbers(cpf)) {
                        system(CLEAR);
                        printf("Invalid CPF! Enter numbers only.\n");
                        clear_buffer();
                    }
                } while (!isOnlyNumbers(cpf));

                do {
                    printf("Enter the patient's age: ");
                    if (scanf("%d", &age) != 1 || age <= 0) {
                        system(CLEAR);
                        printf("Invalid age! Enter a valid number.\n");
                        clear_buffer();
                    } else {
                        break;
                    }
                } while (1);

                insertPatient(&root, name, cpf, age);
                getchar();  
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 5);

    FILE *file = fopen("PatientBank.txt", "w");
    if (file) {
        fclose(file);
    }
    savePatients(root);
    freeTree(root);
}

void menuConsultation(List table[]){
    Patient patient;
    NodePatient *root = NULL;
    Heap *heap = createHeap(10);
    loadPatients(&root); 
    int option;
    char CPF[11];

    loadFromFileHeap(heap);

    do {
        system(CLEAR);
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
                do{
                    printf("Enter the patient's CPF: ");
                    scanf("%s", CPF);

                    if (!isOnlyNumbers(CPF)) {
                        system(CLEAR);
                        printf("Invalid CPF! Enter numbers only.\n");
                        clear_buffer();
                    }
                } while (!isOnlyNumbers(CPF));
                system(CLEAR);

                searchByCPF(heap, CPF);
                getchar();
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 2:
                displayHeap(heap);
                getchar();
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 3:
                insertIntoHeap(heap, &root, table); 
                getchar();
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4:
                patient =  removeHeap(heap);
                if(patient.null == -1){
                    printf("There are no queries to remove!\n");
                } else {
                    printf("Consultation carried out successfully!\n");
                }
                getchar();
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 5:
                do{
                    printf("Enter the patient's CPF: ");
                    scanf("%s", CPF);

                    if (!isOnlyNumbers(CPF)) {
                        system(CLEAR);
                        printf("Invalid CPF! Enter numbers only.\n");
                        clear_buffer();
                    }
                } while (!isOnlyNumbers(CPF));
                system(CLEAR);

                editConsultationByCPF(heap, CPF, table);
                getchar();
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while(option != 6);

    writeToFile(heap);
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isOnlyLetters(char *str){
    for(int i  = 0; str[i] != '\0'; i++){
        if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))){
            return 0;
        }
    }
    return 1;
}

int isOnlyNumbers(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}