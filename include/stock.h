//declaring the libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Defining hash table size
#define SIZE 13

//Declaration of the input type structure
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

//fuctions
//Function that initializes the hash table
void initializeTable(List table[]);

//function that generates my hash
int hashFunction(int key);

//Function that inserts the inputs into the hash table
void insertInputs(List table[]);

//Function searches for a specific element in the table
Node *search(List table[], int key);

//Function prints the hash table
void printInputs(List table[]);

//Function prints the hash table in the text file
void printFileTxt(List table[]);

//Function that reads data from the text file and throws it into the hash table
List *loadFromFile(List table[]);

//Function that reduces the amount of inputs
void decrement(List table[]);

//Function that increases the amount of inputs
void increment(List table[]);

void removeInput(List table[]);
