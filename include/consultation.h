#ifndef CONSULTAION_H
#define CONSULTAION_H
//declaring the libraries
#include "../include/stock.h"
#include "../include/patient.h"

//
typedef struct {
    int age;
    int null;
    NodePatient dataPataient;
    Inputs dataInputs;
    char description[50];
} Patient;

//
typedef struct {
    Patient *Patient;
    int size;
    int capacity;
} Heap;

//Functions
//Creates a new heap with the specified capacity, initializing the patient array, size, and capacity
Heap *createHeap(int capacity);

//Exchanges the contents of two patient structures
void swap(Patient *patientOne, Patient *patientTwo);

//Compares the element at the given index with its parent and swaps them
void heapUp(Heap *heap, int index);

//Prompts the user for patient information, creates a new patient object, inserts it into the heap, and calls heapUp
void insertIntoHeap(Heap *heap, NodePatient **root, List table[]);

//Compares the element at the given index with its children and swaps it with the larger child
void heapBelow(Heap *heap, int index);

//Replaces the root with the last element, removes the last element, and calls heapBelow
Patient removeHeap(Heap *heap);

//Fries the memory heap allocated for the patient array and the heap structure itself
void freeHeap(Heap *heap);

//Print the patient information for each elements in the heap
void displayHeap(Heap *heap);

// Searches for a patient in the heap by CPF
void searchByCPF(Heap *heap, const char *CPF);

// Writes the patient data to a file
void writeToFile(Heap *heap);

// Loads the patient data from a file into the heap
Heap* loadFromFileHeap(Heap *heap);

// Edits a patient's consultation by CPF and updates the description and input data
void editConsultationByCPF(Heap *heap, const char *CPF, List table[]);

#endif 