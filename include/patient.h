//Declaring the libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PATIENT_H
#define PATIENT_H

//Rename the struct for Patient
typedef struct NodePatient{
    char name[100]; 
    char cpf[12];  
    int age;
    struct NodePatient *left;
    struct NodePatient *right;
} NodePatient;

NodePatient* createNode(const char *name, const char *cpf, int age);
void loadPatients(NodePatient **root);
void searchPatientByCPF(NodePatient *root, const char *cpf);
void editPatient(NodePatient *root, const char *cpf);
void printInOrder(NodePatient *root);
void savePatients(NodePatient *root);
void freeTree(NodePatient *root);
#endif
