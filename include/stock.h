#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Defining hash table size
#define SIZE 13
// 599

typedef struct {
    int amount;
    int barcode;
    char productName[50];
} Inputs;

//Creating the simple linked list structure
typedef struct node{
    Inputs input;
    struct node *next;
} Node;

typedef Node* List;