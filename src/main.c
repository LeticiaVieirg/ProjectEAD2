#include "../include/functions.h"

int main(void) {
    List table[SIZE];
    initializeTable(table);
    loadFromFile(table);

    int option;

    do {
        system(CLEAR);
        printf("\n=======================================\n");
        printf("           Dental Clinic System          \n");
        printf("=========================================\n");
        printf("[1] Stock area\n");
        printf("[2] Patient area\n");
        printf("[3] Consultation area\n");
        printf("[4] Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &option) != 1 || option < 0 || option > 4) {
            printf("Invalid option. Please enter a number between 1 and 4.\n");
            clear_buffer();
            option = -1;
        }

        switch (option) {
            case 1:
                menuStock(table);
                break;
            case 2:
                menuPatient();
                break;
            case 3:
                menuConsultation(table);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Option entered is invalid...\n");
        }
    } while (option != 4);
    
    return 0;
}
