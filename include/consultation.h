//declaring the libraries
#include "../include/stock.h"

typedef struct {
    int age;
    char description[50];
} Patient;

typedef struct {
    Patient *Patient;
    int size;
    int capacity;
} Heap;