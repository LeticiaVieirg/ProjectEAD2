#include "../include/patient.h"


NodePatient* createNode(const char *name, const char *cpf, int age) {
    NodePatient *newNode = malloc(sizeof(NodePatient));
    strcpy(newNode->cpf, cpf);
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->left = newNode->right = NULL;
    return newNode;
}


void insertPatient(NodePatient **root, const char *name, const char *cpf, int age) {
    if (*root == NULL) {
        *root = createNode(name, cpf, age);
    } else if (strcmp(cpf, (*root)->cpf) < 0) {
        insertPatient(&(*root)->left, name, cpf, age);
    } else {
        insertPatient(&(*root)->right, name, cpf, age);
    }
}


void loadPatients(NodePatient **root) {
    FILE *file = fopen("PatientBank.txt", "r");
    if (!file) {
        perror("Could not open file");
        return;
    }
    
    char name[100];
    char cpf[12];
    int age;
    
    while (fscanf(file, " %[^\n]s", name) != EOF) { 
        fscanf(file, "%s", cpf); 
        fscanf(file, "%d", &age); 
        insertPatient(root, name, cpf, age);
    }
    fclose(file);
}


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
        return NULL; 
    }

    if (strcmp(cpf, root->cpf) == 0) {
        return root; 
    } else if (strcmp(cpf, root->cpf) < 0) {
        return returnSearchPatientByCPF(root->left, cpf);
    } else {
        return returnSearchPatientByCPF(root->right, cpf);
    }
}


void editPatient(NodePatient *root, const char *cpf) {
    if (root == NULL) {
        printf("Patient with CPF %s not found.\n", cpf);
        return;
    }

    
    if (strcmp(cpf, root->cpf) == 0) {
        
        char newName[100];
        int newAge;
        getchar();
        
        printf("Enter new name (or press Enter to keep current): ");
        fgets(newName, sizeof(newName), stdin);
        
        
        if (newName[0] != '\n') {
            newName[strcspn(newName, "\n")] = 0;  
            strcpy(root->name, newName);        
        }
        
        
        printf("Enter new age (or press 0 to keep current): ");
        scanf("%d", &newAge);
        
        
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


void printInOrder(NodePatient *root) {
    if (root) {
        printInOrder(root->left);
        printf("Name: %s, CPF: %s, Age: %d\n", root->name, root->cpf, root->age);
        printInOrder(root->right);
    }
}


void savePatients(NodePatient *root) {
    FILE *file = fopen("PatientBank.txt", "a");
    if (!file) {
        perror("Could not open file");
        return;
    }


    if (root) {
        savePatients(root->left);
        fprintf(file, "%s\n%s\n%d\n", root->name, root->cpf, root->age);
        savePatients(root->right); 
    }
    
    fclose(file);
}


void freeTree(NodePatient *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}