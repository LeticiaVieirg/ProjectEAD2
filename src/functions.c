#include "../include/functions.h"

void menu() {
    printf("\n=======================================\n");
    printf("              Dental Clinic System\n");
    printf("=======================================\n");
    printf("[1] Schedule Appointment\n");
    printf("[2] Search for Appointment\n");
    printf("[3] Cancel Appointment\n");
    printf("[4] Add Inventory Item\n");
    printf("[5] Search for Inventory Item\n");
    printf("[6] Search for Patient\n");
    printf("[7] Exit\n");
    printf("=======================================\n");
    printf("Enter your choice: ");
}

void number_treatment(char *num_variable) {
    int counter, counter2;
    for (counter = 0; num_variable[counter] != '\0'; counter++) {
        if (num_variable[counter] < 48 || num_variable[counter] > 57) {
            for (counter2 = counter; num_variable[counter2] != '\0'; counter2++) {
                num_variable[counter2] = num_variable[counter2 + 1];
            }
            counter--;
        }
    }
}
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Clears the buffer by reading until newline or EOF
}