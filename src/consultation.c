#include "../include/consultation.h"

Heap *createHeap(int capacity){
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    heap->Patient = (Patient*) malloc(capacity *sizeof(Patient));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}
