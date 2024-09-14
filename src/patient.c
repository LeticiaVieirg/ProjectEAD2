#include "../include/dental_appointment.h"
#include "../include/patiente.h"
#include "../include/functions.h"

Patient patients[MAX_PACIENTES];
int num_patients = 0;

int find_patient_by_cpf(char *cpf) {
    for (int i = 0; i < num_patients; i++) {
        if (strcmp(patients[i].cpf, cpf) == 0) {
            return i; 
        }
    }
    return -1; 
}

void register_patient() {
    Patient new_patient;
    printf("Enter the patient's name: ");
    fgets(new_patient.name, sizeof(new_patient.name), stdin);
    new_patient.name[strcspn(new_patient.name, "\n")] = '\0';

    printf("Enter the patient's CPF: ");
    fgets(new_patient.cpf, sizeof(new_patient.cpf), stdin);
    new_patient.cpf[strcspn(new_patient.cpf, "\n")] = '\0';

    // Check if the patient already exists
    int index = find_patient_by_cpf(new_patient.cpf);
    if (index != -1) {
        printf("Patient already registered!\n");
        return;
    }

    // Add the patient to the list
    patients[num_patients++] = new_patient;
    printf("Patient registered successfully!\n");
}

//Implement in main.c same parts of code
/*
int main() {

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

  */
}
