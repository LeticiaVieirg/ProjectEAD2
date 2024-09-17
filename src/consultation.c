#include "../include/consultation.h"

Heap *createHeap(int capacity){
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    heap->Patient = (Patient*) malloc(capacity *sizeof(Patient));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap( Patient *patientOne, Patient *patientTwo){
    Patient temp = *patientOne;
    *patientOne = *patientTwo;
    *patientTwo = temp;
}

void heapUp(Heap *heap, int index){
    if(index == 0) return;

    int parent = (index - 1) / 2;
    if(heap->Patient[index].age > heap->Patient[parent].age){
        swap(&heap->Patient[index], &heap->Patient[parent]);
        heapUp(heap, parent);
    }
}

void insertIntoHeap(Heap *heap){
    if(heap->size == heap->capacity){
        printf("Full heap!\n");
        return;
    }

    Patient newPatient;
    List table[SIZE];

    printf("Enter the patient's age: ");
    scanf("%d", &newPatient.age);

    printf("Inform the procedure to be carried out: ");
    getchar();
    fgets(newPatient.description, 50, stdin);
    newPatient.description[strcspn(newPatient.description, "\n")] = '\0';

    decrement(table);

    heap->Patient[heap->size] = newPatient;
    heapUp(heap, heap->size);
    heap->size++;
}

void heapBelow(Heap *heap, int index){
    int bigger = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < heap->size && heap->Patient[left].age > heap->Patient[bigger].age){
        bigger = left;
    }

    if(right < heap->size && heap->Patient[right].age > heap->Patient[bigger].age){
        bigger = right;
    }

    if(bigger != index){
        swap(&heap->Patient[index], &heap->Patient[bigger]);
        heapBelow(heap, bigger);
    }
}