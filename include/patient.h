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
typedef struct NodePatient {
    Patient patient;
    struct NodePatient *right;
    struct NodePatient *left;
} NodePatient;

//Function for 
void formatCPF(char *formattedCPF, const char *cpf);

//Function for initialize 
NodePatient *initializeNode(Patient newPatient);

//
void cleanCPF(char *cpf);

//
NodePatient *insertNode(NodePatient *root, Patient newPatient);

//
NodePatient *searchNode(NodePatient *root, const char *cpf);

//
void searchPatientByCPF(NodePatient *root, const char *cpf);

//
void editPatient(NodePatient *root, const char *cpf);

//
void printInOrder(NodePatient *root);

//
void freeTree(NodePatient *root);

//
void savePatients(NodePatient *root, const char *filename);

void loadPatients(NodePatient **root, const char *filename);

#endif
