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