#include "../include/patient.h"

void formatCPF(char *formattedCPF, const char *cpf) {
    sprintf(formattedCPF, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

Node *initializeNode(Patient newPatient) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error allocating memory!\n");
        return NULL;
    }

    newNode->patient = newPatient;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void cleanCPF(char *cpf) {
    cpf[strcspn(cpf, "\n")] = '\0';
    if (strlen(cpf) != 11) {
        printf("Invalid CPF. It must have 11 digits.\n");
        cpf[0] = '\0'; 
    }
}

Node *insertNode(Node *root, Patient newPatient) {
    if (root == NULL) {
        return initializeNode(newPatient);
    }

    int cmp = strcmp(root->patient.cpf, newPatient.cpf);
    if (cmp > 0) {
        root->left = insertNode(root->left, newPatient);
    } else if (cmp < 0) {
        root->right = insertNode(root->right, newPatient);
    } else {
        printf("Patient with CPF %s already exists.\n", newPatient.cpf);
    }

    return root;
}

Node *searchNode(Node *root, const char *cpf) {
    if (root == NULL || strcmp(root->patient.cpf, cpf) == 0) {
        return root;
    }

    if (strcmp(root->patient.cpf, cpf) > 0) {
        return searchNode(root->left, cpf);
    } else {
        return searchNode(root->right, cpf);
    }
}

void searchPatientByCPF(Node *root, const char *cpf) {
    Node *node = searchNode(root, cpf);
    if (node == NULL) {
        printf("Patient with CPF %s not found.\n", cpf);
        return;
    }

    char formattedCPF[15];
    formatCPF(formattedCPF, node->patient.cpf);
    printf("Name: %s\n", node->patient.name);
    printf("CPF: %s\n", formattedCPF);
    printf("Age: %d\n", node->patient.age);
}

void editPatient(Node *root, const char *cpf) {
    Node *node = searchNode(root, cpf);
    if (node == NULL) {
        printf("Patient with CPF %s not found.\n", cpf);
        return;
    }

    printf("Editing patient with CPF %s\n", cpf);
    getchar();

    printf("Enter new name: ");
    fgets(node->patient.name, sizeof(node->patient.name), stdin);
    node->patient.name[strcspn(node->patient.name, "\n")] = '\0';

    printf("Enter new age: ");
    scanf("%d", &node->patient.age);
    getchar();

    printf("Patient updated successfully.\n");
}

void printInOrder(Node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        char formattedCPF[15];
        formatCPF(formattedCPF, root->patient.cpf);
        printf("Name: %s\n", root->patient.name);
        printf("CPF: %s\n", formattedCPF);
        printf("Age: %d\n", root->patient.age);
        printf("\n");
        printInOrder(root->right);
    }
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void writePatient(FILE *file, Node *node) {
    if (node != NULL) {
        writePatient(file, node->left);
        fprintf(file, "%s\n%s\n%d\n", node->patient.name, node->patient.cpf, node->patient.age);
        writePatient(file, node->right);
    }
}

void savePatients(Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    writePatient(file, root);
    fclose(file);
}

void loadPatients(Node **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    Patient p;
    while (fscanf(file, "%[^\n]\n%[^\n]\n%d\n", p.name, p.cpf, &p.age) == 3) {
        *root = insertNode(*root, p);
    }

    fclose(file);
}

// // Função principal
// int main() {
//     Node *root = NULL;
//     int option;
//     Patient p;
//     char cpf[12];  // CPF length is 11 + 1 for the null terminator
//     const char *filename = "PatientBank.txt";

//     // Load patients from file
//     loadPatients(&root, filename);

//     do {
//         printf("\n--- Patient Management System ---\n");
//         printf("1. Register a new patient\n");
//         printf("2. Search for a patient by CPF\n");
//         printf("3. Edit a patient by CPF\n");
//         printf("4. Print all patients\n");
//         printf("5. Save and exit\n");
//         printf("Select an option: ");
//         scanf("%d", &option);
//         getchar(); // Remove newline character from buffer

//         switch (option) {
//             case 1:
//                 // Cadastro de pacientes
//                 printf("Enter patient name: ");
//                 fgets(p.name, sizeof(p.name), stdin);
//                 p.name[strcspn(p.name, "\n")] = '\0'; // Remove newline

//                 printf("Enter patient CPF (only digits): ");
//                 fgets(p.cpf, sizeof(p.cpf), stdin);
//                 cleanCPF(p.cpf);
//                 if (strlen(p.cpf) != 11) {
//                     printf("Invalid CPF. Patient not registered.\n");
//                     break;
//                 }

//                 printf("Enter patient age: ");
//                 scanf("%d", &p.age);
//                 getchar(); // Remove newline character from buffer

//                 root = insertNode(root, p);
//                 printf("Patient registered successfully.\n");
//                 break;

//             case 2:
//                 // Buscar paciente por CPF
//                 printf("Enter CPF of patient to search: ");
//                 fgets(cpf, sizeof(cpf), stdin);
//                 cleanCPF(cpf);
//                 searchPatientByCPF(root, cpf);
//                 break;

//             case 3:
//                 // Editar paciente por CPF
//                 printf("Enter CPF of patient to edit: ");
//                 fgets(cpf, sizeof(cpf), stdin);
//                 cleanCPF(cpf);
//                 editPatient(root, cpf);
//                 break;

//             case 4:
//                 // Exibir todos os pacientes
//                 printf("\n--- List of all patients ---\n");
//                 printInOrder(root);
//                 break;

//             case 5:
//                 // Salvar e sair
//                 savePatients(root, filename);
//                 freeTree(root);
//                 printf("Data saved to %s. Exiting...\n", filename);
//                 break;

//             default:
//                 printf("Invalid option. Please try again.\n");
//                 break;
//         }
//     } while (option != 5);

//     return 0;
// }