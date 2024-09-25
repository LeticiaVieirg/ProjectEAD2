#include "../include/consultation.h"
List table[SIZE];

Heap *createHeap(int capacity) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    heap->Patient = (Patient*) malloc(capacity * sizeof(Patient));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Patient *patientOne, Patient *patientTwo) {
    Patient temp = *patientOne;
    *patientOne = *patientTwo;
    *patientTwo = temp;
}

void heapUp(Heap *heap, int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;
    if (heap->Patient[index].age > heap->Patient[parent].age) {
        swap(&heap->Patient[index], &heap->Patient[parent]);
        heapUp(heap, parent);
    }
}

void insertIntoHeap(Heap *heap, NodePatient **root, List table[]) {
    if (heap->size == heap->capacity) {
        printf("Full heap!\n");
        return;
    }

    Patient newPatient;
    char CPF[11];

    printf("Enter the patient's CPF: ");
    scanf("%s", CPF);

    NodePatient *foundPatient = returnSearchPatientByCPF(*root, CPF);
    if (foundPatient == NULL) {
        printf("Patient not found.\n");
    } else {
        printf("Patient found:\n");
        printf("Name: %s, Age: %d, CPF: %s\n", foundPatient->name, foundPatient->age, foundPatient->cpf);

        // Preencher os campos do novo paciente
        newPatient.dataPataient.age = foundPatient->age;
        strcpy(newPatient.dataPataient.name, foundPatient->name);  // Copia o nome
        strcpy(newPatient.dataPataient.cpf, foundPatient->cpf);    // Copia o CPF

        printf("Inform the procedure to be carried out: \n");
        getchar(); // Limpa o buffer antes de ler a descrição
        fgets(newPatient.description, sizeof(newPatient.description), stdin);
        newPatient.description[strcspn(newPatient.description, "\n")] = '\0';

        printf("Provide the necessary inputs for the procedure:\n");
        int totalDecremented = 0;
        DecrementResult* results = decrement(table, &totalDecremented);
        strcpy(newPatient.dataInputs.productName, results->name);
        newPatient.dataInputs.amount = results->quantity;
    }

    // Insere o novo paciente na heap
    heap->Patient[heap->size] = newPatient;
    heapUp(heap, heap->size);
    heap->size++;
}

void heapBelow(Heap *heap, int index) {
    int bigger = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->Patient[left].age > heap->Patient[bigger].age) {
        bigger = left;
    }

    if (right < heap->size && heap->Patient[right].age > heap->Patient[bigger].age) {
        bigger = right;
    }

    if (bigger != index) {
        swap(&heap->Patient[index], &heap->Patient[bigger]);
        heapBelow(heap, bigger);  
    }
}

void searchByCPF(Heap *heap, const char *CPF) {
    int found = 0;  // Flag to indicate if the patient is found
    
    for (int i = 0; i < heap->size; i++) {
        if (strcmp(heap->Patient[i].dataPataient.cpf, CPF) == 0) {
            printf("Patient found at position %d:\n", i + 1);
            printf("Patient: %s\n", heap->Patient[i].dataPataient.name);
            printf("CPF: %s, Age: %d\n", heap->Patient[i].dataPataient.cpf, heap->Patient[i].dataPataient.age);
            printf("Description: %s\n", heap->Patient[i].description);
            printf("Input: %s, Amount: %d\n", heap->Patient[i].dataInputs.productName, heap->Patient[i].dataInputs.amount);
            found = 1;
            break;  // Stop after finding the first match
        }
    }

    if (!found) {
        printf("Patient with CPF %s not found.\n", CPF);
    }
}

Patient removeHeap(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap Null!\n");
        exit(1);
    }

    // Remove a raiz (maior valor)
    Patient patientRemoved = heap->Patient[0];
    heap->Patient[0] = heap->Patient[heap->size - 1];
    heap->size--;

    heapBelow(heap, 0);  

    return patientRemoved;
}

void freeHeap(Heap *heap) {
    free(heap->Patient);
    free(heap);
}

void displayHeap(Heap *heap) {
    printf("Query List: \n");
    for (int i = 0; i < heap->size; i++) {
        printf("Position %d\n", i + 1);
        printf("Patient: %s\n", heap->Patient[i].dataPataient.name);
        printf("CPF: %s, Age: %d\n", heap->Patient[i].dataPataient.cpf, heap->Patient[i].dataPataient.age);
        printf("Description: %s\n", heap->Patient[i].description);
        printf("Input: %s, amount: %d\n", heap->Patient[i].dataInputs.productName, heap->Patient[i].dataInputs.amount);
    }
}