#include "../include/patient.h"

// Function to create a new patient node
NodePatient* createNode(const char *name, const char *cpf, int age) {
    NodePatient *newNode = malloc(sizeof(NodePatient));
    strcpy(newNode->cpf, cpf);
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a patient into the binary tree
void insertPatient(NodePatient **root, const char *name, const char *cpf, int age) {
    if (*root == NULL) {
        *root = createNode(name, cpf, age);
    } else if (strcmp(cpf, (*root)->cpf) < 0) {
        insertPatient(&(*root)->left, name, cpf, age);
    } else {
        insertPatient(&(*root)->right, name, cpf, age);
    }
}

// Function to load patients from a file
void loadPatients(NodePatient **root) {
    FILE *file = fopen("PatientBank.txt", "r");
    if (!file) {
        perror("Could not open file");
        return;
    }
    
    char name[100];
    char cpf[12];
    int age;
    
    while (fscanf(file, " %[^\n]s", name) != EOF) {  // Read the name
        fscanf(file, "%s", cpf);  // Read the CPF
        fscanf(file, "%d", &age); // Read the age
        insertPatient(root, name, cpf, age);
    }
    fclose(file);
}

// Function to search for a patient by CPF
void searchPatientByCPF(NodePatient *root, const char *cpf) {
    if (root == NULL) {
        printf("Patient not found.\n");
        return;
    }
    if (strcmp(cpf, root->cpf) == 0) {
        printf("Patient found: Name = %s, CPF = %s, Age = %d\n", root->name, root->cpf, root->age);
    } else if (strcmp(cpf, root->cpf) < 0) {
        searchPatientByCPF(root->left, cpf);
    } else {
        searchPatientByCPF(root->right, cpf);
    }
}

NodePatient* returnSearchPatientByCPF(NodePatient *root, const char *cpf) {
    if (root == NULL) {
        return NULL; // Patient not found
    }

    if (strcmp(cpf, root->cpf) == 0) {
        return root; // Patient found
    } else if (strcmp(cpf, root->cpf) < 0) {
        return returnSearchPatientByCPF(root->left, cpf);
    } else {
        return returnSearchPatientByCPF(root->right, cpf);
    }
}

// Function to edit patient details
void editPatient(NodePatient *root, const char *cpf) {
    if (root == NULL) {
        printf("Patient with CPF %s not found.\n", cpf);
        return;
    }

    // If we find the patient
    if (strcmp(cpf, root->cpf) == 0) {
        // Ask user for new details
        char newName[100];
        int newAge;
        getchar();
        
        printf("Enter new name (or press Enter to keep current): ");
        fgets(newName, sizeof(newName), stdin);
        
        // If the user provides a new name, update it
        if (newName[0] != '\n') {
            newName[strcspn(newName, "\n")] = 0;  // Remove the trailing newline character
            strcpy(root->name, newName);          // Update the name
        }
        
        // Ask for new age
        printf("Enter new age (or press 0 to keep current): ");
        scanf("%d", &newAge);
        
        // Update the age if a valid new age is provided
        if (newAge > 0) {
            root->age = newAge;
        }

        printf("Patient details updated: Name = %s, CPF = %s, Age = %d\n", root->name, root->cpf, root->age);
    }
    else if (strcmp(cpf, root->cpf) < 0) {
        editPatient(root->left, cpf);
    }
    else {
        editPatient(root->right, cpf);
    }
}

// Function to print all patients in order
void printInOrder(NodePatient *root) {
    if (root) {
        printInOrder(root->left);
        printf("Name: %s, CPF: %s, Age: %d\n", root->name, root->cpf, root->age);
        printInOrder(root->right);
    }
}

// Function to save patients to a file
void savePatients(NodePatient *root) {
    FILE *file = fopen("PatientBank.txt", "a");
    if (!file) {
        perror("Could not open file");
        return;
    }

    // Use in-order traversal to write all patients
    if (root) {
        savePatients(root->left); // Save left subtree first
        fprintf(file, "%s\n%s\n%d\n", root->name, root->cpf, root->age); // Save name, CPF, and age
        savePatients(root->right); // Save right subtree
    }
    
    fclose(file);
}

// Function to free the memory allocated for the tree
void freeTree(NodePatient *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

