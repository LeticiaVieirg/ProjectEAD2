//Declaring the libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PATIENT_H
#define PATIENT_H

//Rename the struct for Patient
typedef struct {
    char name[100]; 
    char cpf[13];  
    int age;
} Patient;

//Rename the struct for Patient
typedef struct Node {
    Patient patient;
    struct Node *right;
    struct Node *left;
} Node;

//Function for 
void formatCPF(char *formattedCPF, const char *cpf);

//Function for initialize 
Node *initializeNode(Patient newPatient);

//
void cleanCPF(char *cpf);

//
Node *insertNode(Node *root, Patient newPatient);

//
Node *searchNode(Node *root, const char *cpf);

//
void searchPatientByCPF(Node *root, const char *cpf);

//
void editPatient(Node *root, const char *cpf);

//
void printInOrder(Node *root);

//
void freeTree(Node *root);

//
void savePatients(Node *root, const char *filename);

void loadPatients(Node **root, const char *filename);

#endif
