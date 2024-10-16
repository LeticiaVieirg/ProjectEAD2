// Declaring the libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PATIENT_H
#define PATIENT_H

// Rename the struct for Patient
typedef struct NodePatient {
    char name[100]; 
    char cpf[12];  
    int age;
    struct NodePatient *left;
    struct NodePatient *right;
} NodePatient;

// Function to create a new patient node
NodePatient* createNode(const char *name, const char *cpf, int age);

// Function to insert a new patient into the binary tree
void insertPatient(NodePatient **root, const char *name, const char *cpf, int age);

// Function to search for a patient by CPF in the binary tree
NodePatient* returnSearchPatientByCPF(NodePatient *root, const char *cpf);

// Function to load patients from a file or other source into the binary tree
void loadPatients(NodePatient **root);

// Function to search for a patient by CPF and print their details
void searchPatientByCPF(NodePatient *root, const char *cpf);

// Function to edit a patient's information by CPF
void editPatient(NodePatient *root, const char *cpf);

// Function to print the patient records in in-order traversal
void printInOrder(NodePatient *root);

// Function to save patient records to a file or other destination
void savePatients(NodePatient *root);

// Function to free the memory allocated for the binary tree
void freeTree(NodePatient *root);


#endif